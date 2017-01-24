/***************************************/
/* FILE NAME: TEMPS_TO_REGS_errormsg.c */
/***************************************/

/****************************************/
/* WARNING DISABLE: sprintf - I love it */
/****************************************/
#pragma warning (disable: 4996)

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "util.h"
#include "TEMPS_TO_REGS_errormsg.h"

bool TEMPS_TO_REGS_anyErrors= FALSE;

static string TEMPS_TO_REGS_fileName = "";

static int TEMPS_TO_REGS_lineNum = 1;

int TEMPS_TO_REGS_EM_tokPos=0;

extern FILE *ggin;

typedef struct TEMPS_TO_REGS_intList {int i; struct TEMPS_TO_REGS_intList *rest;} *TEMPS_TO_REGS_IntList;

static TEMPS_TO_REGS_IntList TEMPS_TO_REGS_intList(int i, TEMPS_TO_REGS_IntList rest) 
{
	TEMPS_TO_REGS_IntList l= (TEMPS_TO_REGS_IntList) checked_malloc(sizeof *l);
	l->i=i; l->rest=rest;
	
	return l;
}

static TEMPS_TO_REGS_IntList TEMPS_TO_REGS_linePos=NULL;

void TEMPS_TO_REGS_EM_newline(void)
{
	TEMPS_TO_REGS_lineNum++;
	TEMPS_TO_REGS_linePos = TEMPS_TO_REGS_intList(TEMPS_TO_REGS_EM_tokPos, TEMPS_TO_REGS_linePos);
}

void TEMPS_TO_REGS_EM_error(int pos, char *message,...)
{
	va_list ap;
	TEMPS_TO_REGS_IntList lines = TEMPS_TO_REGS_linePos;
	int num=TEMPS_TO_REGS_lineNum;

	TEMPS_TO_REGS_anyErrors=TRUE;
	while (lines && lines->i >= pos) 
	{
		lines=lines->rest;
		num--;
	}

	if (TEMPS_TO_REGS_fileName)
	{
		fprintf(stderr,"%s:",TEMPS_TO_REGS_fileName);
	}
	
	if (lines)
	{
		fprintf(stderr,"%d.%d: ", num, pos-lines->i);
	}
	
	va_start(ap,message);
	vfprintf(stderr, message, ap);
	va_end(ap);
	fprintf(stderr,"\n");

	/*********************************/
	/* [0] exit at the first mistake */
	/*********************************/
	exit(0);
}

void TEMPS_TO_REGS_EM_reset(string fname)
{
	TEMPS_TO_REGS_anyErrors=FALSE;
	TEMPS_TO_REGS_fileName=fname;
	TEMPS_TO_REGS_lineNum=1;
	TEMPS_TO_REGS_linePos=TEMPS_TO_REGS_intList(0,NULL);
	ggin = fopen(fname,"r");
	if (!ggin)
	{
		TEMPS_TO_REGS_EM_error(0,"cannot open");
		exit(1);
	}
}

