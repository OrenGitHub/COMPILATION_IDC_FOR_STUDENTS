/********************/
/* FILE NAME: AST.c */
/********************/

/****************************************/
/* WARNING DISABLE: sprintf - I love it */
/****************************************/
#pragma warning (disable: 4996)

/*****************/
/* INCLUDE FILES */
/*****************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "util.h"
#include "absyn.h"
#include "symbol.h"

/********************/
/* GLOBAL VARIABLES */
/********************/
static int serial_node_number=0;

A_var A_SimpleVar(A_pos pos, S_symbol sym)
{
	A_var p = (A_var) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"Simple\nVar(%s)",S_name(sym));

	p->kind=A_simpleVar;
	p->pos=pos;
	p->u.simple=sym;
	return p;
}

A_var A_FieldVar(A_pos pos, A_var var, S_symbol field_name)
{
	A_var p = (A_var) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"Field\nVar\n...->%s",S_name(field_name));

	p->kind=A_fieldVar;
	p->pos=pos;
	p->u.field.var=var;
	p->u.field.field_name=field_name;
	return p;
}

A_var A_SubscriptVar(A_pos pos, A_var var, A_exp exp)
{
	A_var p = (A_var) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"Subscript\nVar\n...[...]");

	p->kind=A_subscriptVar;
	p->pos=pos;
	p->u.subscript.var=var;
	p->u.subscript.exp=exp;
	return p;
}


A_exp A_VarExp(A_pos pos, A_var var)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_varExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	switch (var->kind) {
	case (A_simpleVar):

		sprintf(p->PrintTheKindOfTreeIAm, "SIMPLE\nVAR(%s)",S_name(var->u.simple));
		break;

	case (A_fieldVar) :

		sprintf(p->PrintTheKindOfTreeIAm, "FIELD\nVAR\n... --> %s", S_name(var->u.field.field_name));
		break;

	case (A_subscriptVar) :

		sprintf(p->PrintTheKindOfTreeIAm, "SUBSCRIPT\nVAR\n...[...]");
		break;
	}

	p->pos=pos;
	p->u.var=var;
	return p;
}

A_exp A_NilExp(A_pos pos)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_nilExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"NIL");

	p->pos=pos;
	return p;
}

A_exp A_IntExp(A_pos pos, int i)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_intExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"INT(%d)",i);

	p->pos=pos;
	p->u.intt=i;
	return p;
}

A_exp A_FloatExp(A_pos pos, float f)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_floatExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"FLOAT(%f)",f);

	p->pos=pos;
	p->u.floatt=f;
	return p;
}

A_exp A_StringExp(A_pos pos, string s)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind = A_stringExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"STRING(%s)",s);

	p->pos  = pos;
	p->u.stringg=s;
	return p;
}

A_exp A_CallExp(A_pos pos, S_symbol func, A_expList args)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_callExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"CALL\n(%s)",S_name(func));

	p->pos=pos;
	p->u.call.func=func;
	p->u.call.args=args;
	return p;
}

A_exp A_OpExp(A_pos pos, A_oper oper, A_exp left, A_exp right)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_opExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"OP");

	p->pos=pos;
	p->u.op.oper=oper;
	p->u.op.left=left;
	p->u.op.right=right;
	return p;
}

A_exp A_RecordExp(A_pos pos, S_symbol typ, A_efieldList fields)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_recordExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"RECORD");

	p->pos=pos;
	p->u.record.typ=typ;
	p->u.record.fields=fields;
	return p;
}

A_exp A_AllocateArrayExp(A_pos pos, S_symbol typ, int arraySize, int initializedValue)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_allocateArrayExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm, "Allocate\nArray\nOf\n%d %s", arraySize,S_name(typ));

	p->pos=pos;
	p->u.arrayInit.arrayType = typ;
	p->u.arrayInit.size = arraySize;
	p->u.arrayInit.initializedValue = initializedValue;
	return p;
}

A_exp A_AllocateRecordExp(A_pos pos, S_symbol typ, A_expList fields)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_allocateRecordExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"Allocate\nRecord");

	p->pos=pos;
	p->u.recordInit.reocrdType=typ;
	p->u.recordInit.initExpList = fields;
	return p;
}

A_exp A_SeqExp(A_pos pos, A_expList seq)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_seqExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"SEQ");

	p->pos=pos;
	p->u.seq=seq;
	return p;
}

A_exp A_AssignExp(A_pos pos, A_var var, A_exp exp)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_assignExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"ASSIGN");

	p->pos=pos;
	p->u.assign.var=var;
	p->u.assign.exp=exp;
	return p;
}

A_exp A_IfExp(A_pos pos, A_exp test, A_exp then, A_exp elsee)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_ifExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"IF");

	p->pos=pos;
	p->u.iff.test=test;
	p->u.iff.then=then;
	p->u.iff.elsee=elsee;
	return p;
}

A_exp A_WhileExp(A_pos pos, A_exp test, A_exp body)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_whileExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"WHILE");

	p->pos=pos;
	p->u.whilee.test=test;
	p->u.whilee.body=body;
	return p;
}

A_exp A_ForExp(A_pos pos, S_symbol var, A_exp lo, A_exp hi, A_exp body)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_forExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"FOR");

	p->pos=pos;
	p->u.forr.var=var;
	p->u.forr.lo=lo;
	p->u.forr.hi=hi;
	p->u.forr.body=body;
	return p;
}

A_exp A_BreakExp(A_pos pos)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_breakExp;
	
	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"BREAK");

	p->pos=pos;
	return p;
}

A_exp A_LetExp(A_pos pos, A_decList decs, A_exp body)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_letExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"LET");

	p->pos=pos;
	p->u.let.decs=decs;
	p->u.let.body=body;
	return p;
}

A_exp A_ArrayExp(A_pos pos, S_symbol typ, A_exp size, A_exp init)
{
	A_exp p = (A_exp) checked_malloc(sizeof(*p));
	p->kind=A_arrayExp;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"ARRAY");

	p->pos=pos;
	p->u.array.typ=typ;
	p->u.array.size=size;
	p->u.array.init=init;

	return p;
}

A_dec A_FunDec(A_pos pos, S_symbol name, A_fieldList params, S_symbol result, A_exp body)
{
	A_dec p = (A_dec) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"FUNCTION\nDEC");

	p->kind = A_functionDec;
	p->pos=pos;

	p->u.func_dec.name = name;
	p->u.func_dec.params = params;
	p->u.func_dec.result = result;
	p->u.func_dec.body = body;

	return p;
}

A_dec A_VarDec(A_pos pos, S_symbol var_name, S_symbol type_name, A_exp init)
{
	A_dec p = (A_dec) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"VARIABLE\nDEC");

	p->kind=A_varDec;
	p->pos=pos;
	p->u.var_dec.var_name=var_name;
	p->u.var_dec.type_name=type_name;
	p->u.var_dec.init=init;

	return p;
}

A_dec A_NameTypeDec(A_pos pos, S_symbol declared_type_name, S_symbol existing_type_name)
{
	A_dec p = (A_dec) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"NAME TYPE\nDEC");

	p->kind=A_typeDec;
	p->pos=pos;

	p->u.type_dec.type_name = declared_type_name;
	p->u.type_dec.ty.kind = A_nameTy;
	p->u.type_dec.ty.u.name = existing_type_name;

	return p;
}

A_dec A_ArrayTypeDec(A_pos pos, S_symbol declared_array_type_name, S_symbol the_type_of_each_entry_in_the_array)
{
	A_dec p = (A_dec) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"ARRAY TYPE\nDEC");

	p->kind=A_typeDec;
	p->pos=pos;

	p->u.type_dec.type_name = declared_array_type_name;
	p->u.type_dec.ty.kind = A_arrayTy;
	p->u.type_dec.ty.u.array = the_type_of_each_entry_in_the_array;

	return p;
}

A_dec A_RecordTypeDec(A_pos pos, S_symbol declared_record_type_name, A_fieldList fieldList)
{
	A_dec p = (A_dec) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"TYPE\nDEC");

	p->kind=A_typeDec;
	p->pos=pos;

	p->u.type_dec.type_name = declared_record_type_name;
	p->u.type_dec.ty.kind = A_recordTy;
	p->u.type_dec.ty.u.record = fieldList;
	
	return p;
}

A_field A_Field(A_pos pos, S_symbol field_name, S_symbol field_type_name)
{
	A_field p = (A_field) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"field");

	p->pos=pos;
	p->field_name=field_name;
	p->field_type_name=field_type_name;
	return p;
}

A_fieldList A_FieldList(A_field head, A_fieldList tail)
{
	A_fieldList p = (A_fieldList) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"Type\nFields");

	p->head=head;
	p->tail=tail;
	return p;
}

A_expList A_ExpList(A_exp head, A_expList tail)
{
	A_expList p = (A_expList) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm, "Exp\nList");

	p->head=head;
	p->tail=tail;
	return p;
}

A_decList A_DecList(A_dec head, A_decList tail)
{
	A_decList p = (A_decList) checked_malloc(sizeof(*p));

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm, "Dec\nList");

	p->head = head;
	p->tail=tail;
	return p;
}

