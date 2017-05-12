/************************************************/
/* FILE NAEM: FILE_13_RowOperations_AST_Print.c */
/************************************************/

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

/********************/
/* GLOBAL VARIABLES */
/********************/
static FILE *fl;

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
void RowOperations_AST_Print_Recursive(A_exp ABSYN_Tree);

void RowOperations_AST_Print_Init(const char *filename)
{
	fl=fopen(filename,"w+t");
	if (fl == NULL) return;

	fprintf(fl,"digraph\n");
	fprintf(fl,"{\n");
	fprintf(fl,"graph [ordering = \"out\"]\n");
}

void RowOperations_AST_Print_Finalize(void)
{
	fprintf(fl,"\n}");
	fclose(fl);
}

void RowOperations_AST_Print(AST_RowOpList AST,const char *filename)
{
	/************/
	/* [1] Init */
	/************/
	RowOperations_AST_Print_Init(filename);

	/******************************/
	/* [2] Print Tree Recursively */
	/******************************/
	RowOperations_AST_Print_Recursive(ABSYN_tree);

	/***********/
	/* [3] End */
	/***********/
	RowOperations_AST_Print_Finalize();
}
