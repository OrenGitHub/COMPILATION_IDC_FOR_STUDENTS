/************/
/* semant.c */
/************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_02_symbol.h"
#include "FILE_03_StarKist_ErrorMsg.h"
#include "FILE_06_StarKist_AST.h"
#include "FILE_08_semant.h"
#include "FILE_10_SymbolTableEntry.h"
#include "FILE_11_types.h"

/**************************/
/* FUNCTIONS DECLARATIONS */
/**************************/
Ty_ty SEM_transExp(S_table venv,S_table tenv,A_exp exp);

void SEM_transVarDecInit(S_table venv,S_table tenv, A_dec dec)
{
	Ty_ty var_type;
	Ty_ty declared_type;
	Ty_ty type_of_init_exp;
	S_symbol type_name = dec->u.var_dec.type_name;

	/**********************/
	/* [1] trans init exp */
	/**********************/
	type_of_init_exp = SEM_transExp(venv,tenv,dec->u.var_dec.init);
	var_type = type_of_init_exp;

	/********************************************/
	/* [2] check if variable's type was defined */
	/********************************************/
	if (type_name != NULL)
	{
		/***************************************/
		/* [3] check if variable's type exists */
		/***************************************/
		if (S_look(tenv,type_name) == NULL)
		{
			EM_error(
				dec->pos,
				"unknown type %s\n",
				S_name(type_name));
		}

		/**********************************/
		/* [4] Find declared type in tenv */
		/**********************************/
		declared_type = (Ty_ty) S_look(tenv,type_name);

		/****************************************************************************************/
		/* [5] make sure the initialized value is the same as the declared type of the variable */
		/****************************************************************************************/
		if (type_of_init_exp != declared_type)
		{
			/************************************************************************/
			/* [6] Alternatively from [5], an initialization with NIL is also valid */
			/************************************************************************/
			if (((declared_type->kind == Ty_array) || (declared_type->kind == Ty_record)) && (type_of_init_exp == Ty_Nil()))
			{
				var_type = declared_type;
			}
			else if ((declared_type->kind == Ty_array) && (type_of_init_exp->kind == Ty_array))
			{
				if (declared_type->u.array != type_of_init_exp->u.array)
				{
					EM_error(
						dec->pos,
						"type mismatch in initialization of variable %s",
						S_name(dec->u.var_dec.var_name));
				}
			}
			else
			{
				EM_error(
					dec->pos,
					"type mismatch in initialization of variable %s",
					S_name(dec->u.var_dec.var_name));
			}
		}
	}

	/**********************************/
	/* [6] Enter the variable to venv */
	/**********************************/
	S_enter(venv,dec->u.var_dec.var_name,var_type);
}

void SEM_transVarDecNoInit(S_table venv,S_table tenv, A_dec dec)
{
	Ty_ty type;
	S_symbol type_name = dec->u.var_dec.type_name;

	/*********************************************/
	/* [1] make sure variable's type was defined */
	/*********************************************/
	if (type_name == NULL) 
	{
		EM_error(
			dec->pos,
			"could not determine variable type\n");
	}

	/***************************************/
	/* [2] check if variable's type exists */
	/***************************************/
	if (S_look(tenv,type_name) == NULL)
	{
		EM_error(
			dec->pos,
			"unknown type %s\n",
			S_name(type_name));
	}

	/*****************************/
	/* [3] Find the type in tenv */
	/*****************************/
	type = (Ty_ty) S_look(tenv,type_name);

	/**********************************/
	/* [4] Enter the variable to venv */
	/**********************************/
	S_enter(venv,type_name,type);	
}

void SEM_transVarDec(S_table venv,S_table tenv, A_dec dec)
{
	/********************************************************************/
	/* [0] Make sure the declaration is indeed a "variable" declaration */
	/********************************************************************/
	assert(dec->kind == A_varDec);

	/*************************************/
	/* [1] trans var with initialization */
	/*************************************/
	if (dec->u.var_dec.init != NULL)
	{
		SEM_transVarDecInit(venv,tenv,dec);
		return;
	}

	/****************************************/
	/* [2] trans var without initialization */
	/****************************************/
	if (dec->u.var_dec.init == NULL)
	{
		SEM_transVarDecNoInit(venv,tenv,dec);
		return;
	}
}

void SEM_transNameTypeDec(S_table venv,S_table tenv, A_dec dec)
{
	Ty_ty existing_type;
	S_symbol existing_type_name=dec->u.type_dec.ty.u.name;
	S_symbol currently_defined_type_name=dec->u.type_dec.type_name;

	/*****************************/
	/* EXAMPLE:	                 */
	/*                           */
	/* let                       */
	/*                           */
	/*     type oren_int := int  */
	/*     type dan__int := int  */
	/*                           */
	/*     var x:oren_int := 70  */
	/*     var y:dan__int := 80  */
	/*     var z:int      := 90  */
	/*                           */
	/* in                        */
	/*                           */
	/*     x+y+z                 */
	/*                           */
	/*****************************/

	/*****************************************************************************/
	/* [0] We try to define a new type [oren_int] based on an existing one [int] */
	/*     so first, find the existing type [int] in tenv                        */
	/*****************************************************************************/
	existing_type = (Ty_ty) S_look(tenv,existing_type_name);

	if (existing_type == NULL)
	{
		/*************************************************/
		/* [1] the supposedly existing type is not found */
		/*************************************************/
		EM_error(
			dec->pos,
			"undefined type %s\n",
			S_name(existing_type_name));
	}
	else
	{
		/*********************************************************************/
		/* [2] Enter the new currently defined type [oren_int] name to tenv  */
		/*     for all practical purposes, it is the same type as            */
		/*     the type that was used to define it [int]                     */
		/*********************************************************************/
		S_enter(tenv,currently_defined_type_name,existing_type);
		return;
	}
}

void SEM_transArrayTypeDec(S_table venv,S_table tenv, A_dec dec)
{
	S_symbol type_name = dec->u.type_dec.type_name;
	S_symbol array_of_what = dec->u.type_dec.ty.u.array;

	/**********************************************/
	/* [1] make sure the type of array is defined */
	/**********************************************/
	if (S_look(tenv,array_of_what) == NULL)
	{
		EM_error(
			dec->pos,
			"undefined type %s for array\n",
			S_name(array_of_what));
	}

	/******************************/
	/* [2] Enter new type to tenv */
	/******************************/
	S_enter(tenv,type_name,Ty_Array((Ty_ty) S_look(tenv,array_of_what)));
}

Ty_fieldList PrepareFieldsTypeList(S_table tenv,A_fieldList fields)
{
	Ty_ty field_type;
	S_symbol field_name=NULL;
	S_symbol field_type_name=NULL;
	Ty_fieldList fieldsTypesList=NULL;	

	if (fields == NULL) return NULL;

	field_name = fields->head->field_name;
	field_type_name = fields->head->field_type_name;

	field_type = (Ty_ty) S_look(tenv,field_type_name);

	return Ty_FieldList(Ty_Field(field_name,field_type),PrepareFieldsTypeList(tenv,fields->tail));
}

void SEM_transRecordTypeDec(S_table venv,S_table tenv, A_dec dec)
{
	S_table temp_env;
	S_symbol field_name=NULL;
	A_fieldList fields = NULL;
	S_symbol field_type_name=NULL;
	Ty_fieldList fieldTypePtr=NULL;
	Ty_fieldList fieldsTypesList=NULL;	
	S_symbol type_name=dec->u.type_dec.type_name;
	A_fieldList beginning_of_record = dec->u.type_dec.ty.u.record;

	/*************************************************************************************/
	/* [0] for recursive definitions, we enter the record name to declare its existance  */
	/*     however, its field list is only a dummy place holder. this is why we open a   */
	/*     scope for this record, process it, and once we are ready, we close the scope, */
	/*     and enter it to the tenv                                                      */
	/*************************************************************************************/
	S_beginScope(tenv);
	S_enter(tenv,type_name,Ty_DummyType());

	/**************************************************************************/
	/* [1] We have to make sure there are no two fields with the same name.   */
	/*     for that, we open a new environment, and make sure each field name */
	/*     wasn't previously defined in this record                           */
	/**************************************************************************/
	temp_env = E_base_tenv();
	S_beginScope(temp_env);

	/*********************************************/
	/* [2] for each field check two things:      */
	/*                                           */
	/*     [a] That its type exists, and         */
	/*     [b] No two fields with the same name  */
	/*                                           */
	/*********************************************/
	for (fields = beginning_of_record; fields != NULL;fields = fields->tail)
	{
		field_name = fields->head->field_name;
		field_type_name = fields->head->field_type_name;

		/***********************************/
		/* [2a] check that its type exists */
		/***********************************/

		/***************************************************************/
		/* [2b] check that there are no two fields with the same name */
		/***************************************************************/
	}
	
	/******************************/
	/* [3] SOMETHING HAPPENS HERE */
	/******************************/

	/*******************************/
	/* [4] Prepare field type list */
	/*******************************/
	fieldsTypesList = PrepareFieldsTypeList(tenv,beginning_of_record);

	/******************************/
	/* [5] SOMETHING HAPPENS HERE */
	/******************************/

	/********************************************/
	/* [6] check for recursive type definitions */
	/********************************************/
	for (fieldTypePtr = fieldsTypesList; fieldTypePtr != NULL; fieldTypePtr = fieldTypePtr->tail)
	{
	}

	/******************************/
	/* [7] SOMETHING HAPPENS HERE */
	/******************************/

	/******************************/
	/* [8] SOMETHING HAPPENS HERE */
	/******************************/
}

void SEM_transTypeDec(S_table venv,S_table tenv, A_dec dec)
{
	/************************************************************/
	/* [0] make sure declaration is indeed a "type" declaration */
	/************************************************************/
	assert(dec->kind == A_typeDec);

	/************************************************/
	/* [1] make sure type does not exist previously */
	/************************************************/
	if (S_look(tenv,dec->u.type_dec.type_name) != NULL)
	{
		EM_error(
			dec->pos,
			"type %s previously defined in this scope",
			S_name(dec->u.type_dec.type_name));
	}

	/********************************************************/
	/* [2] scan the declaration for simple, array or record */
	/********************************************************/
	switch (dec->u.type_dec.ty.kind) {
	case (A_nameTy):  SEM_transNameTypeDec(  venv,tenv,dec); return; 
	case (A_arrayTy): SEM_transArrayTypeDec( venv,tenv,dec); return; 
	case (A_recordTy):SEM_transRecordTypeDec(venv,tenv,dec); return; 
	}
}

void SEM_transFuncDec(S_table venv,S_table tenv, A_dec dec)
{
	Ty_ty type;
	Ty_ty resultType=NULL;
	S_symbol func_name = dec->u.func_dec.name;
	Ty_tyList parametersTypes=Ty_TyList(NULL,NULL);
	Ty_tyList temp=parametersTypes;
	A_fieldList functionParameters = dec->u.func_dec.params;

	/**************************************************************/
	/* [0] check type of the returned value in case it is defined */
	/**************************************************************/
	if (dec->u.func_dec.result != NULL)
	{
		resultType = (Ty_ty) S_look(tenv,dec->u.func_dec.result);
		if (resultType == NULL)
		{
			EM_error(
				dec->u.func_dec.pos,
				"Unknown returned type in function %s\n",
				S_name(func_name));
		}
	}

	/******************************************/
	/* [1] check types of function parameters */
	/******************************************/
	for (functionParameters = dec->u.func_dec.params;functionParameters;functionParameters=functionParameters->tail) 
	{
		type = (Ty_ty) S_look(tenv,functionParameters->head->field_type_name);
		if (type == NULL)
		{
			EM_error(
				dec->u.func_dec.pos,
				"unknown parameter type in function declaration\n",
				func_name);
		}
	}

	/***************************************************/
	/* [2] pack types of function parameters in a list */
	/***************************************************/
	for (functionParameters = dec->u.func_dec.params;functionParameters;functionParameters=functionParameters->tail) 
	{
		type = (Ty_ty) S_look(tenv,functionParameters->head->field_type_name);
		temp->tail = Ty_TyList(type,NULL);
		temp = temp->tail;
	}

	/**********************************************/
	/* [3] enter function to variable environment */
	/**********************************************/
	S_enter(venv,func_name,E_FunEntry(parametersTypes->tail,resultType,NULL));

	/*****************************************/
	/* [4] open a new scope for the function */
	/*****************************************/
	S_beginScope(venv);

	/************************************************/
	/* [5] enter parameters to variable environment */
	/************************************************/
	for (functionParameters = dec->u.func_dec.params;functionParameters;functionParameters=functionParameters->tail) 
	{
		type = (Ty_ty) S_look(tenv,functionParameters->head->field_type_name);
		S_enter(venv,functionParameters->head->field_name,type);
	}

	/**********************/
	/* [6] trans the body */
	/**********************/
	type=SEM_transExp(venv,tenv,dec->u.func_dec.body);
	if (dec->u.func_dec.result)
	{
		if ((resultType == type) || ((resultType->kind == Ty_record) && (type->kind == Ty_nil)))
		{
		}
		else
		{
			EM_error(dec->pos,"return value has different type from declaration");
		}
	}

	/***************************************/
	/* [7] close the scope of the function */
	/***************************************/
	S_endScope(venv);

	/**************************************************************************************/
	/* [8] enter function to variable environment in case returned type is only now known */
	/**************************************************************************************/
	S_enter(venv,func_name,E_FunEntry(parametersTypes->tail,type,NULL));

	/***************************/
	/* [9] free allocated data */
	/***************************/
	free(parametersTypes);
}

void SEM_transDecs(S_table venv,S_table tenv, A_decList decList)
{
	/**************************/
	/* [1] trans dec the head */
	/**************************/
	switch (decList->head->kind) {
	case (A_varDec):      SEM_transVarDec( venv,tenv,decList->head); break;
	case (A_typeDec):     SEM_transTypeDec(venv,tenv,decList->head); break;
	case (A_functionDec): SEM_transFuncDec(venv,tenv,decList->head); break;
	}

	/**************************/
	/* [2] trans dec the tail */
	/**************************/
	if (decList->tail != NULL) SEM_transDecs(venv,tenv,decList->tail);
}

Ty_ty SEM_transSeqExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;
	A_expList expList;

	/**********************/
	/* [0] Trans exp list */
	/**********************/
	for (expList=exp->u.seq; expList; expList = expList->tail)
	{
		/**********************/
		/* [1] Trans the head */
		/**********************/
		type=SEM_transExp(venv,tenv,expList->head);
	}
	
	/************************************************************************************/
	/* [2] the returned type of a seq expression is the last expression of the sequence */
	/************************************************************************************/
	return type;
}

Ty_ty SEM_transLetExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;

	/*************************************************************/
	/* [0] Make sure the expression is indeed a "let" expression */
	/*************************************************************/
	assert(exp->kind  == A_letExp);

	/*************************************************/
	/* [1] open a new variable and type environments */
	/*************************************************/
	S_beginScope(venv);
	S_beginScope(tenv);

	/***********************************/
	/* [2] Scan  the declarations part */
	/***********************************/
	SEM_transDecs(venv,tenv,exp->u.let.decs);

	/**********************************/
	/* [3] Scan  the expressions part */
	/**********************************/
	type=SEM_transExp(venv,tenv,exp->u.let.body);

	/****************************************************/
	/* [4] close the new variable and type environments */
	/****************************************************/
	S_endScope(venv);
	S_endScope(tenv);

	return type;
}

Ty_ty TypeCheck(Ty_ty left,Ty_ty right, A_oper op,int pos)
{
	switch (op) {
	case (A_andOp):
	case (A_orOp):

		if ((left == Ty_Int()) && (right == Ty_Int()))
		{
			return Ty_Int();
		}
		else
		{
			EM_error(pos,"Illegal use of operator(s) |,& between operands");
			return left;
		}

	case (A_plusOp):
	case (A_minusOp):
	case (A_timesOp):
	case (A_divideOp):

		if ((left == Ty_Int()) && (right == Ty_Int()))
		{
			return Ty_Int();
		}
		else
		{
			if ((left == Ty_Int())   && (right == Ty_Float())  ||
				(left == Ty_Float()) && (right == Ty_Int())    ||
				(left == Ty_Float()) && (right == Ty_Float()))
			{
				return Ty_Float();
			}
			else
			{
				EM_error(pos,"Illegal use of operator(s) +,-,*,/ between operands");
				return left;
			}
		}

	case (A_eqOp):
	case (A_neqOp):

		/******************************/
		/* Comparison between numbers */
		/******************************/
		if ((left == Ty_Int())    && (right == Ty_Int()))    {return Ty_Int();}
		if ((left == Ty_Int())    && (right == Ty_Float()))  {return Ty_Int();}
		if ((left == Ty_Float())  && (right == Ty_Int()))    {return Ty_Int();}
		if ((left == Ty_Float())  && (right == Ty_Float()))  {return Ty_Int();}

		/******************************/
		/* Comparison between strings */
		/******************************/
		if ((left == Ty_String()) && (right == Ty_String())) {return Ty_Int();}

		/******************************/
		/* Comparison between records */
		/******************************/
		if ((left->kind == Ty_record) && (right->kind == Ty_record)) {return Ty_Int();}
		if ((left->kind == Ty_record) && (right->kind == Ty_nil))    {return Ty_Int();}
		if ((left->kind == Ty_nil)    && (right->kind == Ty_record)) {return Ty_Int();}

	case (A_ltOp):
	case (A_leOp):
	case (A_gtOp):
	case (A_geOp):

		/******************************/
		/* Comparison between numbers */
		/******************************/
		if ((left == Ty_Int())    && (right == Ty_Int()))    {return Ty_Int();}
		if ((left == Ty_Int())    && (right == Ty_Float()))  {return Ty_Int();}
		if ((left == Ty_Float())  && (right == Ty_Int()))    {return Ty_Int();}
		if ((left == Ty_Float())  && (right == Ty_Float()))  {return Ty_Int();}

		/******************************/
		/* Comparison between strings */
		/******************************/
		if ((left == Ty_String()) && (right == Ty_String())) {return Ty_Int();}

		default:
			
			return NULL;
	}
}

Ty_ty SEM_transOpExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;
	Ty_ty left;
	Ty_ty right;

	/*************************************************************/
	/* [0] Make sure the expression is indeed an "op" expression */
	/*************************************************************/
	assert(exp->kind  == A_opExp);

	/******************************/
	/* [1] trans the left operand */
	/******************************/
	left = SEM_transExp(venv,tenv,exp->u.op.left);

	/*******************************/
	/* [2] trans the right operand */
	/*******************************/
	right = SEM_transExp(venv,tenv,exp->u.op.right);

	/****************************************************/
	/* [3] check validity of operation between operands */
	/****************************************************/
	type = TypeCheck(left,right,exp->u.op.oper,exp->pos);

	/****************/
	/* return value */
	/****************/
	return type;
}

Ty_ty SEM_transIntExp(S_table venv,S_table tenv,A_exp exp)
{
	/**************************************************************/
	/* [0] Make sure the expression is indeed an "int" expression */
	/**************************************************************/
	assert(exp->kind  == A_intExp);

	/**************/
	/* [1] return */
	/**************/
	return Ty_Int();
}

Ty_ty SEM_transNilExp(S_table venv,S_table tenv,A_exp exp)
{
	return Ty_Nil();
}

Ty_ty SEM_transFloatExp(S_table venv,S_table tenv,A_exp exp)
{
	/***************************************************************/
	/* [0] Make sure the expression is indeed a "float" expression */
	/***************************************************************/
	assert(exp->kind == A_floatExp);

	/**************/
	/* [1] return */
	/**************/	
	return Ty_Float();
}

Ty_ty SEM_transVarExp(S_table venv,S_table tenv,A_var var)
{
	Ty_ty type;
	Ty_fieldList fieldList;

	switch (var->kind) {
	case (A_simpleVar):

		/****************************/
		/* [0] check if type exists */
		/****************************/
		if (S_look(venv,var->u.simple) == NULL)
		{
			/*****************************/
			/* ERROR: type doesn't exist */
			/*****************************/
			EM_error(
				var->pos,
				"undefined variable %s\n",
				S_name(var->u.simple));
		}
	
		return (Ty_ty) S_look(venv,var->u.simple);

	case (A_fieldVar):;

	case (A_subscriptVar):
		
		var->u.subscript.var
		;

	}
}

void SEM_CheckIfAssignmentIsValid(Ty_ty type1,Ty_ty type2,int pos)
{
	/**********************/
	/* [1] Same types ... */
	/**********************/
	if (type1 == type2) return;

	/******************************************/
	/* [2] Assignment of nil to a record = OK */
	/******************************************/
	if ((type1->kind == Ty_record) && (type2 == Ty_Nil())) return;

	/******************************************/
	/* [3] Assignment of nil to an array = OK */
	/******************************************/
	if ((type1->kind == Ty_array) && (type2 == Ty_Nil())) return;

	/*******************************************************************************/
	/* [4] array assignment is valid only if they are both arrays of the same type */
	/*******************************************************************************/
	if ((type1->kind == Ty_array) && (type2->kind == Ty_array))
	{
		if (type1->u.array != type2->u.array)
		{
			EM_error(pos,"Illegal assignment, or onversion\n");
			return;
		}
		else
		{
			return;
		}
	}

	/********************************************/
	/* [5] Otherwise, the assignment is illegal */
	/********************************************/
	EM_error(pos,"Illegal assignment\n");
}

Ty_ty SEM_transAssignExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type1;
	Ty_ty type2;

	/**********************/
	/* [1] trans variable */
	/**********************/
	type1 = SEM_transVarExp(venv,tenv,exp->u.var);

	/************************************/
	/* [2] trans initialized expression */
	/************************************/
	type2 = SEM_transExp(venv,tenv,exp->u.assign.exp);
	
	/******************/
	/* [3] type check */
	/******************/
	SEM_CheckIfAssignmentIsValid(type1,type2,exp->pos);

	return type2;
}

Ty_ty SEM_transForExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;

	/*************************************************************/
	/* [0] Make sure the expression is indeed a "for" expression */
	/*************************************************************/
	assert(exp->kind == A_forExp);

	/**********************************************************/
	/* [1] Check lower bound of for loop is indeed an integer */
	/**********************************************************/
	type=SEM_transExp(venv,tenv,exp->u.forr.lo);
	if (type != Ty_Int())
	{
		EM_error(exp->pos,"lower bound of for loop is not an integer");
	}

	/**********************************************************/
	/* [2] Check upper bound of for loop is indeed an integer */
	/**********************************************************/
	type=SEM_transExp(venv,tenv,exp->u.forr.hi);
	if (type != Ty_Int())
	{
		EM_error(exp->pos,"upper bound of for loop is not an integer");
	}

	/************************************************************************/
	/* [3] Check that the for loop variable is not defined in current scope */
	/************************************************************************/
	if (S_look(venv,exp->u.forr.var) != NULL)
	{
		EM_error(exp->pos,"for loop variable already exists in current scope");
	}

	/***********************************/
	/* [4] enter loop variable to venv */
	/***********************************/
	S_enter(venv,exp->u.forr.var,Ty_Int());

	/**************************************/
	/* [5] trans the body of the for loop */
	/**************************************/
	(void) SEM_transExp(venv,tenv,exp->u.forr.body);

	/**************/
	/* [5] return */
	/**************/
	return Ty_Void();
}

Ty_ty SEM_transIfExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;

	/*************************************************************/
	/* [0] Make sure the expression is indeed an "if" expression */
	/*************************************************************/
	assert(exp->kind == A_ifExp);

	/*********************************************************************/
	/* [1] Check the test expression to make sure it has an integer type */
	/*********************************************************************/
	type=SEM_transExp(venv,tenv,exp->u.iff.test);
	if (type != Ty_Int())
	{
		EM_error(exp->pos,"condition in IF expression is not an integer");
		return NULL;
	}

	/***********************************/
	/* [2] trans the result expression */
	/***********************************/
	type=SEM_transExp(venv,tenv,exp->u.iff.then);

	return type;
}

E_enventry CheckIfFunctionExists(S_table venv,S_symbol functionName,A_pos pos)
{
	E_enventry enventry;

	enventry = (E_enventry) S_look(venv,functionName);
	if ((enventry == NULL) || (enventry->kind != E_funEntry))
	{
		EM_error(pos,"a call to an undefined function");
		return NULL;
	}

	return enventry;
}

void Check_Number_Of_Actual_Parameters_Sent_Match_Number_Of_Expected_Input_Parameters(
	S_symbol functionName,
	A_expList actualParametersSent,
	Ty_tyList expectedInputParameters,
	A_pos pos)
{
	for (;
		(actualParametersSent != NULL) ||
		(expectedInputParameters != NULL);
		actualParametersSent = actualParametersSent->tail,
		expectedInputParameters = expectedInputParameters->tail)
	{
		if ((actualParametersSent != NULL) && (expectedInputParameters == NULL))
		{
			EM_error(pos,"Too many parameters passed to function %s",S_name(functionName));
		}

		if ((actualParametersSent == NULL) && (expectedInputParameters != NULL))
		{
			EM_error(pos,"Too few parameters passed to function %s",S_name(functionName));
		}
	}
}

Ty_ty SEM_transCallExp(S_table venv,S_table tenv,A_exp exp)
{
	int i=0;
	Ty_ty type;
	Ty_ty expectedType;
	E_enventry enventry;
	A_expList actualParameterSentIterator=NULL;
	Ty_tyList expectedInputParameterTypeIterator=NULL;
	
	/*****************************/
	/* [1] Check function exists */
	/*****************************/
	enventry = CheckIfFunctionExists(venv,exp->u.call.func,exp->pos);

	/*************************************************************************/
	/* [2] Check that the numbe of sent parameters match the expected number */
	/*************************************************************************/
	Check_Number_Of_Actual_Parameters_Sent_Match_Number_Of_Expected_Input_Parameters(
		exp->u.call.func,
		exp->u.call.args,
		enventry->u.fun.formals,
		exp->pos);

	/***********************************************************/
	/* [3] Check that the arguments match their expected types */
	/***********************************************************/
	for (
		expectedInputParameterTypeIterator = enventry->u.fun.formals,
		actualParameterSentIterator = exp->u.call.args;
		expectedInputParameterTypeIterator &&
		actualParameterSentIterator;
		expectedInputParameterTypeIterator = expectedInputParameterTypeIterator->tail,
		actualParameterSentIterator = actualParameterSentIterator->tail)
	{
		/***********************/
		/* expected_field_type */
		/***********************/
		expectedType = expectedInputParameterTypeIterator->head;

		/********************************/
		/* actual field initalizer type */
		/********************************/
		type = SEM_transExp(venv,tenv,actualParameterSentIterator->head);

		/********************/
		/* check assignment */
		/********************/
		SEM_CheckIfAssignmentIsValid(expectedType,type,exp->pos);
	}

	/**********/
	/* return */
	/**********/
	return enventry->u.fun.result;
}

Ty_ty SEM_transAllocateArrayExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;

	type = (Ty_ty) S_look(tenv,exp->u.arrayInit.arrayType);

	if (type == NULL)
	{
		EM_error(exp->pos,"type of array (%s) is undefined\n",S_name(exp->u.arrayInit.arrayType));
		return NULL;
	}

	return Ty_Array(type);
}

Ty_ty CheckIfRecordTypeExists(S_table tenv,S_symbol recordType,A_pos pos)
{
	Ty_ty type;

	type = (Ty_ty) S_look(tenv,recordType);

	if (type == NULL)
	{
		EM_error(pos,"undefined record %s\n",S_name(recordType));
	}

	return type;
}

void Check_Number_Of_Record_Initializer_List_Match_Number_Of_Record_Fields(
	S_symbol recordType,
	A_expList fieldInitializerIterator,
	Ty_fieldList fieldTypeIterator,
	A_pos pos)
{
	for (;
		(fieldTypeIterator != NULL) ||
		(fieldInitializerIterator != NULL);
		fieldTypeIterator = fieldTypeIterator->tail,
		fieldInitializerIterator = fieldInitializerIterator->tail)
	{
		if ((fieldInitializerIterator != NULL) && (fieldTypeIterator == NULL))
		{
			EM_error(pos,"Too many initzlizer fields for record %s",S_name(recordType));
		}

		if ((fieldInitializerIterator == NULL) && (fieldTypeIterator != NULL))
		{
			EM_error(pos,"Too few initzlizer fields for record %s",S_name(recordType));
		}
	}
}

Ty_ty SEM_transAllocateRecordExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;
	Ty_ty expected_field_type;
	Ty_ty current_field_initalizer_type;
	Ty_fieldList fieldTypeIterator = NULL;
	A_expList fieldInitializerIterator = NULL;

	/************************************/
	/* [1] Make sure record type exists */
	/************************************/
	type = CheckIfRecordTypeExists(tenv,exp->u.recordInit.reocrdType,exp->pos);

	/*************************************************************************************/
	/* [2] Make sure number of record initializer list match the number of record fields */
	/*************************************************************************************/
	Check_Number_Of_Record_Initializer_List_Match_Number_Of_Record_Fields(
		exp->u.recordInit.reocrdType,
		exp->u.recordInit.initExpList,
		type->u.record,
		exp->pos);

	/*********************************************************************/
	/* [3] Make sure each field initizlizer type match its expected type */
	/*********************************************************************/
	for (
		fieldTypeIterator = type->u.record,
		fieldInitializerIterator = exp->u.recordInit.initExpList;
		fieldTypeIterator &&
		fieldInitializerIterator;
		fieldTypeIterator = fieldTypeIterator->tail,
		fieldInitializerIterator = fieldInitializerIterator->tail)
	{
		/***********************/
		/* expected_field_type */
		/***********************/
		expected_field_type = fieldTypeIterator->head->ty;

		/********************************/
		/* actual field initalizer type */
		/********************************/
		current_field_initalizer_type = SEM_transExp(venv,tenv,fieldInitializerIterator->head);

		/********************/
		/* check assignment */
		/********************/
		SEM_CheckIfAssignmentIsValid(expected_field_type,current_field_initalizer_type,exp->pos);
	}

	return type;
}

/****************/
/* SEM_transExp */
/****************/
Ty_ty SEM_transExp(S_table venv,S_table tenv,A_exp exp)
{
	switch (exp->kind) {
	case (A_opExp):             return SEM_transOpExp(            venv,tenv,exp);
	case (A_ifExp):             return SEM_transIfExp(            venv,tenv,exp);
	case (A_forExp):            return SEM_transForExp(           venv,tenv,exp);
	case (A_letExp):            return SEM_transLetExp(           venv,tenv,exp);
	case (A_nilExp):            return SEM_transNilExp(           venv,tenv,exp);
	case (A_intExp):            return SEM_transIntExp(           venv,tenv,exp);
	case (A_seqExp):            return SEM_transSeqExp(           venv,tenv,exp);
	case (A_varExp):            return SEM_transVarExp(           venv,tenv,exp->u.var);
	case (A_callExp):           return SEM_transCallExp(          venv,tenv,exp);
	case (A_floatExp):          return SEM_transFloatExp(         venv,tenv,exp);
	case (A_assignExp):         return SEM_transAssignExp(        venv,tenv,exp);
	case (A_allocateArrayExp):  return SEM_transAllocateArrayExp( venv,tenv,exp);
	case (A_allocateRecordExp): return SEM_transAllocateRecordExp(venv,tenv,exp);
	}
}

/*********************/
/* Semantic_Analysis */
/*********************/
void Semantic_Analysis(A_exp AST)
{
	S_table baseTypesEnv;
	S_table baseVariablesEnv;

	/****************************************************/
	/* [0] set up base variables and types environments */
	/****************************************************/
	baseTypesEnv = E_base_tenv();
	baseVariablesEnv = E_base_venv();

	/*********************************************/
	/* [1] enter basic types: int, float, string */
	/*********************************************/
	S_enter(baseTypesEnv,S_Symbol("int"),Ty_Int());
	S_enter(baseTypesEnv,S_Symbol("void"),Ty_Void());
	S_enter(baseTypesEnv,S_Symbol("float"),Ty_Float());
	S_enter(baseTypesEnv,S_Symbol("string"),Ty_String());

	/*****************************/
	/* [2] enter basic functions */
	/*****************************/
	S_enter(baseVariablesEnv,S_Symbol("PrintInt"),   E_FunEntry(Ty_TyList(Ty_Int(),   NULL),NULL,NULL));
	S_enter(baseVariablesEnv,S_Symbol("PrintFloat"), E_FunEntry(Ty_TyList(Ty_Float(), NULL),NULL,NULL));
	S_enter(baseVariablesEnv,S_Symbol("PrintString"),E_FunEntry(Ty_TyList(Ty_String(),NULL),NULL,NULL));

	/********************************/
	/* [3] trans the entire program */
	/********************************/
	SEM_transExp(baseVariablesEnv,baseTypesEnv,AST);
}
