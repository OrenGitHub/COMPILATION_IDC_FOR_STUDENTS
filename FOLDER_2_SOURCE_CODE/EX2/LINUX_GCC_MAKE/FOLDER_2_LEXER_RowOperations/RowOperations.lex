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
#include "RowOperations_ErrorMsg.h"
#include "RowOperations_Tokens.h"
#include "util.h"

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
static int charPos=1;

/******************/
/* PROVIDE bbwrap */
/******************/
int bbwrap(void)
{
	charPos=1;
	return 1;
}

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
static void adjust(void)
{
	RowOperations_ErrorMsg_tokPos = charPos;
	charPos += bbleng;
}

/***********/
/* YYSTYPE */
/***********/
YYSTYPE bblval;

%}

/*****************/
/* UNIQUE PREFIX */
/*****************/
%option prefix="bb"

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

/**********/
/* BINOPS */
/**********/
PLUS	"+"
MINUS	"-"
TIMES	"*"
DIVIDE	"/"

/*******/
/* INT */
/*******/
INT			[0-9]+
		
/*********/
/* RULES */
/*********/
%%
{WHITE_SPACE}		{adjust(); continue;}
{LINE_TERMINATOR}	{adjust(); RowOperations_ErrorMsg_Newline(); continue;}
{PLUS}				{adjust(); RowOperations_ErrorMsg_Log("+");  return PLUS;}
{MINUS}				{adjust(); RowOperations_ErrorMsg_Log("-");  return MINUS;}
{INT}				{
						adjust();
						bblval.gval.ival=atoi(bbtext);
						RowOperations_ErrorMsg_Log("INT(%d)",bblval.gval.ival);
						return INT;
					}

