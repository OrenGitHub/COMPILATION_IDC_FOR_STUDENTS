#ifndef __PARSE_H__
#define __PARSE_H__

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_06_StarKist_AST.h"
#include "FILE_19_PseudoAsm_To_Simulation_AST.h"

A_exp Tiger_Program_To_AST(string Tiger_Program_Filename);
PSEUDO_MIPS_ASM_AST_expList Pseudo_Assembley_To_AST(string Pseudo_Assembley_Filename);

extern int yyparse(void);
extern A_exp absyn_root;

extern int zzparse(void);
extern PSEUDO_MIPS_ASM_AST_expList PSEUDO_MIPS_ASM_AST_root;

#endif
