#ifndef __PSEUDO_MIPS_ASM_AST_ERRORMSG_H__
#define __PSEUDO_MIPS_ASM_AST_ERRORMSG_H__

/*********************************************/
/* FILE NAME: PSEUDO_MIPS_ASM_AST_errormsg.h */
/*********************************************/
extern bool PSEUDO_MIPS_ASM_AST_EM_anyErrors;

void PSEUDO_MIPS_ASM_AST_EM_newline(void);

extern int PSEUDO_MIPS_ASM_AST_EM_tokPos;

void PSEUDO_MIPS_ASM_AST_EM_error(int, string,...);
void PSEUDO_MIPS_ASM_AST_EM_impossible(string,...);
void PSEUDO_MIPS_ASM_AST_EM_reset(string filename);

#endif