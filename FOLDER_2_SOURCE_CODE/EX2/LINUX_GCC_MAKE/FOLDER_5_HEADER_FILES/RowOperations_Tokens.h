#ifndef __ROW_OPERATIONS_TOKENS_H__
#define __ROW_OPERATIONS_TOKENS_H__

/***********************************/
/* FLEX uses 0-255 for inner stuff */
/***********************************/
#define SERIAL_NUMBER_START	256

/*********************/
/* TOKENS start here */
/*********************/
#define ROW					SERIAL_NUMBER_START+1
#define INDEX				SERIAL_NUMBER_START+2
#define LEFT_ARROW			SERIAL_NUMBER_START+3
#define LEFT_RIGHT_ARROW	SERIAL_NUMBER_START+4
#define INT					SERIAL_NUMBER_START+5
#define PLUS				SERIAL_NUMBER_START+6
#define MINUS				SERIAL_NUMBER_START+7
#define DIVIDE				SERIAL_NUMBER_START+8

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
/* EXTERNAL VARIABLE bblval */
/****************************/
extern YYSTYPE bblval;

#endif
