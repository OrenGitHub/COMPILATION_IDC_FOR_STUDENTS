#ifndef __UTIL_H__
#define __UTIL_H__

/*****************************/
/* FILE NAME: FILE_01_util.h */
/*****************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <assert.h>

/*********/
/* TYPES */
/*********/
typedef char *string;
typedef char bool;

/***************/
/* DEFINITIONS */
/***************/
#define TRUE 1
#define FALSE 0

/*************/
/* FUNCTIONS */
/*************/
void *checked_malloc(int);
string String(char *);

#endif
