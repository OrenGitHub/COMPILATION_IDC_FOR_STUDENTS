#ifndef __MAT_READER_TOKENS_H__
#define __MAT_READER_TOKENS_H__

/***********************************/
/* FLEX uses 0-255 for inner stuff */
/***********************************/
#define SERIAL_NUMBER_START	256

/*********************/
/* TOKENS start here */
/*********************/
#define LBRACK		SERIAL_NUMBER_START+1
#define RBRACK		SERIAL_NUMBER_START+2
#define DIVIDE		SERIAL_NUMBER_START+3
#define SEMICOLON	SERIAL_NUMBER_START+4
#define INT			SERIAL_NUMBER_START+5

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
/* EXTERNAL VARIABLE aalval */
/****************************/
extern YYSTYPE aalval;

#endif
