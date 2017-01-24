/************************************/
/* FILE NAME: PSEUDO_MIPS_ASM_AST.c */
/************************************/

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
#include "util.h"
#include "PSEUDO_MIPS_ASM_AST.h"


PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_LOAD(PSEUDO_MIPS_ASM_AST_Var var1,PSEUDO_MIPS_ASM_AST_Var var2,int offset)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_LOAD_EXP_TYPE;

	p->u.load.var1 = var1;
	p->u.load.var2 = var2;

	p->u.load.offset = offset;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_ADD_IMMEDIATE(PSEUDO_MIPS_ASM_AST_Var var1,PSEUDO_MIPS_ASM_AST_Var var2,int value)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_ADD_IMMEDIATE_EXP_TYPE;

	p->u.add_immediate.var1 = var1;
	p->u.add_immediate.var2 = var2;

	p->u.add_immediate.value = value;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_STORE(PSEUDO_MIPS_ASM_AST_Var var1,PSEUDO_MIPS_ASM_AST_Var var2,int offset)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_STORE_EXP_TYPE;

	p->u.store.var1 = var1;
	p->u.store.var2 = var2;

	p->u.store.offset = offset;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_MOVE(PSEUDO_MIPS_ASM_AST_Var var1,PSEUDO_MIPS_ASM_AST_Var var2)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_MOVE_EXP_TYPE;

	p->u.move.var1 = var1;
	p->u.move.var2 = var2;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_ADD(PSEUDO_MIPS_ASM_AST_Var var1,PSEUDO_MIPS_ASM_AST_Var var2,PSEUDO_MIPS_ASM_AST_Var var3)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_ADD_EXP_TYPE;

	p->u.add.var1 = var1;
	p->u.add.var2 = var2;
	p->u.add.var3 = var3;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_SUB(PSEUDO_MIPS_ASM_AST_Var var1,PSEUDO_MIPS_ASM_AST_Var var2,PSEUDO_MIPS_ASM_AST_Var var3)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_SUB_EXP_TYPE;

	p->u.add.var1 = var1;
	p->u.add.var2 = var2;
	p->u.add.var3 = var3;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_MUL(PSEUDO_MIPS_ASM_AST_Var var1,PSEUDO_MIPS_ASM_AST_Var var2,PSEUDO_MIPS_ASM_AST_Var var3)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_MUL_EXP_TYPE;

	p->u.add.var1 = var1;
	p->u.add.var2 = var2;
	p->u.add.var3 = var3;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_DIV(PSEUDO_MIPS_ASM_AST_Var var1,PSEUDO_MIPS_ASM_AST_Var var2,PSEUDO_MIPS_ASM_AST_Var var3)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_DIV_EXP_TYPE;

	p->u.add.var1 = var1;
	p->u.add.var2 = var2;
	p->u.add.var3 = var3;

	return p;
}


PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_LOAD_IMMEDIATE(PSEUDO_MIPS_ASM_AST_Var var,int value)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_LOAD_IMMEDIATE_EXP_TYPE;

	p->u.load_immediate.var = var;
	p->u.load_immediate.value = value;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_JUMP_LABEL(PSEUDO_MIPS_ASM_AST_Label_Type_ label)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_JUMP_LABEL_EXP_TYPE;

	strcpy(p->u.jump_label.name,label.name);

	p->u.jump_label.serial_number = label.serial_number;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_JUMP_REGISTER(char *register_name)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_JUMP_REGISTER_EXP_TYPE;

	strcpy(p->u.jump_register,register_name);

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_JUMP_AND_LINK(char *label)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_JUMP_AND_LINK_EXP_TYPE;

	strcpy(p->u.jump_and_link,label);

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_LABEL(PSEUDO_MIPS_ASM_AST_Label_Type_ label)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_LABEL_EXP_TYPE;

	strcpy(p->u.label.name,label.name);

	p->u.label.serial_number = label.serial_number;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_BEQ(
	PSEUDO_MIPS_ASM_AST_Var var1,
	PSEUDO_MIPS_ASM_AST_Var var2,
	PSEUDO_MIPS_ASM_AST_Label_Type_ label)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_BEQ_EXP_TYPE;

	p->u.beq.var1 = var1;
	p->u.beq.var2 = var2;

	strcpy(p->u.beq.label.name,label.name);
	p->u.beq.label.serial_number = label.serial_number;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_BNE(
	PSEUDO_MIPS_ASM_AST_Var var1,
	PSEUDO_MIPS_ASM_AST_Var var2,
	PSEUDO_MIPS_ASM_AST_Label_Type_ label)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_BNE_EXP_TYPE;

	p->u.bne.var1 = var1;
	p->u.bne.var2 = var2;

	strcpy(p->u.bne.label.name,label.name);
	p->u.bne.label.serial_number = label.serial_number;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_BGT(
	PSEUDO_MIPS_ASM_AST_Var var1,
	PSEUDO_MIPS_ASM_AST_Var var2,
	PSEUDO_MIPS_ASM_AST_Label_Type_ label)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_BGT_EXP_TYPE;

	p->u.bgt.var1 = var1;
	p->u.bgt.var2 = var2;

	strcpy(p->u.bgt.label.name,label.name);
	p->u.bgt.label.serial_number = label.serial_number;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_BLT(
	PSEUDO_MIPS_ASM_AST_Var var1,
	PSEUDO_MIPS_ASM_AST_Var var2,
	PSEUDO_MIPS_ASM_AST_Label_Type_ label)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_BLT_EXP_TYPE;

	p->u.blt.var1 = var1;
	p->u.blt.var2 = var2;

	strcpy(p->u.blt.label.name,label.name);
	p->u.blt.label.serial_number = label.serial_number;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_BGE(
	PSEUDO_MIPS_ASM_AST_Var var1,
	PSEUDO_MIPS_ASM_AST_Var var2,
	PSEUDO_MIPS_ASM_AST_Label_Type_ label)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_BGE_EXP_TYPE;

	p->u.bge.var1 = var1;
	p->u.bge.var2 = var2;

	strcpy(p->u.bge.label.name,label.name);
	p->u.bge.label.serial_number = label.serial_number;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_BLE(
	PSEUDO_MIPS_ASM_AST_Var var1,
	PSEUDO_MIPS_ASM_AST_Var var2,
	PSEUDO_MIPS_ASM_AST_Label_Type_ label)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_BLE_EXP_TYPE;

	p->u.ble.var1 = var1;
	p->u.ble.var2 = var2;

	strcpy(p->u.ble.label.name,label.name);
	p->u.ble.label.serial_number = label.serial_number;

	return p;
}

PSEUDO_MIPS_ASM_AST_Var PSEUDO_MIPS_ASM_AST_TEMP_VAR(int temp_serial_number)
{
	PSEUDO_MIPS_ASM_AST_Var p = (PSEUDO_MIPS_ASM_AST_Var) checked_malloc(sizeof(*p));

	p->type = TEMPORARY_VAR;

	p->u.temp = temp_serial_number;

	return p;
}

PSEUDO_MIPS_ASM_AST_Var PSEUDO_MIPS_ASM_AST_REGISTER_VAR(char *register_name)
{
	PSEUDO_MIPS_ASM_AST_Var p = (PSEUDO_MIPS_ASM_AST_Var) checked_malloc(sizeof(*p));

	p->type = REGISTER_VAR;

	p->u.reg = String(register_name);

	return p;
}

PSEUDO_MIPS_ASM_AST_expList PSEUDO_MIPS_ASM_AST_ExpList(PSEUDO_MIPS_ASM_AST_exp head, PSEUDO_MIPS_ASM_AST_expList tail)
{
	PSEUDO_MIPS_ASM_AST_expList p = (PSEUDO_MIPS_ASM_AST_expList) checked_malloc(sizeof(*p));

	p->head = head;
	p->tail = tail;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_PRINT_INT(void)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_PRINT_INT_EXP_TYPE;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_PRINT_CHAR(void)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_PRINT_CHAR_EXP_TYPE;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_ALLOCATE(void)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_ALLOCATE_EXP_TYPE;

	return p;
}

PSEUDO_MIPS_ASM_AST_exp PSEUDO_MIPS_ASM_AST_EXIT(void)
{
	PSEUDO_MIPS_ASM_AST_exp p = (PSEUDO_MIPS_ASM_AST_exp) checked_malloc(sizeof(*p));

	p->type = PSEUDO_MIPS_ASM_AST_EXIT_EXP_TYPE;

	return p;
}


