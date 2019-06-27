/***********/
/* parse.c */
/***********/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "parse.h"
#include "FILE_01_util.h"
#include "FILE_02_symbol.h"
#include "FILE_06_StarKist_AST.h"
#include "FILE_03_StarKist_ErrorMsg.h"
#include "FILE_16_PseudoAsm_To_Simulation_ErrorMsg.h"

/************************/
/* Tiger_Program_To_AST */
/************************/
A_exp Tiger_Program_To_AST(string Tiger_Program_Filename)
{
	EM_reset(Tiger_Program_Filename);
	if (yyparse() == 0)
	{
		/******************/
		/* parsing worked */
		/******************/
		return absyn_root;
	}
	else
	{
		return NULL;
	}
}

/***************************/
/* Pseudo_Assembley_To_AST */
/***************************/
PSEUDO_MIPS_ASM_AST_expList Pseudo_Assembley_To_AST(string Pseudo_Assembley_Filename)
{
	PSEUDO_MIPS_ASM_AST_EM_reset(Pseudo_Assembley_Filename);
 	if (zzparse() == 0)
	{
		/******************/
		/* parsing worked */
		/******************/
		return PSEUDO_MIPS_ASM_AST_root;
	}
	else
	{
		return NULL;
	}
}
