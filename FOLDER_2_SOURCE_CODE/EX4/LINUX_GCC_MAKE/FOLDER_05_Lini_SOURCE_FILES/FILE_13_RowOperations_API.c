/***************************/
/* FILE_06_MatReader_API.c */
/***************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_09_RowOperations_ErrorMsg.h"
#include "FILE_12_RowOperations_AST.h"
#include "FILE_13_RowOperations_API.h"

/**********************/
/* Parse Input Matrix */
/**********************/
AST_RowOpList Parse_Row_Operations(string RowOperations_Filename)
{
	/*************************/
	/* Open file for parsing */
	/*************************/
	RowOperations_ErrorMsg_Reset(RowOperations_Filename);

	/*******************************/
	/* 3 ... 2 ... 1 ... parse !!! */
	/*******************************/
	if (bbparse() == 0)
	{
		/******************/
		/* parsing worked */
		/******************/
		return RowOperations_AST_ROOT;
	}
	else
	{
		/******************/
		/* parsing failed */
		/******************/
		return NULL;
	}
}

