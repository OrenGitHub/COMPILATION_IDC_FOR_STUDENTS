#ifndef __ROW_OPERATIONS_ERRORMSG_H__
#define __ROW_OPERATIONS_ERRORMSG_H__

/***********************************************/
/* FILE NAME: FILE_09_RowOperations_ErrorMsg.h */
/***********************************************/
extern bool RowOperations_ErrorMsg_anyErrors;

void RowOperations_ErrorMsg_Newline(void);

extern int RowOperations_ErrorMsg_tokPos;

void RowOperations_ErrorMsg_Error(int, string,...);
void RowOperations_ErrorMsg_Reset(string filename);

#endif
