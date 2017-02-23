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
#include "Calc_ErrorMsg.h"
#include "Calc_Tokens.h"
#include "util.h"

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
static int charPos=1;

/******************/
/* PROVIDE ZZWRAP */
/******************/
int zzwrap(void)
{
	charPos=1;
	return 1;
}

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
void adjust(void)
{
	Calc_ErrorMsg_tokPos = charPos;
	charPos += zzleng;
}

%}

/*****************/
/* UNIQUE PREFIX */
/*****************/
%option prefix="zz"

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
DIGIT			[0-9]
NON_ZERO_DIGIT	[1-9]
LETTER			[a-zA-Z_]
INT				"0"|({NON_ZERO_DIGIT}({DIGIT}*))|"-"{DIGIT}
		
/*********/
/* RULES */
/*********/
%%
{WHITE_SPACE}		{adjust(); continue;}
{LINE_TERMINATOR}	{adjust(); Calc_ErrorMsg_Newline(); continue;}
{LPAREN}			{adjust(); Calc_ErrorMsg_Log("("); return LPAREN;}
{RPAREN}			{adjust(); Calc_ErrorMsg_Log(")"); return RPAREN;}
{PLUS}				{adjust(); Calc_ErrorMsg_Log("+"); return PLUS;}
{MINUS}				{adjust(); Calc_ErrorMsg_Log("-"); return MINUS;}
{TIMES}				{adjust(); Calc_ErrorMsg_Log("*"); return TIMES;}
{DIVIDE}			{adjust(); Calc_ErrorMsg_Log("/"); return DIVIDE;}
{INT}				{
						adjust();
						zzlval.gval.ival=atoi(zztext);
						Calc_ErrorMsg_Log("INT(%d)",zzlval.gval.ival);
						return INT;
					}

