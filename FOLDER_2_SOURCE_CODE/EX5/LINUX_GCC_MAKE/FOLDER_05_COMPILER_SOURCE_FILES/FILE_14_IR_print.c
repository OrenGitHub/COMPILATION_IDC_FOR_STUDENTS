/*************************/
/* FILE NAEM: IR_Print.c */
/*************************/

/****************************************/
/* WARNING DISABLE: sprintf - I love it */
/****************************************/
#pragma warning (disable: 4996)

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "frame.h"
#include "FILE_02_symbol.h"
#include "FILE_03_StarKist_ErrorMsg.h"
#include "FILE_06_StarKist_AST.h"
#include "FILE_08_semant.h"
#include "FILE_10_SymbolTableEntry.h"
#include "FILE_11_Types.h"
#include "FILE_13_IR_tree.h"

/********************/
/* GLOBAL VARIABLES */
/********************/
static FILE *fl;

void IR_PrintTreeRecursively(T_exp IR_Tree)
{
	/*****************/
	/* [0] Oh well.. */
	/*****************/
	if (IR_Tree == NULL) return;

	/***********************************/
	/* [1] Print my serial node number */
	/***********************************/
	fprintf(fl,"v%d ",IR_Tree->PrintMyNodeSerialNumber);

	/***************************/
	/* [2] Print my node label */
	/***************************/
	fprintf(fl,"[label = \"%s\"];\n",IR_Tree->PrintTheKindOfTreeIAm);

	/***********************************************/
	/* [3] Print the remaining subtree recursively */
	/***********************************************/
	switch (IR_Tree->kind) {

	case (T_SEQ):
		
		if (IR_Tree->u.SEQ.left)  fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.SEQ.left->PrintMyNodeSerialNumber);
		if (IR_Tree->u.SEQ.right) fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.SEQ.right->PrintMyNodeSerialNumber);
		
		IR_PrintTreeRecursively(IR_Tree->u.SEQ.left);
		IR_PrintTreeRecursively(IR_Tree->u.SEQ.right);

		break;

	case (T_MOVE):

		if (IR_Tree->PrintMyNodeSerialNumber == 76)
		{
			int oren=100;
		}

		if (IR_Tree->u.MOVE.dst) fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.MOVE.dst->PrintMyNodeSerialNumber);
		if (IR_Tree->u.MOVE.src) fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.MOVE.src->PrintMyNodeSerialNumber);

		IR_PrintTreeRecursively(IR_Tree->u.MOVE.dst);
		IR_PrintTreeRecursively(IR_Tree->u.MOVE.src);

		break;

	case (T_BINOP):

		if (IR_Tree->u.BINOP.left)  fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.BINOP.left->PrintMyNodeSerialNumber);
		if (IR_Tree->u.BINOP.right) fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.BINOP.right->PrintMyNodeSerialNumber);

		IR_PrintTreeRecursively(IR_Tree->u.BINOP.left);
		IR_PrintTreeRecursively(IR_Tree->u.BINOP.right);

		break;

	case (T_MEM):

		if (IR_Tree->u.MEM)
		{
			fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.MEM->PrintMyNodeSerialNumber);
		}

		IR_PrintTreeRecursively(IR_Tree->u.MEM);

		break;

	case (T_FUNCTION):

		fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.FUNCTION.prologue->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.FUNCTION.body->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.FUNCTION.epilogue->PrintMyNodeSerialNumber);

		IR_PrintTreeRecursively(IR_Tree->u.FUNCTION.prologue);
		IR_PrintTreeRecursively(IR_Tree->u.FUNCTION.body);
		IR_PrintTreeRecursively(IR_Tree->u.FUNCTION.epilogue);

		break;

	case (T_CJUMP):

		fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.CJUMP.left->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",IR_Tree->PrintMyNodeSerialNumber,IR_Tree->u.CJUMP.right->PrintMyNodeSerialNumber);

		IR_PrintTreeRecursively(IR_Tree->u.CJUMP.left);
		IR_PrintTreeRecursively(IR_Tree->u.CJUMP.right);

		break;
	};
}

void IR_PrintTreeInit(const char *filename)
{
	fl=fopen(filename,"w+t");
	if (fl == NULL) return;

	fprintf(fl,"digraph\n");
	fprintf(fl,"{\n");
	fprintf(fl,"graph [ordering = \"out\"]\n");
}

void IR_PrintTreeEnd(void)
{
	fprintf(fl,"\n}");
	fclose(fl);
}

void IR_PrintTree(T_exp IR_tree,const char *filename)
{
	/************/
	/* [1] Init */
	/************/
	IR_PrintTreeInit(filename);

	/******************************/
	/* [2] Print Tree Recursively */
	/******************************/
	IR_PrintTreeRecursively(IR_tree);

	/***********/
	/* [3] End */
	/***********/
	IR_PrintTreeEnd();
}
