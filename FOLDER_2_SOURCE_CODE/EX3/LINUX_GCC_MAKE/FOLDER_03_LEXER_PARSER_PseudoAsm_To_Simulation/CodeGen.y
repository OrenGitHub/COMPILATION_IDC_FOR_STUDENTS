%{
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "PSEUDO_MIPS_ASM_AST_errormsg.h"
#include "PSEUDO_MIPS_ASM_AST.h"

#define alloca malloc

#define yyparse zzparse
#define yylex zzlex
#define yyerror zzerror
#define yylval zzlval
#define yychar zzchar
#define yydebug zzdebug
#define yynerrs zznerrs

int zzlex(void); /* function prototype */

PSEUDO_MIPS_ASM_AST_expList PSEUDO_MIPS_ASM_AST_root;

void zzerror(char *s)
{
	PSEUDO_MIPS_ASM_AST_EM_error(PSEUDO_MIPS_ASM_AST_EM_tokPos, "%s", s);
}
%}

%union
{
	union
	{
		int								ival;
		int								temp_serial_number;
		float							fval;
		string							sval;
		string							register_name;
		PSEUDO_MIPS_ASM_AST_Var			var;
		PSEUDO_MIPS_ASM_AST_Label_Type_	label;
		PSEUDO_MIPS_ASM_AST_exp			exp;
		PSEUDO_MIPS_ASM_AST_expList		expList;
	}
	gval;
}

%token <gval> INT
%token <gval> FLOAT
%token <gval> STRING
%token <gval> PRINT_INT
%token <gval> PRINT_CHAR
%token <gval> ALLOCATE
%token <gval> EXIT
%token <gval> ID
%token <gval> LABEL
%token <gval> COMMA
%token <gval> COLON
%token <gval> LOAD
%token <gval> STORE
%token <gval> LOAD_IMMEDIATE
%token <gval> ADD_IMMEDIATE
%token <gval> JUMP
%token <gval> JUMP_AND_LINK
%token <gval> LPAREN
%token <gval> RPAREN
%token <gval> PLUS
%token <gval> MINUS
%token <gval> ADD
%token <gval> SUB
%token <gval> MUL
%token <gval> DIV
%token <gval> TEMP
%token <gval> BEQ
%token <gval> BNE
%token <gval> BLT
%token <gval> BLE
%token <gval> BGT
%token <gval> BGE
%token <gval> REGISTER
%token <gval> AND
%token <gval> OR
%token <gval> MOVE

%type <gval> exp
%type <gval> expList
%type <gval> labelExp
%type <gval> jumpExp	
%type <gval> cjumpExp	
%type <gval> loadExp	
%type <gval> storeExp	
%type <gval> binopExp	
%type <gval> movExp	
%type <gval> var
%type <gval> program

%start program

%%

program:				expList										{PSEUDO_MIPS_ASM_AST_root = $1.expList;}

expList:				exp	expList									{$$.expList = PSEUDO_MIPS_ASM_AST_ExpList($1.exp,$2.expList);}
						| exp										{$$.expList = PSEUDO_MIPS_ASM_AST_ExpList($1.exp,NULL);}

exp:					labelExp									{$$.exp = $1.exp;}
						| jumpExp									{$$.exp = $1.exp;}
						| cjumpExp									{$$.exp = $1.exp;}
						| loadExp									{$$.exp = $1.exp;}
						| storeExp									{$$.exp = $1.exp;}
						| binopExp									{$$.exp = $1.exp;}
						| movExp									{$$.exp = $1.exp;}
						| PRINT_INT									{$$.exp = PSEUDO_MIPS_ASM_AST_PRINT_INT();}
						| PRINT_CHAR								{$$.exp = PSEUDO_MIPS_ASM_AST_PRINT_CHAR();}
						| ALLOCATE									{$$.exp = PSEUDO_MIPS_ASM_AST_ALLOCATE();}
						| EXIT										{$$.exp = PSEUDO_MIPS_ASM_AST_EXIT();}

labelExp:				LABEL COLON									{$$.exp = PSEUDO_MIPS_ASM_AST_LABEL($1.label);}

jumpExp:				JUMP LABEL									{$$.exp = PSEUDO_MIPS_ASM_AST_JUMP_LABEL($2.label);}
						| JUMP REGISTER								{$$.exp = PSEUDO_MIPS_ASM_AST_JUMP_REGISTER($2.sval);}
						| JUMP_AND_LINK LABEL						{$$.exp = PSEUDO_MIPS_ASM_AST_JUMP_AND_LINK($2.label.name);}

cjumpExp:				BEQ var COMMA var COMMA LABEL				{$$.exp = PSEUDO_MIPS_ASM_AST_BEQ( $2.var,$4.var,$6.label );}
						| BNE var COMMA var COMMA LABEL				{$$.exp = PSEUDO_MIPS_ASM_AST_BNE( $2.var,$4.var,$6.label );}
						| BGT var COMMA var COMMA LABEL				{$$.exp = PSEUDO_MIPS_ASM_AST_BGT( $2.var,$4.var,$6.label );}
						| BLT var COMMA var COMMA LABEL				{$$.exp = PSEUDO_MIPS_ASM_AST_BLT( $2.var,$4.var,$6.label );}
						| BGE var COMMA var COMMA LABEL				{$$.exp = PSEUDO_MIPS_ASM_AST_BGE( $2.var,$4.var,$6.label );}
						| BLE var COMMA var COMMA LABEL				{$$.exp = PSEUDO_MIPS_ASM_AST_BLE( $2.var,$4.var,$6.label );}

loadExp:				LOAD var COMMA INT LPAREN var RPAREN		{$$.exp = PSEUDO_MIPS_ASM_AST_LOAD($2.var,$6.var,$4.ival);}
						| LOAD_IMMEDIATE var COMMA INT				{$$.exp = PSEUDO_MIPS_ASM_AST_LOAD_IMMEDIATE($2.var,$4.ival);}

storeExp:				STORE var COMMA INT LPAREN var RPAREN		{$$.exp = PSEUDO_MIPS_ASM_AST_STORE($2.var,$6.var,$4.ival);}

binopExp:				ADD var COMMA var COMMA var					{$$.exp = PSEUDO_MIPS_ASM_AST_ADD($2.var,$4.var,$6.var);}
						| SUB var COMMA var COMMA var				{$$.exp = PSEUDO_MIPS_ASM_AST_SUB($2.var,$4.var,$6.var);}
						| MUL var COMMA var COMMA var				{$$.exp = PSEUDO_MIPS_ASM_AST_MUL($2.var,$4.var,$6.var);}
						| DIV var COMMA var COMMA var				{$$.exp = PSEUDO_MIPS_ASM_AST_DIV($2.var,$4.var,$6.var);}
						| ADD_IMMEDIATE var COMMA var COMMA INT		{$$.exp = PSEUDO_MIPS_ASM_AST_ADD_IMMEDIATE($2.var,$4.var,$6.ival);}

movExp:					MOVE var COMMA var							{$$.exp = PSEUDO_MIPS_ASM_AST_MOVE($2.var,$4.var);}

var:					TEMP										{$$.var = PSEUDO_MIPS_ASM_AST_TEMP_VAR($1.temp_serial_number);}
						| REGISTER									{$$.var = PSEUDO_MIPS_ASM_AST_REGISTER_VAR($1.register_name);}

%%

	
