#ifndef __MAT_READER_ERRORMSG_H__
#define __MAT_READER_ERRORMSG_H__

/*******************************************/
/* FILE NAME: FILE_04_MatReader_ErrorMsg.h */
/*******************************************/
extern bool MatReader_ErrorMsg_anyErrors;

void MatReader_ErrorMsg_Newline(void);

extern int MatReader_ErrorMsg_tokPos;

void MatReader_ErrorMsg_Error(int, string,...);
void MatReader_ErrorMsg_Reset(string filename);

#endif
