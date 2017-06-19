#ifndef __TEMPS_TO_REGS_ERRORMSG_H__
#define __TEMPS_TO_REGS_ERRORMSG_H__

/*********************************************/
/* FILE NAME: PSEUDO_MIPS_ASM_AST_errormsg.h */
/*********************************************/
extern bool TEMPS_TO_REGS_EM_anyErrors;

void TEMPS_TO_REGS_EM_newline(void);

extern int TEMPS_TO_REGS_EM_tokPos;

void TEMPS_TO_REGS_EM_error(int, string,...);
void TEMPS_TO_REGS_EM_impossible(string,...);
void TEMPS_TO_REGS_EM_reset(string filename);

#endif