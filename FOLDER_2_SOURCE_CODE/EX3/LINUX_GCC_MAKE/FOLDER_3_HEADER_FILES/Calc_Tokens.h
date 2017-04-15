#ifndef __CALC_TOKENS_H__
#define __CALC_TOKENS_H__

/***********************************/
/* FLEX uses 0-255 for inner stuff */
/***********************************/
#define SERIAL_NUMBER_START	256

/*********************/
/* TOKENS start here */
/*********************/
#define PLUS	SERIAL_NUMBER_START+1
#define MINUS	SERIAL_NUMBER_START+2
#define TIMES	SERIAL_NUMBER_START+3
#define DIVIDE	SERIAL_NUMBER_START+4
#define LPAREN	SERIAL_NUMBER_START+5
#define RPAREN	SERIAL_NUMBER_START+6
#define INT		SERIAL_NUMBER_START+7

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
/* EXTERNAL VARIABLE zzlval */
/****************************/
extern YYSTYPE zzlval;

#endif
