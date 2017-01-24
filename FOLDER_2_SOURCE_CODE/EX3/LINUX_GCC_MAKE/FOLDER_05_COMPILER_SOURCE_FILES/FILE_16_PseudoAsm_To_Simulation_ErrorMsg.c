/*****************************************/
/* FILE NAME: PSEUDO_MIPS_ASM_AST_errormsg.c */
/*****************************************/

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
#include "PSEUDO_MIPS_ASM_AST_errormsg.h"

bool PSEUDO_MIPS_ASM_AST_anyErrors= FALSE;

static string PSEUDO_MIPS_ASM_AST_fileName = "";

static int PSEUDO_MIPS_ASM_AST_lineNum = 1;

int PSEUDO_MIPS_ASM_AST_EM_tokPos=0;

extern FILE *zzin;

typedef struct PSEUDO_MIPS_ASM_AST_intList {int i; struct PSEUDO_MIPS_ASM_AST_intList *rest;} *PSEUDO_MIPS_ASM_AST_IntList;

static PSEUDO_MIPS_ASM_AST_IntList PSEUDO_MIPS_ASM_AST_intList(int i, PSEUDO_MIPS_ASM_AST_IntList rest) 
{
	PSEUDO_MIPS_ASM_AST_IntList l= (PSEUDO_MIPS_ASM_AST_IntList) checked_malloc(sizeof *l);
	l->i=i; l->rest=rest;
	
	return l;
}

static PSEUDO_MIPS_ASM_AST_IntList PSEUDO_MIPS_ASM_AST_linePos=NULL;

void PSEUDO_MIPS_ASM_AST_EM_newline(void)
{
	PSEUDO_MIPS_ASM_AST_lineNum++;
	PSEUDO_MIPS_ASM_AST_linePos = PSEUDO_MIPS_ASM_AST_intList(PSEUDO_MIPS_ASM_AST_EM_tokPos, PSEUDO_MIPS_ASM_AST_linePos);
}

void PSEUDO_MIPS_ASM_AST_EM_error(int pos, char *message,...)
{
	va_list ap;
	PSEUDO_MIPS_ASM_AST_IntList lines = PSEUDO_MIPS_ASM_AST_linePos;
	int num=PSEUDO_MIPS_ASM_AST_lineNum;

	PSEUDO_MIPS_ASM_AST_anyErrors=TRUE;
	while (lines && lines->i >= pos) 
	{
		lines=lines->rest;
		num--;
	}

	if (PSEUDO_MIPS_ASM_AST_fileName)
	{
		fprintf(stderr,"%s:",PSEUDO_MIPS_ASM_AST_fileName);
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

void PSEUDO_MIPS_ASM_AST_EM_reset(string fname)
{
	PSEUDO_MIPS_ASM_AST_anyErrors=FALSE;
	PSEUDO_MIPS_ASM_AST_fileName=fname;
	PSEUDO_MIPS_ASM_AST_lineNum=1;
	PSEUDO_MIPS_ASM_AST_linePos=PSEUDO_MIPS_ASM_AST_intList(0,NULL);
	zzin = fopen(fname,"r");
	if (!zzin)
	{
		PSEUDO_MIPS_ASM_AST_EM_error(0,"cannot open");
		exit(1);
	}
}

