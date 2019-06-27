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
#include "FILE_09_RowOperations_ErrorMsg.h"
#include "FILE_12_RowOperations_AST.h"
#include "FILE_11_RowOperations_Parser.h"

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
/* INDEX */
/*********/
INDEX		[1-4]

/*******/
/* ROW */
/*******/
ROW			"R"{INDEX}
	
/*********/
/* RULES */
/*********/
%%
{WHITE_SPACE}		{adjust(); continue;}
{LINE_TERMINATOR}	{adjust(); RowOperations_ErrorMsg_Newline(); continue;}
{PLUS}				{adjust(); RowOperations_ErrorMsg_Log("+");  return PLUS;}
{MINUS}				{adjust(); RowOperations_ErrorMsg_Log("-");  return MINUS;}
{ROW}				{
						adjust();
						bblval.gval.row=atoi(bbtext);
						RowOperations_ErrorMsg_Log("R%d",bblval.gval.row);
						return ROW;
					}
{INT}				{
						adjust();
						bblval.gval.ival=atoi(bbtext);
						RowOperations_ErrorMsg_Log("INT(%d)",bblval.gval.ival);
						return INT;
					}
%%
