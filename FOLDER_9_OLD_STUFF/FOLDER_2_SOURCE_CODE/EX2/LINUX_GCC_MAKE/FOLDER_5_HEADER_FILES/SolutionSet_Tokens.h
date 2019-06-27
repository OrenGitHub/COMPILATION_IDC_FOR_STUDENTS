#ifndef __SOLUTION_SET_TOKENS_H__
#define __SOLUTION_SET_TOKENS_H__

/***********************************/
/* FLEX uses 0-255 for inner stuff */
/***********************************/
#define SERIAL_NUMBER_START	256

/*********************/
/* TOKENS start here */
/*********************/
#define LPAREN	SERIAL_NUMBER_START+1
#define RPAREN	SERIAL_NUMBER_START+2
#define LBRACE	SERIAL_NUMBER_START+3
#define RBRACE	SERIAL_NUMBER_START+4
#define SP		SERIAL_NUMBER_START+5
#define COLON	SERIAL_NUMBER_START+6
#define INT		SERIAL_NUMBER_START+7
#define PLUS	SERIAL_NUMBER_START+8
#define DIVIDE	SERIAL_NUMBER_START+9

/*********/
/* TYPES */
/*********/
typedef union
{
	union
	{
		int ival;
	}
	gval;
}
YYSTYPE;

/****************************/
/* EXTERNAL VARIABLE cclval */
/****************************/
extern YYSTYPE cclval;

#endif
