#ifndef __ABSYN_H__
#define __ABSYN_H__

/**********************/
/* FILE NAME: absyn.h */
/**********************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include "symbol.h"

/***************/
/* DEFINITIONS */
/***************/
#define MAX_NAME_LENGTH_OF_ABSYN_TREE_KIND 100

/*********/
/* TYPES */
/*********/
typedef int A_pos;

typedef struct A_var_	*A_var;
typedef struct A_exp_	*A_exp;
typedef struct A_dec_	*A_dec;
typedef struct A_ty_	*A_ty;
typedef struct A_field_	*A_field;

typedef struct A_decList_		*A_decList;
typedef struct A_expList_		*A_expList;
typedef struct A_fieldList_		*A_fieldList;
typedef struct A_efieldList_	*A_efieldList;

typedef enum {
	A_plusOp,
	A_minusOp,
	A_timesOp,
	A_divideOp,
	A_eqOp,
	A_neqOp,
	A_ltOp,
	A_leOp,
	A_gtOp,
	A_geOp,
	A_andOp,
	A_orOp
} A_oper;

typedef enum {A_simpleVar, A_fieldVar, A_subscriptVar} VarType;

struct A_var_
{
	VarType kind;
    
	int PrintMyNodeSerialNumber;

	char PrintTheKindOfTreeIAm[MAX_NAME_LENGTH_OF_ABSYN_TREE_KIND];

	A_pos pos;

	union
	{
		S_symbol simple;
		
		struct {A_var var; S_symbol field_name;} field;
		struct {A_var var; A_exp exp;} subscript;
	} u;
};

typedef enum
{
	A_varExp,
	A_nilExp,
	A_intExp,
	A_floatExp,
	A_stringExp,
	A_callExp,
	A_opExp,
	A_recordExp,
	A_seqExp,
	A_assignExp,
	A_ifExp,
	A_whileExp,
	A_forExp,
	A_breakExp,
	A_letExp,
	A_arrayExp,
	A_allocateArrayExp,
	A_allocateRecordExp,
}
expType;

struct A_exp_
{
	expType kind;
	
	int PrintMyNodeSerialNumber;

	char PrintTheKindOfTreeIAm[MAX_NAME_LENGTH_OF_ABSYN_TREE_KIND];

	A_pos pos;

	union
	{
		A_var var;
		/* nil; - needs only the pos */
		int intt;
		float floatt;
		string stringg;
		struct {S_symbol func; A_expList args;} call;
		struct {A_oper oper; A_exp left; A_exp right;} op;
		struct {S_symbol typ; A_efieldList fields;} record;
		A_expList seq;
		struct {A_var var; A_exp exp;} assign;
		struct {A_exp test, then, elsee;} iff; /* elsee is optional */
		struct {A_exp test, body;} whilee;
		struct {S_symbol var; A_exp lo; A_exp hi; A_exp body;} forr;
		/* breakk; - need only the pos */
		struct {A_decList decs; A_exp body;} let;
		struct {S_symbol typ; A_exp size; A_exp init;} array;
		struct {S_symbol reocrdType; A_expList initExpList;} recordInit;
		struct {S_symbol arrayType; int size; int initializedValue;} arrayInit;
	} u;
};

typedef enum {A_functionDec, A_varDec, A_typeDec} declarationType;

typedef enum {A_nameTy, A_recordTy, A_arrayTy} Ty_Type;

typedef struct 
{
	Ty_Type kind;
	
	union
	{
		S_symbol name;
		A_fieldList record;
		S_symbol array;
	} u;
} A_ty_;

/****************/
/* DECLARATIONS */
/****************/
typedef struct {S_symbol type_name; A_ty_ ty;} A_typedec_;
typedef struct {S_symbol var_name; S_symbol type_name; A_exp init;} A_vardec_;
typedef struct {A_pos pos;S_symbol name; A_fieldList params; S_symbol result; A_exp body;} A_fundec_;

/***************/
/* DECLARATION */
/***************/
struct A_dec_ 
{
	declarationType kind;
	
	int PrintMyNodeSerialNumber;

	char PrintTheKindOfTreeIAm[MAX_NAME_LENGTH_OF_ABSYN_TREE_KIND];

	A_pos pos;
	
	union
	{
		A_fundec_ func_dec;
		
		A_vardec_ var_dec;
	    
		A_typedec_ type_dec;
	} u;
};

struct A_field_
{
	int PrintMyNodeSerialNumber;

	char PrintTheKindOfTreeIAm[MAX_NAME_LENGTH_OF_ABSYN_TREE_KIND];

	S_symbol field_name;
	S_symbol field_type_name;
	A_pos pos;
};

struct A_fieldList_
{
	A_field head;
	A_fieldList tail;

	int PrintMyNodeSerialNumber;

	char PrintTheKindOfTreeIAm[MAX_NAME_LENGTH_OF_ABSYN_TREE_KIND];
};

/***********************************/
/* Linked lists and nodes of lists */
/***********************************/
struct A_expList_
{
	int PrintMyNodeSerialNumber;
	char PrintTheKindOfTreeIAm[MAX_NAME_LENGTH_OF_ABSYN_TREE_KIND];

	A_exp head;
	A_expList tail;
};
struct A_decList_
{
	int PrintMyNodeSerialNumber;
	char PrintTheKindOfTreeIAm[MAX_NAME_LENGTH_OF_ABSYN_TREE_KIND];

	A_dec head;
	A_decList tail;
};

/* Function Prototypes */
A_var A_SimpleVar(A_pos pos, S_symbol sym);
A_var A_FieldVar(A_pos pos, A_var var, S_symbol sym);
A_var A_SubscriptVar(A_pos pos, A_var var, A_exp exp);
A_exp A_VarExp(A_pos pos, A_var var);
A_exp A_NilExp(A_pos pos);
A_exp A_IntExp(A_pos pos, int i);
A_exp A_FloatExp(A_pos pos, float f);
A_exp A_StringExp(A_pos pos, string s);
A_exp A_CallExp(A_pos pos, S_symbol func, A_expList args);
A_exp A_OpExp(A_pos pos, A_oper oper, A_exp left, A_exp right);
A_exp A_SeqExp(A_pos pos, A_expList seq);
A_exp A_AssignExp(A_pos pos, A_var var, A_exp exp);
A_exp A_IfExp(A_pos pos, A_exp test, A_exp then, A_exp elsee);
A_exp A_WhileExp(A_pos pos, A_exp test, A_exp body);
A_exp A_ForExp(A_pos pos, S_symbol var, A_exp lo, A_exp hi, A_exp body);
A_exp A_BreakExp(A_pos pos);
A_exp A_LetExp(A_pos pos, A_decList decs, A_exp body);
A_exp A_ArrayExp(A_pos pos, S_symbol typ, A_exp size, A_exp init);
A_exp A_AllocateArrayExp(A_pos pos, S_symbol typ, int arraySize, int initializedValue);
A_exp A_AllocateRecordExp(A_pos pos, S_symbol typ, A_expList fields);
A_dec A_FunDec(A_pos pos, S_symbol name, A_fieldList params, S_symbol result, A_exp body);
A_dec A_VarDec(A_pos pos, S_symbol var, S_symbol typ, A_exp init);
A_dec A_NameTypeDec(A_pos pos, S_symbol declared_type_name, S_symbol existing_type_name);
A_dec A_ArrayTypeDec(A_pos pos, S_symbol declared_array_type_name, S_symbol the_type_of_each_entry_in_the_array);
A_dec A_RecordTypeDec(A_pos pos, S_symbol declared_record_type_name, A_fieldList fieldList);
A_field A_Field(A_pos pos, S_symbol name, S_symbol typ);
A_fieldList A_FieldList(A_field head, A_fieldList tail);
A_expList A_ExpList(A_exp head, A_expList tail);
A_decList A_DecList(A_dec head, A_decList tail);

void ABSYN_PrintTree(A_exp ABSYN_tree,const char *filename);

#endif
