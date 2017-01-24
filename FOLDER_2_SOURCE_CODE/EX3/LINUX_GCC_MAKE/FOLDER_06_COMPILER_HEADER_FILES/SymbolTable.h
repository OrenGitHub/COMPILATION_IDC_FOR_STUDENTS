#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

/****************************/
/* FILE NAME: SymbolTable.h */
/****************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "symbol.h"
#include "table.h"

/*********/
/* TYPES */
/*********/
typedef struct TAB_table_ *S_table;

S_table S_empty(void);

void S_enter(S_table t, S_symbol sym, void *value);
void *S_look(S_table t, S_symbol sym);

void S_beginScope(S_table t);
void S_endScope(S_table t);

#endif