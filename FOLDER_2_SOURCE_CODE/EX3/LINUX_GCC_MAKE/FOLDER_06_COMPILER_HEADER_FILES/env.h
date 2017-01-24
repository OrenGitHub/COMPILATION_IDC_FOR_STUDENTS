#ifndef __ENV_H__
#define __ENV_H__

/*****************/
/* INCLUDE FILES */
/*****************/
#include "SymbolTable.h"
#include "types.h"
#include "IR.h"

/*********/
/* TYPES */
/*********/
typedef struct E_enventry_ *E_enventry;
typedef enum {E_varEntry,E_funEntry} envEntryType;

/**************/
/* STRUCTURES */
/**************/
struct E_enventry_
{
	envEntryType kind;

	union
	{
		struct {F_access access; Ty_ty type;} var;
		
		struct
		{
			F_frame frame;
			Ty_tyList formals;
			Ty_ty result;
		}
		fun;
	}
	u;
};

/*************/
/* FUNCTIONS */
/*************/
E_enventry E_VarEntry(Ty_ty ty,F_access access);
E_enventry E_FunEntry(Ty_tyList formulas, Ty_ty result,F_frame f);

S_table E_base_tenv(void);
S_table E_base_venv(void);


#endif