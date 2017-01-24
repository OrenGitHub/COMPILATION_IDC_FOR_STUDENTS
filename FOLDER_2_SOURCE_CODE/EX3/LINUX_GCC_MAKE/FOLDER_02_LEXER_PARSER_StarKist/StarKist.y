%{
/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "util.h"
#include "errormsg.h"
#include "symbol.h" 
#include "absyn.h"

#define alloca malloc

int yylex(void); /* function prototype */

A_exp absyn_root;

void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
}
%}


%union
{
	union
	{
		int			ival;
		float		fval;
		string		sval;
		A_var		var;
		A_exp		exp;
		A_dec		dec;
		A_decList	decList;
		A_expList	expList;
		A_fieldList	fieldList;
	}
	gval;
}

%token <gval> INT
%token <gval> FLOAT
%token <gval> STRING
%token <gval> ID
%token <gval> COMMA
%token <gval> COLON
%token <gval> SEMICOLON
%token <gval> LPAREN
%token <gval> RPAREN
%token <gval> LBRACK
%token <gval> RBRACK
%token <gval> LBRACE
%token <gval> RBRACE
%token <gval> ARROW
%token <gval> PLUS
%token <gval> MINUS
%token <gval> TIMES
%token <gval> DIVIDE
%token <gval> EQ
%token <gval> NEQ
%token <gval> LT
%token <gval> LE
%token <gval> GT
%token <gval> GE
%token <gval> AND
%token <gval> OR
%token <gval> ASSIGN
%token <gval> ARRAY
%token <gval> IF
%token <gval> THEN
%token <gval> ELSE
%token <gval> WHILE
%token <gval> FOR
%token <gval> TO
%token <gval> DO
%token <gval> LET
%token <gval> IN
%token <gval> END
%token <gval> OF 
%token <gval> BREAK
%token <gval> NIL
%token <gval> FUNCTION
%token <gval> VAR
%token <gval> TYPE 

%type <gval> exp
%type <gval> OpExp
%type <gval> CallExp
%type <gval> IfThenExp
%type <gval> ForExp
%type <gval> ListExpComma
%type <gval> ListExpSemicolon
%type <gval> variable
%type <gval> AssignExp
%type <gval> SequenceExp
%type <gval> LetExp
%type <gval> TypeFields
%type <gval> TypeDeclaration
%type <gval> VariableDeclaration
%type <gval> FunctionDeclaration
%type <gval> AllocateArrayExp
%type <gval> AllocateRecordExp
%type <gval> declaration
%type <gval> declarations
%type <gval> program

%left DO
%left THEN
%left ASSIGN
%left OR AND
%left EQ NEQ LT GT LE GE
%left PLUS MINUS
%left TIMES DIVIDE

%start program

%%

program:				exp														{absyn_root = $1.exp;}

exp:					INT														{$$.exp = A_IntExp(EM_tokPos,$1.ival);}
						| FLOAT													{$$.exp = A_FloatExp(EM_tokPos,$1.fval);}
						| STRING												{$$.exp = A_StringExp(EM_tokPos,$1.sval);}
						| variable												{$$.exp = A_VarExp(EM_tokPos,$1.var);}
						| SequenceExp											{$$.exp = $1.exp;}
						| LPAREN exp RPAREN										{$$.exp = $2.exp;}
						| LetExp												{$$.exp = $1.exp;}
						| ForExp												{$$.exp = $1.exp;}
						| IfThenExp												{$$.exp = $1.exp;}
						| AssignExp												{$$.exp = $1.exp;}
						| OpExp													{$$.exp = $1.exp;}
						| CallExp												{$$.exp = $1.exp;}
						| NIL													{$$.exp = A_NilExp(EM_tokPos);}									

OpExp:					exp		PLUS	exp										{$$.exp = A_OpExp(EM_tokPos, A_plusOp,   $1.exp, $3.exp);}
						| exp	MINUS	exp										{$$.exp = A_OpExp(EM_tokPos, A_minusOp,  $1.exp, $3.exp);}
						| exp	TIMES	exp										{$$.exp = A_OpExp(EM_tokPos, A_timesOp,  $1.exp, $3.exp);}
						| exp	DIVIDE	exp										{$$.exp = A_OpExp(EM_tokPos, A_divideOp, $1.exp, $3.exp);}
						| exp	EQ		exp										{$$.exp = A_OpExp(EM_tokPos, A_eqOp,     $1.exp, $3.exp);}
						| exp	NEQ		exp										{$$.exp = A_OpExp(EM_tokPos, A_neqOp,    $1.exp, $3.exp);}
						| exp	LT		exp										{$$.exp = A_OpExp(EM_tokPos, A_ltOp,     $1.exp, $3.exp);}
						| exp	LE		exp										{$$.exp = A_OpExp(EM_tokPos, A_leOp,     $1.exp, $3.exp);}
						| exp	GT		exp										{$$.exp = A_OpExp(EM_tokPos, A_gtOp,     $1.exp, $3.exp);}
						| exp	GE		exp										{$$.exp = A_OpExp(EM_tokPos, A_geOp,     $1.exp, $3.exp);}
						| exp	AND		exp										{$$.exp = A_OpExp(EM_tokPos, A_andOp,    $1.exp, $3.exp);}
						| exp	OR		exp										{$$.exp = A_OpExp(EM_tokPos, A_orOp,     $1.exp, $3.exp);}

IfThenExp:				IF exp THEN exp											{$$.exp = A_IfExp(EM_tokPos,$2.exp,$4.exp,NULL);}

ForExp:					FOR ID ASSIGN exp TO exp DO exp							{$$.exp = A_ForExp(EM_tokPos,S_Symbol($2.sval),$4.exp,$6.exp,$8.exp);}

ListExpSemicolon:		exp SEMICOLON ListExpSemicolon							{$$.expList = A_ExpList($1.exp,$3.expList);}
						| exp SEMICOLON exp										{$$.expList = A_ExpList($1.exp,A_ExpList($3.exp,NULL));}

ListExpComma:			exp COMMA ListExpComma									{$$.expList = A_ExpList($1.exp,$3.expList);}
						| exp													{$$.expList = A_ExpList($1.exp,NULL);}

SequenceExp:			LPAREN ListExpSemicolon RPAREN							{$$.exp = A_SeqExp(EM_tokPos,$2.expList);}

TypeFields:				ID COLON ID COMMA TypeFields							{$$.fieldList = A_FieldList(A_Field(EM_tokPos,S_Symbol($1.sval),S_Symbol($3.sval)),$5.fieldList);}
						| ID COLON ID											{$$.fieldList = A_FieldList(A_Field(EM_tokPos,S_Symbol($1.sval),S_Symbol($3.sval)),NULL);}

TypeDeclaration:		TYPE ID EQ ID											{$$.dec = A_NameTypeDec(  EM_tokPos,S_Symbol($2.sval),S_Symbol($4.sval));}
						| TYPE ID EQ ARRAY OF ID								{$$.dec = A_ArrayTypeDec( EM_tokPos,S_Symbol($2.sval),S_Symbol($6.sval));}
						| TYPE ID EQ LBRACE TypeFields RBRACE					{$$.dec = A_RecordTypeDec(EM_tokPos,S_Symbol($2.sval),$5.fieldList);}

AllocateArrayExp:		ID LBRACK INT RBRACK OF NIL								{$$.exp = A_AllocateArrayExp(EM_tokPos,S_Symbol($1.sval),$3.ival,0);}
						| ID LBRACK INT RBRACK OF INT							{$$.exp = A_AllocateArrayExp(EM_tokPos,S_Symbol($1.sval),$3.ival,$6.ival);}
						| ID LBRACK INT RBRACK OF FLOAT							{$$.exp = A_AllocateArrayExp(EM_tokPos,S_Symbol($1.sval),$3.ival,2);}

AllocateRecordExp:		ID LBRACE ListExpComma RBRACE							{$$.exp = A_AllocateRecordExp(EM_tokPos,S_Symbol($1.sval),$3.expList);}

VariableDeclaration:	VAR ID COLON ID											{$$.dec = A_VarDec(EM_tokPos,S_Symbol($2.sval),S_Symbol($4.sval),NULL);}
						| VAR ID ASSIGN exp										{$$.dec = A_VarDec(EM_tokPos,S_Symbol($2.sval),NULL,             $4.exp);}
						| VAR ID ASSIGN AllocateArrayExp						{$$.dec = A_VarDec(EM_tokPos,S_Symbol($2.sval),NULL,             $4.exp);}
						| VAR ID ASSIGN AllocateRecordExp						{$$.dec = A_VarDec(EM_tokPos,S_Symbol($2.sval),NULL,             $4.exp);}
						| VAR ID COLON ID ASSIGN exp							{$$.dec = A_VarDec(EM_tokPos,S_Symbol($2.sval),S_Symbol($4.sval),$6.exp);}
						| VAR ID COLON ID ASSIGN AllocateArrayExp				{$$.dec = A_VarDec(EM_tokPos,S_Symbol($2.sval),S_Symbol($4.sval),$6.exp);}
						| VAR ID COLON ID ASSIGN AllocateRecordExp				{$$.dec = A_VarDec(EM_tokPos,S_Symbol($2.sval),S_Symbol($4.sval),$6.exp);}

FunctionDeclaration:	FUNCTION ID LPAREN RPAREN EQ exp						{$$.dec = A_FunDec(EM_tokPos,S_Symbol($2.sval),NULL,NULL,$6.exp);}
						| FUNCTION ID LPAREN RPAREN COLON ID EQ exp				{$$.dec = A_FunDec(EM_tokPos,S_Symbol($2.sval),NULL,S_Symbol($6.sval),$8.exp);}
						| FUNCTION ID LPAREN TypeFields RPAREN EQ exp			{$$.dec = A_FunDec(EM_tokPos,S_Symbol($2.sval),$4.fieldList,NULL,$7.exp);}
						| FUNCTION ID LPAREN TypeFields RPAREN COLON ID EQ exp	{$$.dec = A_FunDec(EM_tokPos,S_Symbol($2.sval),$4.fieldList,S_Symbol($7.sval),$9.exp);}

declaration:			TypeDeclaration											{$$.dec = $1.dec;}
						| VariableDeclaration									{$$.dec = $1.dec;}
						| FunctionDeclaration									{$$.dec = $1.dec;}

declarations:			declaration declarations								{$$.decList = A_DecList($1.dec,$2.decList);}
						| declaration											{$$.decList = A_DecList($1.dec,NULL);}

LetExp:					LET declarations IN exp END								{$$.exp = A_LetExp(EM_tokPos,$2.decList,$4.exp);}

variable:				ID														{$$.var = A_SimpleVar(EM_tokPos,S_Symbol($1.sval));}
						| variable ARROW ID										{$$.var = A_FieldVar(EM_tokPos,$1.var,S_Symbol($3.sval));}
						| variable LBRACK exp RBRACK							{$$.var = A_SubscriptVar(EM_tokPos,$1.var,$3.exp);}

AssignExp:				variable ASSIGN exp										{$$.exp = A_AssignExp(EM_tokPos,$1.var,$3.exp);}
						| variable ASSIGN AllocateArrayExp						{$$.exp = A_AssignExp(EM_tokPos,$1.var,$3.exp);}
						| variable ASSIGN AllocateRecordExp						{$$.exp = A_AssignExp(EM_tokPos,$1.var,$3.exp);}

CallExp:				ID LPAREN RPAREN										{$$.exp = A_CallExp(EM_tokPos,S_Symbol($1.sval),NULL);}
						| ID LPAREN ListExpComma RPAREN							{$$.exp = A_CallExp(EM_tokPos,S_Symbol($1.sval),$3.expList);}

%%
