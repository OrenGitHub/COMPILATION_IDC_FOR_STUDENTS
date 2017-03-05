#ifndef __SOLUTION_SET_ERRORMSG_H__
#define __SOLUTION_SET_ERRORMSG_H__

/*********************************************/
/* FILE NAME: FILE_14_SolutionSet_ErrorMsg.h */
/*********************************************/
extern bool SolutionSet_ErrorMsg_anyErrors;

void SolutionSet_ErrorMsg_Newline(void);

extern int SolutionSet_ErrorMsg_tokPos;

void SolutionSet_ErrorMsg_Error(int, string,...);
void SolutionSet_ErrorMsg_Reset(string filename);

#endif
