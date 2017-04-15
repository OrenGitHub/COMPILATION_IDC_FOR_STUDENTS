#ifndef __SEMANT_H__
#define __SEMANT_H__

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_10_SymbolTable.h"
#include "FILE_06_StarKist_AST.h"
#include "FILE_11_Types.h"

/*********************/
/* Semantic_Analysis */
/*********************/
void Semantic_Analysis(A_exp AST);

void SEM_transTypeDec(S_table venv,S_table tenv, A_dec dec);
Ty_ty SEM_transExp(S_table venv,S_table tenv,A_exp exp);

#endif
