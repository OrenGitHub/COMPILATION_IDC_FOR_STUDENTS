/****************************/
/* FILE NAME: SymbolTable.c */
/****************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <string.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "symbol.h"
#include "SymbolTable.h"

/********************/
/* New Symbol Table */
/********************/
S_table S_empty(void)
{
	return TAB_empty();
}

void S_enter(S_table t, S_symbol sym, void *value)
{
	TAB_enter(t, sym, value);
}

void *S_look(S_table t, S_symbol sym)
{
	return TAB_look(t, sym);
}

void S_beginScope(S_table t)
{
	S_symbol ScopeSign = S_Symbol("<SCOPE-SIGN>");
	S_enter(t, ScopeSign, NULL);
}

void S_endScope(S_table t)
{
	S_symbol s;
	S_symbol ScopeSign = S_Symbol("<SCOPE-SIGN>");

	do
	{
		s = (S_symbol) TAB_pop(t);
	}
	while (s != ScopeSign);
}
