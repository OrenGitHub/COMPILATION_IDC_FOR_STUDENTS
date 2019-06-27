#ifndef __TREE_H__
#define __TREE_H__

/*********************/
/* FILE NAME: tree.h */
/*********************/

/****************/
/* INCLUDE FILE */
/****************/
#include "FILE_15_Temporaries_and_Labels.h"

/***************/
/* DEFINITIONS */
/***************/
#define MAX_NAME_LENGTH_OF_IR_TREE_KIND 200

/*********/
/* TYPES */
/*********/
typedef struct T_exp_ *T_exp;
typedef struct T_expList_
{
	int PrintMyNodeSerialNumber;
	char PrintTheKindOfTreeIAm[MAX_NAME_LENGTH_OF_IR_TREE_KIND];

    T_exp head;
    struct T_expList_ *tail;
} T_expList_;

typedef struct T_expList_ *T_expList;

typedef enum {
	T_plus,
	T_minus,
	T_mul,
	T_div,
	T_and,
	T_or,
	T_lshift,
	T_rshift,
	T_arshift,
	T_xor,
	T_eq,
	T_ne,
	T_lt,
	T_gt,
	T_le,
	T_ge,
	T_numBinOps,
	T_invalidBinop,
} T_binOp;
typedef enum
{
	T_SEQ,
	T_LABEL,
	T_JUMP,
	T_CJUMP,
	T_MOVE,
	T_EXP,
	T_BINOP,
	T_MEM,
	T_TEMP,
	T_NAME,
	T_CONST,
	T_CALL,
	T_FUNCTION,
} T_ExpType;
typedef enum
{
	T_JUMP_REGISTER,
	T_JUMP_LABEL
} T_JumpExpType;

struct T_exp_
{
	T_ExpType kind;

	int PrintMyNodeSerialNumber;

	char PrintTheKindOfTreeIAm[MAX_NAME_LENGTH_OF_IR_TREE_KIND];

	union
	{
		T_exp MEM;
		Temp_temp TEMP;
		Temp_label NAME;
		Temp_label LABEL;

		struct
		{
			union
			{
				Temp_label label;
				Temp_temp temp;
			} u;

			T_JumpExpType type;
		}
		JUMP;

		int CONST;

		struct
		{
			T_exp src;
			T_exp dst;
		}
		MOVE;

		struct
		{
			T_exp left;
			T_exp right;
		}
		SEQ;

		struct
		{
			Temp_label name;
			T_exp prologue;
			T_exp body;
			T_exp epilogue;
			int numArguments;
		}
		FUNCTION;

		struct
		{
			Temp_label name;
			T_expList args;
		}
		CALL;

		struct
		{
			T_binOp op;
			T_exp left;
			T_exp right;
		}
		BINOP;

		struct
		{
			T_binOp op;
			T_exp left;
			T_exp right;
			Temp_label jumpToHereIfTrue;
			Temp_label jumpToHereIfFalse;
		}
		CJUMP;

		T_exp EXP;
	} u;
};

void SetSerialNumber(T_expList expList,int serialNumber);
T_exp T_Mem(T_exp);
T_exp T_Const(int i);
T_exp T_Temp(Temp_temp);
T_exp T_Label(Temp_label);
T_exp T_Move(T_exp dst, T_exp src);
T_exp T_JumpLabel(Temp_label label);
T_exp T_JumpRegister(Temp_temp temp);
T_exp T_Seq(T_exp left, T_exp right);
T_exp T_Call(Temp_label name, T_expList args);
T_exp T_Binop(T_binOp, T_exp left, T_exp right);
T_expList T_ExpList(T_exp head, T_expList tail);
T_exp T_Function(T_exp prologue, T_exp body, T_exp epilogue, Temp_label name);
T_exp T_Cjump(T_binOp op, T_exp left, T_exp right, Temp_label jumpToHereIfTrue, Temp_label jumpToHereIfFalse);

#endif
