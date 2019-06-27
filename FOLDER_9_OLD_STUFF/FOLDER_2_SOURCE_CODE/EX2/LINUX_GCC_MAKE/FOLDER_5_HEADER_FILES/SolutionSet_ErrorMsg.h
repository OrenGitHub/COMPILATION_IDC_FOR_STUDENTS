#ifndef __SOLUTION_SET_ERRORMSG_H__
#define __SOLUTION_SET_ERRORMSG_H__

/*************************************/
/* FILE NAME: SolutionSet_ErrorMsg.h */
/*************************************/

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "util.h"

/**********************/
/* EXTERNAL VARIABLES */
/**********************/
extern int SolutionSet_ErrorMsg_tokPos;

/***********/
/* NEWLINE */
/***********/
void SolutionSet_ErrorMsg_Newline(void);

/*********/
/* ERROR */
/*********/
void SolutionSet_ErrorMsg_Error(int, string,...);

/****************/
/* LOG FILENAME */
/****************/
void SolutionSet_ErrorMsg_Set_Log_Filename(string log_Filename);

/*********/
/* RESET */
/*********/
void SolutionSet_ErrorMsg_Reset(string filename);

#endif
