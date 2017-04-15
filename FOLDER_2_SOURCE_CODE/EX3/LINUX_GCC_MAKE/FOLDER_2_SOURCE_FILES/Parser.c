/***********************/
/* FILE NAME: Parser.c */
/***********************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "util.h"
#include "Stack.h"
#include "Parser.h"
#include "Calc_ErrorMsg.h"
#include "Calc_Tokens.h"

/***************/
/* DEFINITIONS */
/***************/
#define ERROR_STATE 15
#define ACCEPT_STATE 16
#define X ERROR_STATE
#define A ACCEPT_STATE

/********************/
/* GLOBAL VARIABLES */
/********************/
Stack s;
int tok=0;
int status=1;
int readToken=1;
string entry=NULL;

/********************/
/* GLOBAL VARIABLES */
/********************/
YYSTYPE zzlval;

/****************************/
/* EXTERNAL LEXING FUNCTION */
/****************************/
int zzlex(void);

#define NUM_DERIVIATION_RULES 9
char *RULES[NUM_DERIVIATION_RULES]=
{
	"S->E$",
	"E->E+T",
	"E->E-T",
	"E->T",
	"T->T*F",
	"T->T/F",
	"T->F",
	"F->y",
	"F->(E)"
};

char LEFT_SIDE_DERIVIATION_RULES[NUM_DERIVIATION_RULES]=
{
	'S',
	'E',
	'E',
	'E',
	'T',
	'T',
	'T',
	'F',
	'F'
};

int LENGTH_DERIVIATION_RULES[NUM_DERIVIATION_RULES]=
{
	2,/* S->E$, */
	3,/* E->E+T */
	3,/* E->E-T */
	1,/* E->T   */
	3,/* T->T*F */
	3,/* T->T/F */
	1,/* T->F   */
	1,/* F->y   */
	3/* F->(E) */
};

int ConvertTokenToIndex(int token)
{
	switch (token) {
	case (LPAREN): return 0;
	case (RPAREN): return 1;
	case (INT):    return 2;
	case (PLUS):   return 3;
	case (MINUS):  return 4;
	case (TIMES):  return 5;
	case (DIVIDE): return 6;
	case (0):      return 7;
	default:       return -1;
	}
}

int ConvertCharToIndex(char c)
{
	switch (c) {
	case ('('): return  0;
	case (')'): return  1;
	case ('y'): return  2;
	case ('+'): return  3;
	case ('-'): return  4;
	case ('*'): return  5;
	case ('/'): return  6;
	case ('$'): return  7;
	case ('E'): return  8;
	case ('T'): return  9;
	case ('F'): return 10;
	default:    return -1;
	}
}

char ConvertTokenToChar(int token)
{
	switch (token) {
	case (LPAREN): return '(';
	case (RPAREN): return ')';
	case (INT):    return 'y';
	case (PLUS):   return '+';
	case (MINUS):  return '-';
	case (TIMES):  return '*';
	case (DIVIDE): return '/';
	case (0):      return '$';
	default:       return  0 ;
	}
}

void Shift(void)
{
	int state=0;

	/**********************/
	/* Compute Next State */
	/**********************/
	state=atoi(entry+1);

	/********/
	/* Push */
	/********/
	Push(&s,state,ConvertTokenToChar(tok));
	
	/*******************/
	/* Read next token */
	/*******************/
	tok=zzlex();
	
	/*******************/
	/* print the stack */
	/*******************/
	PrintStack(&s);
}

void Reduce(int rule_number)
{
	int i=0;
	int state=0;

	/**********************************************************/
	/* Pop the stack the length of the right side of the rule */
	/**********************************************************/
	for (i=0;i<LENGTH_DERIVIATION_RULES[rule_number];i++)
	{
		Pop(&s);
	}

	/**********************/
	/* Compute Next State */
	/**********************/
	entry=table[Top(&s)->state][ConvertCharToIndex(LEFT_SIDE_DERIVIATION_RULES[rule_number])];

	/******************************************/
	/* Only goto states are possible here ... */
	/******************************************/
	assert((*entry) == 'g');
	state=atoi(entry+1);

	/************************************/
	/* Push left side variable on stack */
	/************************************/
	Push(&s,state,LEFT_SIDE_DERIVIATION_RULES[rule_number]);

	/*******************/
	/* print the stack */
	/*******************/
	PrintStack(&s);
}

int Parse()
{
	/**************/
	/* Init Stack */
	/**************/
	s.c=0;
	s.state=0;
	s.next=NULL;

	/*******************/
	/* print the stack */
	/*******************/
	PrintStack(&s);

	/***********************/
	/* Get the first token */
	/***********************/
	tok=zzlex();
	
	while (1) {

		/***********************/
		/* extract table entry */
		/***********************/
		entry=table[Top(&s)->state][ConvertTokenToIndex(tok)];
		
		switch (*entry) {
		
		case ('s'):

			// Shift
			Shift();
			break;

		case ('r'):

			// Reduce
			Reduce(atoi(entry+1));
			break;

		case ('a'):
			
			// Accept
			return 1;

		case (0):

			// Error
			return 0;
		}
	}

	return 0;
}
