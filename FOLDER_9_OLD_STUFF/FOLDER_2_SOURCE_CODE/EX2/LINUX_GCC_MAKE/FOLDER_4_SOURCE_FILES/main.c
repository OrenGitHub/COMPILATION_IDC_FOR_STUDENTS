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
	if (argc != 5)
	{
		printf("%d",argc);
		fprintf(stderr,"usage: a.out filename\n");
	}
}

int main(int argc, char **argv)
{
	string RowOperations_Filename=argv[1];
	string SolutionSet_Filename  =argv[2];
	string RowOperationsOutput   =argv[3];
	string SolutionSetOutput     =argv[4];
	
	usage(argc,argv);
	
	RowOperations_ErrorMsg_Set_Log_Filename(RowOperationsOutput);
	SolutionSet_ErrorMsg_Set_Log_Filename(SolutionSetOutput);
	
	RowOperations_ErrorMsg_Reset(RowOperations_Filename);
	SolutionSet_ErrorMsg_Reset(SolutionSet_Filename);

	printf("\n\n");
	
	while (bblex());
	while (cclex());
		
	return 0;
}

