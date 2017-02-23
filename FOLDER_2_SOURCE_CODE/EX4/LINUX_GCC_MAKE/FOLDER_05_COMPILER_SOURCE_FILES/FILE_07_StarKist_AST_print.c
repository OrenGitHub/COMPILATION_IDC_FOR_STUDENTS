/****************************/
/* FILE NAEM: ABSYN_Print.c */
/****************************/

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

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
void ABSYN_PrintTreeRecursively(A_exp ABSYN_Tree);

void ABSYN_PrintVar(A_var var)
{
	fprintf(fl, "v%d [label = \"%s\"];\n", var->PrintMyNodeSerialNumber, var->PrintTheKindOfTreeIAm);

	switch (var->kind) {
	case (A_simpleVar) :

		break;

	case (A_fieldVar) :

		fprintf(fl, "v%d -> v%d;\n", var->PrintMyNodeSerialNumber, var->u.field.var->PrintMyNodeSerialNumber);
		ABSYN_PrintVar(var->u.field.var);

		break;

	case (A_subscriptVar) :

		fprintf(fl, "v%d -> v%d;\n", var->PrintMyNodeSerialNumber, var->u.subscript.var->PrintMyNodeSerialNumber);
		ABSYN_PrintVar(var->u.field.var);

		fprintf(fl, "v%d -> v%d;\n", var->PrintMyNodeSerialNumber, var->u.subscript.exp->PrintMyNodeSerialNumber);
		ABSYN_PrintTreeRecursively(var->u.subscript.exp);
		break;
	}
}

void ABSYN_PrintVarDec(A_dec dec)
{
	/*******************************/
	/* Print my serial node number */
	/*******************************/
	fprintf(fl,"v%d ",dec->PrintMyNodeSerialNumber);

	if (dec->u.var_dec.init == NULL)
	{
		/********************************************/
		/* VariableDeclaration ---> VAR ID COLON ID */
		/********************************************/
		fprintf(
			fl,
			"[label = \"%s%s : %s\"];\n",
			"Variable\nDeclaration\n",
			S_name(dec->u.var_dec.var_name),
			S_name(dec->u.var_dec.type_name));
		return;
	}

	if (dec->u.var_dec.type_name == NULL)
	{
		/**********************************************/
		/* VariableDeclaration ---> VAR ID ASSIGN exp */
		/**********************************************/
		fprintf(
			fl,
			"[label = \"%s(%s)\"];\n",
			"Variable\nDeclaration\n",
			S_name(dec->u.var_dec.var_name));

		fprintf(fl, "v%d -> v%d;\n", dec->PrintMyNodeSerialNumber, dec->u.var_dec.init->PrintMyNodeSerialNumber);
		ABSYN_PrintTreeRecursively(dec->u.var_dec.init);
		return;
	}

	/*******************************************************/
	/* VariableDeclaration ---> VAR ID COLON ID ASSIGN exp */
	/*******************************************************/
	fprintf(
		fl,
		"[label = \"%s(%s : %s)\"];\n",
		"Variable\nDeclaration\n\n",
		S_name(dec->u.var_dec.var_name),
		S_name(dec->u.var_dec.type_name));

	fprintf(fl, "v%d -> v%d;\n", dec->PrintMyNodeSerialNumber, dec->u.var_dec.init->PrintMyNodeSerialNumber);
	ABSYN_PrintTreeRecursively(dec->u.var_dec.init);
	return;
}

void ABSYN_PrintFieldsDecRecursively(A_fieldList fieldList)
{
	/*******************************/
	/* Print my serial node number */
	/*******************************/
	fprintf(fl,"v%d ",fieldList->PrintMyNodeSerialNumber);

	/*****************/
	/* Print content */
	/*****************/
	fprintf(fl,"[label = \"%s\"];\n",fieldList->PrintTheKindOfTreeIAm);

	/*********************/
	/* Print first field */
	/*********************/
	fprintf(fl,"v%d -> v%d;\n",fieldList->PrintMyNodeSerialNumber,fieldList->head->PrintMyNodeSerialNumber);

	/*********************/
	/* Print first field */
	/*********************/
	fprintf(fl,"v%d ",fieldList->head->PrintMyNodeSerialNumber);

	/*****************/
	/* Print content */
	/*****************/
	fprintf(fl,"[label = \"%s:%s\"];\n",S_name(fieldList->head->field_name),S_name(fieldList->head->field_type_name));

	/********************************/
	/* Print the rest of the fields */
	/********************************/
	if (fieldList->tail != NULL)
	{
		fprintf(fl,"v%d -> v%d;\n",fieldList->PrintMyNodeSerialNumber,fieldList->tail->PrintMyNodeSerialNumber);
		ABSYN_PrintFieldsDecRecursively(fieldList->tail);
	}
}
void ABSYN_PrintTypeDec(A_dec dec)
{
	switch (dec->u.type_dec.ty.kind) {
	case (A_nameTy):
		
		fprintf(
			fl,
			"[label = \"%s%s = %s\"];\n",
			"Name Type\nDeclaration\n\n",
			S_name(dec->u.type_dec.type_name),
			S_name(dec->u.type_dec.ty.u.name));
		break;

	case (A_arrayTy):
		
		fprintf(
			fl,
			"[label = \"%s%s =\n ARRAY OF %s\"];\n",
			"Type\nDeclaration\n\n",
			S_name(dec->u.type_dec.type_name),
			S_name(dec->u.type_dec.ty.u.array));
		break;

	case (A_recordTy):
		
		fprintf(
			fl,
			"[label = \"%s%s = \"];\n",
			"Record Type\nDeclaration\n\n",
			S_name(dec->u.type_dec.type_name));

		fprintf(fl, "v%d -> v%d;\n", dec->PrintMyNodeSerialNumber ,dec->u.type_dec.ty.u.record->PrintMyNodeSerialNumber);
		ABSYN_PrintFieldsDecRecursively(dec->u.type_dec.ty.u.record);
		break;
	}
}

void ABSYN_PrintFunDec(A_dec dec)
{
	/*****************/
	/* Print content */
	/*****************/
	fprintf(fl,"[label = \"%s(%s)\"];\n","Function\nDeclaration\n",S_name(dec->u.func_dec.name));
	
	/****************/
	/* Print params */
	/****************/
	fprintf(fl,"v%d -> v%d;\n",dec->PrintMyNodeSerialNumber,dec->u.func_dec.params->PrintMyNodeSerialNumber);
	ABSYN_PrintFieldsDecRecursively(dec->u.func_dec.params);

	/**************/
	/* Print body */
	/**************/
	fprintf(fl,"v%d -> v%d;\n",dec->PrintMyNodeSerialNumber,dec->u.func_dec.body->PrintMyNodeSerialNumber);
	ABSYN_PrintTreeRecursively(dec->u.func_dec.body);
}

void ABSYN_PrintDec(A_dec dec)
{
	/***********************************/
	/* [1] Print my serial node number */
	/***********************************/
	fprintf(fl,"v%d ",dec->PrintMyNodeSerialNumber);

	/*************************/
	/* [2] Print declaration */
	/*************************/
	switch (dec->kind) {
	case (A_varDec):      ABSYN_PrintVarDec( dec); break;
	case (A_typeDec):     ABSYN_PrintTypeDec(dec); break;
	case (A_functionDec): ABSYN_PrintFunDec( dec); break;
	}
}

void ABSYN_PrintDecList(A_decList declarationList)
{
	if (declarationList == NULL) return;

	fprintf(fl, "v%d [label = \"%s\"];\n", declarationList->PrintMyNodeSerialNumber, declarationList->PrintTheKindOfTreeIAm);

	fprintf(fl, "v%d -> v%d;\n", declarationList->PrintMyNodeSerialNumber, declarationList->head->PrintMyNodeSerialNumber);
	ABSYN_PrintDec(declarationList->head);

	if (declarationList->tail == NULL) return;

	fprintf(fl, "v%d -> v%d;\n", declarationList->PrintMyNodeSerialNumber, declarationList->tail->PrintMyNodeSerialNumber);
	ABSYN_PrintDecList(declarationList->tail);
}

void ABSYN_PrintExpList(A_expList expList)
{
	if (expList == NULL) return;

	fprintf(fl, "v%d [label = \"%s\"];\n", expList->PrintMyNodeSerialNumber, expList->PrintTheKindOfTreeIAm);

	fprintf(fl, "v%d -> v%d;\n", expList->PrintMyNodeSerialNumber, expList->head->PrintMyNodeSerialNumber);
	ABSYN_PrintTreeRecursively(expList->head);

	if (expList->tail == NULL) return;

	fprintf(fl, "v%d -> v%d;\n", expList->PrintMyNodeSerialNumber, expList->tail->PrintMyNodeSerialNumber);
	ABSYN_PrintExpList(expList->tail);
}

void ABSYN_PrintTreeRecursively(A_exp ABSYN_Tree)
{
	/*****************/
	/* [0] Oh well.. */
	/*****************/
	if (ABSYN_Tree == NULL) return;

	/***********************************/
	/* [1] Print my serial node number */
	/***********************************/
	fprintf(fl,"v%d ",ABSYN_Tree->PrintMyNodeSerialNumber);

	/***************************/
	/* [2] Print my node label */
	/***************************/
	fprintf(fl,"[label = \"%s\"];\n",ABSYN_Tree->PrintTheKindOfTreeIAm);

	/***********************************************/
	/* [3] Print the remaining subtree recursively */
	/***********************************************/
	switch (ABSYN_Tree->kind) {

	case (A_seqExp):

		fprintf(fl, "v%d -> v%d;\n", ABSYN_Tree->PrintMyNodeSerialNumber, ABSYN_Tree->u.seq->PrintMyNodeSerialNumber);
		ABSYN_PrintExpList(ABSYN_Tree->u.seq);
		break;

	case (A_callExp):

		fprintf(fl, "v%d -> v%d;\n", ABSYN_Tree->PrintMyNodeSerialNumber, ABSYN_Tree->u.call.args->PrintMyNodeSerialNumber);
		ABSYN_PrintExpList(ABSYN_Tree->u.call.args);
		break;

	case (A_opExp):

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.op.left->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.op.right->PrintMyNodeSerialNumber);

		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.op.left);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.op.right);
		break;

	case (A_ifExp):

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.iff.test->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.iff.then->PrintMyNodeSerialNumber);

		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.iff.test);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.iff.then);
		break;

	case (A_whileExp):

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.whilee.test->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.whilee.body->PrintMyNodeSerialNumber);

		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.whilee.test);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.whilee.body);
		break;

	case (A_forExp):

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.forr.lo->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.forr.hi->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.forr.body->PrintMyNodeSerialNumber);

		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.forr.lo);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.forr.hi);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.forr.body);
		break;

	case (A_letExp):

		fprintf(fl, "v%d -> v%d;\n", ABSYN_Tree->PrintMyNodeSerialNumber, ABSYN_Tree->u.let.decs->PrintMyNodeSerialNumber);
		ABSYN_PrintDecList(ABSYN_Tree->u.let.decs);

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.let.body->PrintMyNodeSerialNumber);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.let.body);
		break;

	case (A_assignExp):

		fprintf(fl, "v%d -> v%d;\n", ABSYN_Tree->PrintMyNodeSerialNumber, ABSYN_Tree->u.assign.var->PrintMyNodeSerialNumber);
		ABSYN_PrintVar(ABSYN_Tree->u.assign.var);
		fprintf(fl, "v%d -> v%d;\n", ABSYN_Tree->PrintMyNodeSerialNumber, ABSYN_Tree->u.assign.exp->PrintMyNodeSerialNumber);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.assign.exp);
		break;

	case (A_varExp):

		switch (ABSYN_Tree->u.var->kind) {
		case (A_simpleVar) :

			break;

		case (A_fieldVar) :

			fprintf(fl, "v%d -> v%d;\n", ABSYN_Tree->PrintMyNodeSerialNumber, ABSYN_Tree->u.var->u.field.var->PrintMyNodeSerialNumber);
			ABSYN_PrintVar(ABSYN_Tree->u.var->u.field.var);
			break;

		case (A_subscriptVar) :

			fprintf(fl, "v%d -> v%d;\n", ABSYN_Tree->PrintMyNodeSerialNumber, ABSYN_Tree->u.var->u.subscript.var->PrintMyNodeSerialNumber);
			ABSYN_PrintVar(ABSYN_Tree->u.var->u.subscript.var);

			fprintf(fl, "v%d -> v%d;\n", ABSYN_Tree->PrintMyNodeSerialNumber, ABSYN_Tree->u.var->u.subscript.exp->PrintMyNodeSerialNumber);
			ABSYN_PrintTreeRecursively(ABSYN_Tree->u.var->u.subscript.exp);
			break;

		}
		break;
	}
}

void ABSYN_PrintTreeInit(const char *filename)
{
	fl=fopen(filename,"w+t");
	if (fl == NULL) return;

	fprintf(fl,"digraph\n");
	fprintf(fl,"{\n");
	fprintf(fl,"graph [ordering = \"out\"]\n");
}

void ABSYN_PrintTreeEnd(void)
{
	fprintf(fl,"\n}");
	fclose(fl);
}

void ABSYN_PrintTree(A_exp ABSYN_tree,const char *filename)
{
	/************/
	/* [1] Init */
	/************/
	ABSYN_PrintTreeInit(filename);

	/******************************/
	/* [2] Print Tree Recursively */
	/******************************/
	ABSYN_PrintTreeRecursively(ABSYN_tree);

	/***********/
	/* [3] End */
	/***********/
	ABSYN_PrintTreeEnd();
}
