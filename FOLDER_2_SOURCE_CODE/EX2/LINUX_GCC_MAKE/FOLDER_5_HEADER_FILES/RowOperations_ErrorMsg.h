#ifndef __ROW_OPERATIONS_ERRORMSG_H__
#define __ROW_OPERATIONS_ERRORMSG_H__

/***************************************/
/* FILE NAME: RowOperations_ErrorMsg.h */
/***************************************/

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "util.h"

/**********************/
/* EXTERNAL VARIABLES */
/**********************/
extern int RowOperations_ErrorMsg_tokPos;

/***********/
/* NEWLINE */
/***********/
void RowOperations_ErrorMsg_Newline(void);

/*********/
/* ERROR */
/*********/
void RowOperations_ErrorMsg_Error(int, string,...);

/****************/
/* LOG FILENAME */
/****************/
void RowOperations_ErrorMsg_Set_Log_Filename(string log_Filename);

/*********/
/* RESET */
/*********/
void RowOperations_ErrorMsg_Reset(string filename);

#endif
