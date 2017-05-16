%{
/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_14_SolutionSet_ErrorMsg.h"
#include "FILE_17_SolutionSet_AST.h"

/**********/
/* ALLOCA */
/**********/
#define alloca malloc

/*******************/
/* LEXING FUNCTION */
/*******************/
int cclex(void);

/******************/
/* ERROR FUNCTION */
/******************/
void ccerror(char *s)
{
	SolutionSet_ErrorMsg_Error(SolutionSet_ErrorMsg_tokPos,"%s",s);
}

/************/
/* AST ROOT */
/************/
int SolutionSet_AST_ROOT;

%}

/********************************************************************************/
/* This union is a C replacement for an abstract class representing an AST node */
/********************************************************************************/
%union
{
	union
	{
		int			ival;
		float		fval;
		string		sval;
	}
	gval;
}

/*************/
/* TERMINALS */
/*************/
%token <gval> INT
%token <gval> LPAREN
%token <gval> RPAREN
%token <gval> LBRACE
%token <gval> RBRACE
%token <gval> COMMA
%token <gval> DIVIDE

/*****************/
/* NON TERMINALS */
/*****************/
%type <gval> program
%type <gval> solutionSet

/**************/
/* START HERE */
/**************/
%start program

%%

program:		solutionSet					{SolutionSet_AST_ROOT = 100;}

solutionSet:	INT INT						{printf("solutionSet --> singleVecSet");}

%%
