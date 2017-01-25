%{
/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_22_RegAlloc_ErrorMsg.h"
/* #include "FILE_24_RegAlloc_Parser.h" */

#define alloca malloc

#define yyparse ggparse
#define yylex gglex
#define yyerror ggerror
#define yylval gglval
#define yychar ggchar
#define yydebug ggdebug
#define yynerrs ggnerrs

int gglex(void); /* function prototype */

void ggerror(char *s)
{
	TEMPS_TO_REGS_EM_error(TEMPS_TO_REGS_EM_tokPos, "%s", s);
}
%}

%union
{
	union
	{
		int		temp_serial_number;
		string	sval;
	}
	gval;
}

%token <gval> TEMP
%token <gval> SPACE
%token <gval> TAB
%token <gval> NEWLINE
%token <gval> COMMA
%token <gval> LPAREN
%token <gval> RPAREN
%token <gval> ANY_OTHER_THING

%type <gval> program

%start program

%%

program:	TEMP

%%

	
