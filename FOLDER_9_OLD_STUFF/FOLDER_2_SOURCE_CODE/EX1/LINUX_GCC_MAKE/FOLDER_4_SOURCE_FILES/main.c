/***********************/
/* FILE NAME: driver.c */
/***********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "util.h"
#include "MatReader_ErrorMsg.h"
#include "RowOperations_ErrorMsg.h"
#include "SolutionSet_ErrorMsg.h"

int aalex(void);
int bblex(void);
int cclex(void);

/*****************/
/* START OF CODE */
/*****************/
void usage(int argc, char **argv)
{
	if (argc != 7)
	{
		fprintf(stderr,"usage: a.out filename\n");
		return 0;
	}
}

int main(int argc, char **argv)
{
	string MatReader_Filename    =argv[1];
	string RowOperations_Filename=argv[2];
	string SolutionSet_Filename  =argv[3];
	string MatReaderOutput       =argv[4];
	string RowOperationsOutput   =argv[5];
	string SolutionSetOutput     =argv[6];
	
	usage(argc,argv);
	
	MatReader_ErrorMsg_Set_Log_Filename(MatReaderOutput);
	RowOperations_ErrorMsg_Set_Log_Filename(RowOperationsOutput);
	SolutionSet_ErrorMsg_Set_Log_Filename(SolutionSetOutput);
	
	MatReader_ErrorMsg_Reset(MatReader_Filename);
	RowOperations_ErrorMsg_Reset(RowOperations_Filename);
	SolutionSet_ErrorMsg_Reset(SolutionSet_Filename);

	printf("\n\n");
	
	while (aalex());
	while (bblex());
	while (cclex());
		
	return 0;
}

