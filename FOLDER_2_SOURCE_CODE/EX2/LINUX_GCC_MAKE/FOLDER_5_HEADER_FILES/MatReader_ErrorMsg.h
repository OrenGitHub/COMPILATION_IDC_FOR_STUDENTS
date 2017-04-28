#ifndef __MAT_READER_ERRORMSG_H__
#define __MAT_READER_ERRORMSG_H__

/***********************************/
/* FILE NAME: MatReader_ErrorMsg.h */
/***********************************/

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "util.h"

/**********************/
/* EXTERNAL VARIABLES */
/**********************/
extern int MatReader_ErrorMsg_tokPos;

/***********/
/* NEWLINE */
/***********/
void MatReader_ErrorMsg_Newline(void);

/*********/
/* ERROR */
/*********/
void MatReader_ErrorMsg_Error(int, string,...);

/****************/
/* LOG FILENAME */
/****************/
void MatReader_ErrorMsg_Set_Log_Filename(string log_Filename);

/*********/
/* RESET */
/*********/
void MatReader_ErrorMsg_Reset(string filename);

#endif
