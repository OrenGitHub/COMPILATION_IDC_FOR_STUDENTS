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
	/***********************/
	/* [0] Initializations */
	/***********************/
	string SolutionSet_Filename=argv[1];
	string CheckSummary_Filename =argv[2];

	/**************************/
	/* [1] Dummy LEX LOG file */
	/**************************/
	SolutionSet_ErrorMsg_Set_Log_Filename("DUMMY_SOLUTION_SET_LOG_FILE.txt");

	/**************************/
	/* [2] Parse Solution Set */
	/**************************/
	Parse_SolutionSet(SolutionSet_Filename);

	/**********************************************/
	/* [2] Scan the AST Solution Set semantically */
	/**********************************************/
	// Semantic_Analysis_SolutionSet(AST_SolutionSet);
	
	return 0;
}

