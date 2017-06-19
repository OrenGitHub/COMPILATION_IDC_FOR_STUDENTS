/**********************/
/* FILE NAME: types.c */
/**********************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include <stdio.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_01_util.h"
#include "FILE_02_symbol.h"
#include "FILE_11_Types.h"
#include "FILE_13_IR_tree.h"

static struct Ty_ty_ tynil = {Ty_nil};
Ty_ty Ty_Nil(void) {return &tynil;}

static struct Ty_ty_ tyint = {Ty_int};
Ty_ty Ty_Int(void) {return &tyint;}

static struct Ty_ty_ tydummyType = {Ty_dummyType};
Ty_ty Ty_DummyType(void) {return &tydummyType;}

static struct Ty_ty_ tyfloat = {Ty_float};
Ty_ty Ty_Float(void) {return &tyfloat;}

static struct Ty_ty_ tystring = {Ty_string};
Ty_ty Ty_String(void) {return &tystring;}

static struct Ty_ty_ tyvoid = {Ty_void};
Ty_ty Ty_Void(void) {return &tyvoid;}

Ty_ty Ty_Record(Ty_fieldList fields)
{
	Ty_ty p = (Ty_ty) checked_malloc(sizeof(*p));
	p->kind=Ty_record;
	p->u.record=fields;
	return p;
}

Ty_ty Ty_Array(Ty_ty ty)
{
	Ty_ty p = (Ty_ty) checked_malloc(sizeof(*p));
	p->kind=Ty_array;
	p->u.array=ty;
	
	return p;
}

Ty_tyList Ty_TyList(Ty_ty head, Ty_tyList tail)
{
	Ty_tyList p = (Ty_tyList) checked_malloc(sizeof(*p));
	p->head=head;
	p->tail=tail;
	
	return p;
}

Ty_field Ty_Field(S_symbol name, Ty_ty ty)
{
	Ty_field p = (Ty_field) checked_malloc(sizeof(*p));
	p->name=name;
	p->ty=ty;
	
	return p;
}

Ty_fieldList Ty_FieldList(Ty_field head, Ty_fieldList tail)
{
	Ty_fieldList p = (Ty_fieldList) checked_malloc(sizeof(*p));
	p->head=head;
	p->tail=tail;
	
	return p;
}

struct expty expTy(T_exp exp, Ty_ty ty)
{
	struct expty e;
	e.exp = exp;
	e.ty = ty;
	return e;
}
