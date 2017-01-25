/************************/
/* FILE NAEM: IR_Tree.c */
/************************/

/****************************************/
/* WARNING DISABLE: sprintf - I love it */
/****************************************/
#pragma warning (disable: 4996)

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <string.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_01_util.h"
#include "FILE_02_symbol.h"
#include "FILE_13_IR_tree.h"
#include "FILE_15_Temporaries_and_Labels.h"

/********************/
/* GLOBAL VARIABLES */
/********************/
/********************/
/* For Printing ... */
/********************/
static int serial_node_number=0;

/********************/
/* For Printing ... */
/********************/
const char *binopConvertEnumToString[T_numBinOps] =
{
	"PLUS",
	"MINUS",
	"MUL",
	"DIV",
	"AND",
	"OR",
	"LSHIFT",
	"RSHIFT",
	"ARSHIFT",
	"XOR",
	"EQ",
	"NEQ",
	"LT",
	"GT",
	"LE",
	"GE",
};

/****************/
/* CONSTRUCTORS */
/****************/
T_expList T_ExpList(T_exp head, T_expList tail)
{
	T_expList p = (T_expList) checked_malloc (sizeof *p);

	p->head=head;
	p->tail=tail;
 
	return p;
}
T_exp T_Seq(T_exp left, T_exp right)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);
	
	p->kind=T_SEQ;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	strcpy(p->PrintTheKindOfTreeIAm,"SEQ");

	p->u.SEQ.left=left;
	p->u.SEQ.right=right;
	
	return p;
}
T_exp T_Label(Temp_label label)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);
 
	p->kind=T_LABEL;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"LABEL: %s",Temp_labelstring(label));

	p->u.LABEL=label;
 
	return p;
}
T_exp T_JumpLabel(Temp_label label)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);
 
	p->kind=T_JUMP;
 
	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"JUMP %s",Temp_labelstring(label));

	p->u.JUMP.type = T_JUMP_LABEL;
	p->u.JUMP.u.label=label;
 
	return p;
}
T_exp T_JumpRegister(Temp_temp temp)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);
 
	p->kind=T_JUMP;
 
	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"JUMP %s",Temp_look(Temp_name(),temp));

	p->u.JUMP.type = T_JUMP_REGISTER;
	p->u.JUMP.u.temp=temp;
 
	return p;
}
T_exp T_Move(T_exp dst, T_exp src)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);
 
	p->kind=T_MOVE;
 
	p->PrintMyNodeSerialNumber = serial_node_number++;

	strcpy(p->PrintTheKindOfTreeIAm,"MOVE");

	p->u.MOVE.dst=dst;
	p->u.MOVE.src=src;
	
	return p;
}
T_exp T_Binop(T_binOp op, T_exp left, T_exp right)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);

	p->kind=T_BINOP;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"BINOP (%s)",binopConvertEnumToString[op]);

	p->u.BINOP.op=op;
	p->u.BINOP.left=left;
	p->u.BINOP.right=right;
	
	return p;
}
T_exp T_Mem(T_exp exp)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);
 
	p->kind=T_MEM;
 
	p->PrintMyNodeSerialNumber = serial_node_number++;

	strcpy(p->PrintTheKindOfTreeIAm,"MEM");

	p->u.MEM=exp;
 
	return p;
}
T_exp T_Temp(Temp_temp temp)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);

	p->kind=T_TEMP;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"TEMP %s",Temp_look(Temp_name(),temp));
	
	p->u.TEMP=temp;
	
	return p;
}
T_exp T_Const(int consti)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);
	
	p->kind=T_CONST;
	
	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"CONST %d",consti);

	p->u.CONST=consti;
	
	return p;
}
T_exp T_Call(Temp_label name, T_expList args)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);

	p->kind=T_CALL;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"CALL: %s",Temp_labelstring(name));

	p->u.CALL.name = name;
	p->u.CALL.args = args;
	
	return p;
}
T_exp T_Function(T_exp prologue, T_exp body, T_exp epilogue, Temp_label name)
{
	T_exp p = (T_exp) checked_malloc(sizeof *p);
	
	p->kind=T_FUNCTION;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(p->PrintTheKindOfTreeIAm,"FUNCTION: %s",Temp_labelstring(name));

	p->u.FUNCTION.prologue = prologue;
	p->u.FUNCTION.body = body;
	p->u.FUNCTION.epilogue = epilogue;
	p->u.FUNCTION.name = name;
	
	return p;
}
T_exp T_Cjump(T_binOp		op,
	T_exp		left,
	T_exp		right,
	Temp_label	jumpToHereIfTrue,
	Temp_label	jumpToHereIfFalse)
{
	T_exp p = (T_exp)checked_malloc(sizeof *p);

	p->kind = T_CJUMP;

	p->PrintMyNodeSerialNumber = serial_node_number++;

	sprintf(
		p->PrintTheKindOfTreeIAm,
		"CJUMP\n op = %s\n if (left op right) goto %s;\n else goto %s;",
		binopConvertEnumToString[op],
		Temp_labelstring(jumpToHereIfTrue),
		Temp_labelstring(jumpToHereIfFalse));

	p->u.CJUMP.op = op;
	p->u.CJUMP.left = left;
	p->u.CJUMP.right = right;
	p->u.CJUMP.jumpToHereIfTrue = jumpToHereIfTrue;
	p->u.CJUMP.jumpToHereIfFalse = jumpToHereIfFalse;

	return p;
}


