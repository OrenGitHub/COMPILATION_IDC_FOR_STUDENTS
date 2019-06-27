#ifndef __PARSER_H__
#define __PARSER_H__

/*********/
/* E,T,F */
/*********/
#define NUM_VARIABLES 3

/******************************/
/* (, ), INT(x), +, -, *, / $ */
/******************************/
#define NUM_TOKENS 7

/*********/
/* Table */
/*********/
extern string table[][NUM_VARIABLES+NUM_TOKENS+1];

/***********/
/* Parse() */
/***********/
int Parse();

#endif
