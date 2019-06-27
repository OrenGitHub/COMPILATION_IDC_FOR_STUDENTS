#ifndef __SYMBOL_H__
#define __SYMBOL_H__

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_01_util.h"

typedef struct S_symbol_ *S_symbol;

/* Make a unique symbol from a given string.  
 *  Different calls to S_Symbol("foo") will yield the same S_symbol
 *  value, even if the "foo" strings are at different locations. */
S_symbol S_Symbol(string);

/* Extract the underlying string from a symbol */
string S_name(S_symbol);

#endif
