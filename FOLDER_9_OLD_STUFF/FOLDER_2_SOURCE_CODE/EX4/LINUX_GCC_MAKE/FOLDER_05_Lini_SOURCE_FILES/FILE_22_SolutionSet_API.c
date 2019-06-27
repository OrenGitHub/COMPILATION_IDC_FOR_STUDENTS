/*****************************/
/* FILE_22_SolutionSet_API.c */
/*****************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_14_SolutionSet_ErrorMsg.h"
#include "FILE_17_SolutionSet_AST.h"
#include "FILE_18_SolutionSet_API.h"

/**********************/
/* Parse Solution Set */
/**********************/
int Parse_SolutionSet(string SolutionSet_Filename)
{
	/*************************/
	/* Open file for parsing */
	/*************************/
	SolutionSet_ErrorMsg_Reset(SolutionSet_Filename);
	
	/*******************************/
	/* 3 ... 2 ... 1 ... parse !!! */
	/*******************************/
	if (ccparse() == 0)
	{
		/******************/
		/* parsing worked */
		/******************/
		return SolutionSet_AST_ROOT;
	}
	else
	{
		/******************/
		/* parsing failed */
		/******************/
		return NULL;
	}
}

