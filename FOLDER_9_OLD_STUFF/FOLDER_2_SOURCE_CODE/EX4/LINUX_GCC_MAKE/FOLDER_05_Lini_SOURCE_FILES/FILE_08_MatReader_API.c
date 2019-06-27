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
#include "FILE_03_Matrix.h"
#include "FILE_04_MatReader_ErrorMsg.h"
#include "FILE_07_MatReader_AST.h"
#include "FILE_08_MatReader_API.h"

/**********************/
/* Parse Input Matrix */
/**********************/
Matrix Parse_Input_Matrix(string Matrix_Filename)
{
	/*************************/
	/* Open file for parsing */
	/*************************/
	MatReader_ErrorMsg_Reset(Matrix_Filename);

	/*******************************/
	/* 3 ... 2 ... 1 ... parse !!! */
	/*******************************/
	if (aaparse() == 0)
	{
		/******************/
		/* parsing worked */
		/******************/
		return MatReader_AST_ROOT;
	}
	else
	{
		/******************/
		/* parsing failed */
		/******************/
		return NULL;
	}
}

