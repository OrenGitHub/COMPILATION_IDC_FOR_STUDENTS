/*********/
/* env.c */
/*********/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_10_SymbolTableEntry.h"
#include "FILE_10_SymbolTable.h"

/***************/
/* E_base_tenv */
/***************/
S_table E_base_tenv(void)
{
	return S_empty();
}

/***************/
/* E_base_venv */
/***************/
S_table E_base_venv(void)
{
	return S_empty();
}

E_enventry E_VarEntry(Ty_ty ty,F_access access)
{
	E_enventry env_entry = (E_enventry) checked_malloc(sizeof(*env_entry));
	
	env_entry->u.var.type = ty;
	env_entry->kind = E_varEntry;
	env_entry->u.var.access = access;

	return env_entry;
}
E_enventry E_FunEntry(Ty_tyList formals, Ty_ty result,F_frame f)
{
	E_enventry env_entry = (E_enventry) checked_malloc(sizeof(*env_entry));

	env_entry->kind = E_funEntry;

	env_entry->u.fun.frame = f;
	env_entry->u.fun.result = result;
	env_entry->u.fun.formals = formals;

	return env_entry;
}
