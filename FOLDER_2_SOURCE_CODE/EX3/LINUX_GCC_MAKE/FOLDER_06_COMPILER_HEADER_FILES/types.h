#ifndef __TYPES_H__
#define __TYPES_H__

/**********************/
/* FILE NAME: types.h */
/**********************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include "tree.h"
#include "symbol.h"

/*********/
/* TYPES */
/*********/
typedef struct Ty_ty_ *Ty_ty;
typedef struct Ty_field_ *Ty_field;
typedef struct Ty_tyList_ *Ty_tyList;
typedef struct Ty_fieldList_ *Ty_fieldList;

typedef enum 
{
	Ty_int,
	Ty_float,
	Ty_string,
	Ty_nil,
	Ty_void,
	Ty_name,
	Ty_array,
	Ty_record,
	Ty_dummyType,
} TypeKind;


struct Ty_ty_
{
	TypeKind kind;
	
	union
	{
		Ty_ty name;
		Ty_ty array;
		Ty_fieldList record;
	}
	u;
};

struct Ty_tyList_ {Ty_ty head; Ty_tyList tail;};
struct Ty_field_ {S_symbol name; Ty_ty ty;};
struct Ty_fieldList_ {Ty_field head; Ty_fieldList tail;};

Ty_ty Ty_Nil(void);
Ty_ty Ty_Int(void);
Ty_ty Ty_Void(void);
Ty_ty Ty_Float(void);
Ty_ty Ty_String(void);
Ty_ty Ty_DummyType(void);

Ty_ty Ty_Record(Ty_fieldList fields);
Ty_ty Ty_Array(Ty_ty ty);
Ty_ty Ty_Name(S_symbol sym, Ty_ty ty);

Ty_tyList Ty_TyList(Ty_ty head, Ty_tyList tail);
Ty_field Ty_Field(S_symbol name, Ty_ty ty);
Ty_fieldList Ty_FieldList(Ty_field head, Ty_fieldList tail);

void Ty_print(Ty_ty t);
void TyList_print(Ty_tyList list);

struct expty {T_exp exp; Ty_ty ty;};
struct expty expTy(T_exp exp, Ty_ty ty);

#endif