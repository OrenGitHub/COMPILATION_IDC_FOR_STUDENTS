/*********************/
/* FILE NAME: main.c */
/*********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_08_MatReader_API.h"
#include "FILE_13_RowOperations_API.h"
#include "FILE_18_SolutionSet_API.h"

/********/
/* main */
/********/
int main(int argc,char **argv)
{
	AST_RowOpList AST_RowOperations;
	
	/***********************/
	/* [0] Initializations */
	/***********************/
	string RowOperations_Filename=argv[1];
	string CheckSummary_Filename =argv[2];

	/****************************/
	/* [1] Parse Row Operations */
	/****************************/
	AST_RowOperations = Parse_RowOperations(RowOperations_Filename);

	/************************************************/
	/* [2] Scan the AST Row Operations semantically */
	/************************************************/
	Semantic_Analysis_RowOperations(AST_RowOperations);
}

