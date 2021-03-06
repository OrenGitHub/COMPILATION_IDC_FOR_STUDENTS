%{
/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_14_SolutionSet_ErrorMsg.h"
#include "FILE_17_SolutionSet_AST.h"
#include "FILE_18_SolutionSet_Parser.h"

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
static int charPos=1;

/******************/
/* PROVIDE ccWRAP */
/******************/
int ccwrap(void)
{
	charPos=1;
	return 1;
}

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
static void adjust(void)
{
	SolutionSet_ErrorMsg_tokPos = charPos;
	charPos += ccleng;
}

%}

/*****************/
/* UNIQUE PREFIX */
/*****************/
%option prefix="cc"

/********************/
/* COMMON REGEXP(s) */
/********************/

/**********/
/* SPACES */
/**********/
WHITE_SPACE		" "|\t
LINE_TERMINATOR	\n

/***************/
/* PARENTHESES */
/***************/
LPAREN	"("
RPAREN	")"
LBRACE	"{"
RBRACE	"}"

/**********/
/* BINOPS */
/**********/
PLUS	"+"
DIVIDE	"/"

/*******/
/* INT */
/*******/
INT				[0-9]+
SPAN			"SP"
COMMA			","
		
/*********/
/* RULES */
/*********/
%%
{WHITE_SPACE}		{adjust(); continue;}
{LINE_TERMINATOR}	{adjust(); SolutionSet_ErrorMsg_Newline(); continue;}
{LPAREN}			{adjust(); SolutionSet_ErrorMsg_Log("(");  return LPAREN;}
{RPAREN}			{adjust(); SolutionSet_ErrorMsg_Log(")");  return RPAREN;}
{LBRACE}			{adjust(); SolutionSet_ErrorMsg_Log("{");  return LBRACE;}
{RBRACE}			{adjust(); SolutionSet_ErrorMsg_Log("}");  return RBRACE;}
{INT}				{
						adjust();
						cclval.gval.ival=atoi(cctext);
						SolutionSet_ErrorMsg_Log("INT(%d) ",cclval.gval.ival);
						return INT;
					}
%%
