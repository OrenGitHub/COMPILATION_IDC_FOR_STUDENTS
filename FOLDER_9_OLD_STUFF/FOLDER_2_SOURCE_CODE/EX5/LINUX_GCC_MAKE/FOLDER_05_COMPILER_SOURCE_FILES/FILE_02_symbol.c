/***********************/
/* FILE NAME: symbol.c */
/***********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <string.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_02_symbol.h"
//#include "table.h"

/*********/
/* TYPES */
/*********/
struct S_symbol_ {string name; S_symbol next;};

/***************/
/* CONSTRUCTOR */
/***************/
static S_symbol mksymbol(string name, S_symbol next)
{
	S_symbol s = (S_symbol) checked_malloc(sizeof(*s));
	s->name=name; s->next=next;
	return s;
}

/********************/
/* GLOBAL VARIABLES */
/********************/
#define SIZE 109  /* should be prime */
static S_symbol hashtable[SIZE];

/*****************/
/* Hash Function */
/*****************/
static unsigned int hash(char *s0)
{
	char *s;
	unsigned int h=0;
	
	for (s=s0; (*s); s++)
	{
		h = h*65599 + (*s);
	}
	
	return h;
}
 
static int streq(string a, string b)
{
 return !strcmp(a,b);
}

S_symbol S_Symbol(string name)
{
	int index= hash(name) % SIZE;
	S_symbol syms = hashtable[index], sym;
	
	for (sym=syms; sym; sym=sym->next)
	{
		if (streq(sym->name,name))
		{
			return sym;
		}
	}
	
	sym = mksymbol(name,syms);
	hashtable[index]=sym;
	return sym;
}
 
string S_name(S_symbol sym)
{
	return sym->name;
}
