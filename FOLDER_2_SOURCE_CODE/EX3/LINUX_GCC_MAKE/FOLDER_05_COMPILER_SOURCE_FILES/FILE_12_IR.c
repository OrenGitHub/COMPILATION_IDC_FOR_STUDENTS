/*******************/
/* FILE NAEM: IR.c */
/*******************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "frame.h"
#include "FILE_02_symbol.h"
#include "FILE_03_StarKist_ErrorMsg.h"
#include "FILE_06_StarKist_AST.h"
#include "FILE_08_semant.h"
#include "FILE_10_SymbolTableEntry.h"
#include "FILE_11_Types.h"
#include "FILE_13_IR_tree.h"

/**************************/
/* FUNCTIONS DECLARATIONS */
/**************************/
T_exp IR_transExp(S_table venv,S_table tenv,A_exp exp,F_frame frame);

/**********************************/
/* HELPER FUNCTIONS :: PUSH & POP */
/**********************************/
T_exp PUSH(Temp_temp t)
{
	return T_Seq(
		T_Move(T_Temp(SP()),T_Binop(T_minus,T_Temp(SP()),T_Const(F_wordSize))),
		T_Move(T_Mem(T_Temp(SP())),T_Temp(t)));
}

T_exp POP(Temp_temp t)
{
	return T_Seq(
		T_Move(T_Temp(t),T_Mem(T_Temp(SP()))),
		T_Move(T_Temp(SP()),T_Binop(T_plus,T_Temp(SP()),T_Const(F_wordSize))));
}


/**********************************************************/
/* CONVERSION BETWEEN ABSTRACT SYNTAX BINOPS TO IR BINOPS */
/**********************************************************/
T_binOp ConvertAbstractSyntaxBinopsToIRBinops(A_oper abstractSyntaxBinop)
{
	switch (abstractSyntaxBinop) {
	case (A_plusOp):   return T_plus;
	case (A_minusOp):  return T_minus;
	case (A_timesOp):  return T_mul;
	case (A_divideOp): return T_div;
	case (A_eqOp):     return T_eq;
	case (A_neqOp):    return T_ne;
	case (A_ltOp):     return T_lt;
	case (A_leOp):     return T_le;
	case (A_gtOp):     return T_gt;
	case (A_geOp):     return T_ge;
	case (A_andOp):    return T_and;
	case (A_orOp):     return T_or;
	default:           return T_invalidBinop;
	}
}

T_exp IR_transVarDecInit(S_table venv,S_table tenv, A_dec dec, F_frame frame)
{
	F_access access = F_allocLocal(frame);
	Ty_ty type = SEM_transExp(venv,tenv,dec->u.var_dec.init);

	/******************************/
	/* [0] enter variable to venv */
	/******************************/
	S_enter(venv,dec->u.var_dec.var_name,E_VarEntry(type,access));

	/***********************************/
	/* [1] build a move representation */
	/***********************************/
	return T_Move(F_Exp(access,frame),IR_transExp(venv,tenv,dec->u.var_dec.init,frame));
}

T_exp IR_transVarDecNoInit(S_table venv,S_table tenv, A_dec dec, F_frame frame)
{
	F_access access = F_allocLocal(frame);
	Ty_ty type = (Ty_ty) S_look(tenv,dec->u.var_dec.type_name);

	/******************************/
	/* [0] enter variable to venv */
	/******************************/
	S_enter(venv,dec->u.var_dec.var_name,E_VarEntry(type,access));

	/****************************/
	/* [1] nothing to be done.. */
	/****************************/
	return NULL;
}

T_exp IR_transVarDec(S_table venv,S_table tenv, A_dec dec, F_frame frame)
{
	if (dec->u.var_dec.init != NULL)
	{
		/*************************************/
		/* [1] trans var with initialization */
		/*************************************/
		return IR_transVarDecInit(venv,tenv,dec,frame);
	}
	else
	{
		/****************************************/
		/* [2] trans var without initialization */
		/****************************************/
		return IR_transVarDecNoInit(venv,tenv,dec,frame);
	}
}

T_exp IR_transTypeDec(S_table venv,S_table tenv, A_dec dec)
{
	/***************************************************/
	/* [0] The only reason tenv needs to be maintained */
	/*     is to know the offsets of feilds in records */
	/***************************************************/
	SEM_transTypeDec(venv,tenv,dec);

	/***************************************************/
	/* [1] no translated IR code for type declarations */
	/***************************************************/
	return NULL;
}

T_exp IR_transFuncDec(S_table venv,S_table tenv, A_dec dec)
{
	T_exp body;
	F_frame frame;
	T_exp epilogue;
	T_exp prologue;
	int numParameters = 0;
	T_exp sp    =T_Temp(SP());
	T_exp sp_   =T_Temp(SP());
	T_exp sp__  =T_Temp(SP());
	T_exp sp___ =T_Temp(SP());
	T_exp sp____=T_Temp(SP());
	T_exp fp    =T_Temp(FP());
	T_exp fp_   =T_Temp(FP());
	T_exp fp__  =T_Temp(FP());
	T_exp store_return_address;
	T_exp update_new_frame_pointer;
	T_exp update_new_stack_pointer;
	T_exp save_previous_frame_pointer;
	T_exp restore_previous_frame_pointer;
	T_exp restore_previous_stack_pointer;
	T_exp jump_back_to_return_address;
	T_exp load_return_address;
	F_accessList formals=NULL;
	A_fieldList functionParameters = dec->u.func_dec.params;
	Temp_label skipThisFunctionForNow = Temp_newlabel("Skip_This_Function_For_Now");

	/*******************************************/
	/* [0] Create a new label for the function */
	/*******************************************/
	/**********************************************************************************************/
	/* NOTE: since nested functions are allowed, we can not use the function's name for its label */
	/**********************************************************************************************/
	Temp_label functionLabel = Temp_newlabel(S_name(dec->u.func_dec.name));

	/*********************************************/
	/* [1] compute number of incoming parameters */
	/*********************************************/
	for (functionParameters=dec->u.func_dec.params;functionParameters;functionParameters=functionParameters->tail) 
	{
		numParameters++;
	}

	/**************************/
	/* [2] Create a new frame */
	/**************************/
	frame = F_newFrame(functionLabel,numParameters);

	/******************************/
	/* [3] enter function to venv */
	/******************************/
	S_enter(venv,dec->u.func_dec.name,E_FunEntry(NULL,NULL,frame));

	/*****************************************/
	/* [4] open a new scope for the function */
	/*****************************************/
	S_beginScope(venv);

	/************************************************/
	/* [5] enter parameters to variable environment */
	/************************************************/
	for (
		formals = frame->formals,functionParameters=dec->u.func_dec.params;
		functionParameters;
		formals = formals->tail,functionParameters=functionParameters->tail) 
	{
		S_symbol parameter_name = functionParameters->head->field_name;
		S_symbol parameter_type_name = functionParameters->head->field_type_name;

		Ty_ty type = (Ty_ty) S_look(tenv,parameter_type_name);
		S_enter(venv,parameter_name,E_VarEntry(type,formals->head));
	}

	/**************************************/
	/* [6] trans the body of the function */
	/**************************************/
	body = IR_transExp(venv,tenv,dec->u.func_dec.body,frame);

	/***************************************/
	/* [7] close the scope of the function */
	/***************************************/
	S_endScope(venv);

	/***************************/
	/* [8-11] *** PROLOGUE *** */
	/***************************/

	/************************************/
	/* [8] push return address on stack */
	/************************************/
	store_return_address = T_Const(0);

	/***********************************/
	/* [9] save frame pointer המלך מת */
	/***********************************/
	save_previous_frame_pointer = T_Const(0);

	/********************************/
	/* [10] fp = sp יחי המלך החדש */
	/********************************/
	update_new_frame_pointer = T_Const(0);

	/*****************************/
	/* [11] sp = sp - frame size */
	/*****************************/
	update_new_stack_pointer = T_Const(0);
	
	/****************************/
	/* [12-15] *** EPILOGUE *** */
	/****************************/

	/****************************/
	/* [12] restore previous sp */
	/****************************/
	restore_previous_stack_pointer = T_Const(0);

	/****************************/
	/* [13] restore previous fp */
	/****************************/
	restore_previous_frame_pointer = T_Const(0);

	/****************************/
	/* [14] load return address */
	/****************************/
	load_return_address = T_Const(0);

	/************************************/
	/* [15] jump back to return address */
	/************************************/
	jump_back_to_return_address = T_Const(0);

	/*************************/
	/* [16] prepare prologue */
	/*************************/
	prologue = T_Seq(T_Const(0),T_Const(0));

	/*************************/
	/* [17] prepare epilogue */
	/*************************/
	epilogue = T_Seq(T_Const(0),T_Const(0));

	/***************************************************************************************/
	/* [18] this is tricky:                                                                */
	/*                                                                                     */
	/*     [a] write the label of the function                                             */
	/*     [b] generate the code for the function                                          */
	/*                                                                                     */
	/*     however, at the point the PC reaches this code, this function is NOT called, so */
	/*                                                                                     */
	/*     [c] add a jump instruction before, to skip the execution of this code           */
	/*     [d] add a label to know where to jump to                                        */
	/*                                                                                     */
	/***************************************************************************************/
	return
		T_Seq(
			T_JumpLabel(skipThisFunctionForNow),T_Seq(
			T_Function(prologue,body,epilogue,functionLabel),
			T_Label(skipThisFunctionForNow)));
}

T_exp IR_transDecs(S_table venv,S_table tenv, A_decList decList, F_frame frame)
{
	T_exp t=NULL;

	/*************************************************/
	/* [0] if there are no declarations - do nothing */
	/*************************************************/
	if (decList == NULL) return NULL;

	/**************************/
	/* [1] trans dec the head */
	/**************************/
	switch (decList->head->kind) {
	case (A_varDec):      t=IR_transVarDec( venv,tenv,decList->head,frame); break;
	case (A_typeDec):     t=IR_transTypeDec(venv,tenv,decList->head);       break;
	case (A_functionDec): t=IR_transFuncDec(venv,tenv,decList->head);       break;
	}

	/**************************/
	/* [2] trans dec the tail */
	/**************************/
	return T_Seq(t,IR_transDecs(venv,tenv,decList->tail,frame));
}

T_exp IR_transSeqExp(S_table venv,S_table tenv,A_exp exp,F_frame frame)
{
	T_exp t=NULL;
	A_expList expList=exp->u.seq;

	while (expList != NULL)
	{
		/**********************/
		/* [1] Trans the head */
		/**********************/
		t = T_Seq(t,IR_transExp(venv,tenv,expList->head,frame));

		/**********************/
		/* [2] Trans the tail */
		/**********************/
		expList = expList->tail;
	}
	
	return t;
}

T_exp IR_transLetExp(S_table venv,S_table tenv,A_exp exp,F_frame frame)
{
	T_exp t1;
	T_exp t2;

	/*************************************************/
	/* [0] open a new variable and type environments */
	/*************************************************/
	S_beginScope(venv);
	S_beginScope(tenv);

	/***********************************/
	/* [1] trans the declarations part */
	/***********************************/
	t1 = IR_transDecs(venv,tenv,exp->u.let.decs,frame);

	/**********************************/
	/* [2] trans the expressions part */
	/**********************************/
	t2 = IR_transExp(venv,tenv,exp->u.let.body,frame);

	/****************************************************/
	/* [3] close the new variable and type environments */
	/****************************************************/
	S_endScope(venv);
	S_endScope(tenv);

	/***********************************************************************************/
	/* [4] build seq expression for possible initializations done in declarations part */
	/***********************************************************************************/
	return T_Seq(t1,t2);
}

T_exp IR_transOpExp(S_table venv,S_table tenv,A_exp exp,F_frame frame)
{
	T_exp left;
	T_exp right;

	T_binOp op = ConvertAbstractSyntaxBinopsToIRBinops(exp->u.op.oper);

	/******************************/
	/* [1] trans the left operand */
	/******************************/
	left = IR_transExp(venv,tenv,exp->u.op.left,frame);

	/*******************************/
	/* [2] trans the right operand */
	/*******************************/
	right = IR_transExp(venv,tenv,exp->u.op.right,frame);

	/****************************/
	/* [3] return op expression */
	/****************************/
	switch (exp->u.op.oper)
	{
	case (A_orOp):
	case (A_andOp):
	case (A_plusOp):
	case (A_minusOp):
	case (A_timesOp):
	case (A_divideOp):
		
		/********************/
		/* binary operation */
		/********************/
		return T_Binop(op,left,right);
	
	case (A_eqOp):
	case (A_ltOp):
	case (A_leOp):
	case (A_gtOp):
	case (A_geOp):
	case (A_neqOp):

		{
			/****************************/
			/* Allocate A New Temporary */
			/****************************/
			Temp_temp temp = Temp_newtemp("");

			/********************************/
			/* Allocate Fresh Unique Labels */
			/********************************/
			Temp_label T   = Temp_newlabel("T");
			Temp_label F   = Temp_newlabel("F");
			Temp_label END = Temp_newlabel("END");

			/*******************/
			/* binary relation */
			/*******************/
			return T_Seq(
						T_Seq(
							T_Cjump(op,left,right,T,F),
							T_Seq(
								T_Seq(
									T_Label(T),
									T_Seq(
										T_Move(T_Temp(temp),T_Const(1)),
										T_JumpLabel(END))),
								T_Seq(
									T_Label(F),
									T_Seq(
										T_Move(T_Temp(temp),T_Const(0)),
										T_JumpLabel(END))))),
						T_Seq(T_Label(END),T_Temp(temp)));
		}
	}
}

T_exp IR_transIntExp(S_table venv,S_table tenv,A_exp exp)
{
	return T_Const(exp->u.intt);
}

T_exp IR_transNilExp(S_table venv,S_table tenv,A_exp exp)
{
	/***************************************/
	/* [1] Just like in C, NIL has value 0 */
	/***************************************/
	return T_Const(0);
}

T_exp IR_transFloatExp(S_table venv,S_table tenv,A_exp exp)
{	
	return T_Const(exp->u.intt);
}

struct expty IR_transVarExp(S_table venv,S_table tenv,A_var var,F_frame frame)
{
	Ty_ty type;
	int fieldOffset=0;
	E_enventry envEntry;
	Ty_fieldList fieldList;
	struct expty e={NULL,NULL};
	T_exp boundaries_checks=NULL;
	T_exp check_initialization=NULL;
	T_exp check_subscript_ge_than_zero=NULL;
	Temp_label access_violation_label = Temp_newlabel("access_violation");
	Temp_label everything_is_ok_label = Temp_newlabel("everything_is_ok");
	Temp_label initialization_ok_label = Temp_newlabel("initialization_ok");
	Temp_label subscript_ge_than_zero_ok_label = Temp_newlabel("subscript_ge_than_zero_ok");
	Temp_label subscript_le_than_actual_memory_size_allocated_on_heap_ok_label = Temp_newlabel("subscript_le_than_actual_memory_size_allocated_on_heap");
	T_exp check_subscript_le_than_actual_memory_size_allocated_on_heap=NULL;

	switch (var->kind) {
	case (A_simpleVar):

		/*********************************/
		/* for example,                  */
		/*                               */
		/* type salary = int             */
		/*                               */
		/* salary mySalary := 80         */
		/*                               */
		/* mySalary is a simple variable */
		/*********************************/

		/**********************/
		/* [0] find var entry */
		/**********************/
		envEntry = (E_enventry) S_look(venv,var->u.simple);

		/*****************/
		/* [1] build exp */
		/*****************/
		e.exp = F_Exp(envEntry->u.var.access,frame);
		e.ty = envEntry->u.var.type;

		/**************/
		/* [2] return */
		/**************/
		return e;

	case (A_fieldVar):

		/***************************************************************/
		/* for example,                                                */
		/*                                                             */
		/* type salary = int                                           */
		/* type date = {year:int, month:int, day:int, time:float}      */
		/* type employee = {mySalary:salary, startWorking:date}        */
		/*                                                             */
		/* employee oren                                               */
		/*                                                             */
		/* oren->startWorking->time = 23.54 (6 minutes before 24.00)   */
		/*                                                             */
		/* the recursive call will be with variable oren->startWorking */
		/*                                                             */
		/* the following documentation uses [RECORD]->field            */
		/*                                                             */
		/* and in this example: RECORD is oren->startWorking           */
		/*                      field  is time                         */
		/***************************************************************/

		/********************/
		/* [0] trans RECORD */
		/********************/
		e = IR_transVarExp(venv,tenv,var->u.field.var,frame);

		/*******************************************************************************************/
		/* [1] build exp: take return address of record and add the shift needed for current field */
		/*                                                                                         */
		/* in the example above, take the address of oren->startWorking and add 3*sizeof(int)      */
		/*                                                                                         */
		/*******************************************************************************************/

		/*************************/
		/* [1a] read record type */
		/*************************/
		type = e.ty;

		/*********************************/
		/* [1b] find field in field list */
		/*********************************/
		for (fieldList=type->u.record;fieldList;fieldList=fieldList->tail,fieldOffset++)
		{
			if (var->u.field.field_name == fieldList->head->name)
			{
				break;
			}
		}

		/******************************/
		/* [1c] compute actual offset */
		/******************************/
		e.exp = T_Mem(T_Binop(T_plus,e.exp,T_Const(fieldOffset * F_wordSize)));
		e.ty = fieldList->head->ty;

		/**************/
		/* [2] return */
		/**************/
		return e;

	case (A_subscriptVar):

		/*******************/
		/* [0] trans ARRAY */
		/*******************/
		e = IR_transVarExp(venv,tenv,var->u.subscript.var,frame);

		/******************************************************************************/
		/* [1] Boundaries checks consist of:                                          */
		/*                                                                            */
		/*     [a] check is array was initialized. i.e. it is not nil                 */
		/*                                                                            */
		/*     [b] check that subscript is >= 0                                       */
		/*                                                                            */
		/*     [c] check that subscript is <= allocated size of the array on the heap */ 
		/*                                                                            */
		/******************************************************************************/
		check_initialization = T_Const(0);

		check_subscript_ge_than_zero = T_Const(0);
			
		check_subscript_le_than_actual_memory_size_allocated_on_heap = T_Const(0);

		boundaries_checks =
			T_Seq(
				check_initialization,
				T_Seq(
					check_subscript_ge_than_zero,
					T_Seq(
						check_subscript_le_than_actual_memory_size_allocated_on_heap,
						T_Seq(
							T_Label(subscript_le_than_actual_memory_size_allocated_on_heap_ok_label),
							T_Seq(
								T_JumpLabel(everything_is_ok_label),
								T_Seq(
									T_Label(access_violation_label),
									T_Seq(
										F_externalCall("Label_4_Access_Violation",NULL),
										T_Label(everything_is_ok_label))))))));

		/*****************************/
		/* [2] compute actual offset */
		/*****************************/
		e.exp = T_Const(0);

		/************/
		/* [3] type */
		/************/
		e.ty = e.ty->u.array;

		/**************/
		/* [4] return */
		/**************/
		return e;
	}
}

T_exp IR_transAssignExp(S_table venv,S_table tenv,A_exp exp,F_frame frame)
{
	T_exp t;

	struct expty e;

	/************************/
	/* [1] trans expression */
	/************************/
	t = IR_transExp(venv,tenv,exp->u.assign.exp,frame);

	/**********************/
	/* [2] trans variable */
	/**********************/
	e = IR_transVarExp(venv,tenv,exp->u.var,frame);
	
	/*********************/
	/* [3] move t1 to t2 */
	/*********************/
	return T_Move(e.exp,t);
}

T_exp IR_transForExp(S_table venv,S_table tenv,A_exp exp,F_frame frame)
{
	T_exp one;

	T_exp low;
	T_exp low_;
	T_exp high;
	T_exp high_;
	T_exp body;

	T_exp localLoopVariable;
	T_exp localLoopVariable_;
	T_exp localLoopVariable__;
	T_exp localLoopVariable___;
	T_exp localLoopVariable_plus_1;
	T_exp localLoopVariable_plus_plus;
	T_exp localLoopVariable_equals_low;

	/****************************************/
	/* [0] create start and end loop labels */
	/****************************************/
	Temp_label loop      = Temp_newlabel("for_loop");
	Temp_label exitLoop  = Temp_newlabel("exit_loop");

	/************************************/
	/* [1] allocate local loop variable */
	/************************************/
	F_access access = F_allocLocal(frame);

	/*****************************************/
	/* [2] enter local loop variable to venv */
	/*****************************************/
	S_enter(venv,exp->u.forr.var,E_VarEntry(NULL,access));

	/*************************************/
	/* [3] trans lower bound of for loop */
	/*************************************/
	low=IR_transExp(venv,tenv,exp->u.forr.lo,frame);
	low_=IR_transExp(venv,tenv,exp->u.forr.lo,frame);

	/*************************************/
	/* [4] trans upper bound of for loop */
	/*************************************/
	high=IR_transExp(venv,tenv,exp->u.forr.hi,frame);
	high_=IR_transExp(venv,tenv,exp->u.forr.hi,frame);

	/******************************/
	/* [5] trans body of for loop */
	/******************************/
	body=IR_transExp(venv,tenv,exp->u.forr.body,frame);

	/******************************************************/
	/* [6] create IR building blocks for "for" expression */
	/******************************************************/
	one                          = T_Const(1);
	localLoopVariable            = F_Exp(access,frame);
	localLoopVariable_           = F_Exp(access,frame);
	localLoopVariable__          = F_Exp(access,frame);
	localLoopVariable___         = F_Exp(access,frame);
	localLoopVariable_equals_low = T_Move(localLoopVariable_,low);
	localLoopVariable_plus_1     = T_Binop(T_plus,localLoopVariable__,one);
	localLoopVariable_plus_plus  = T_Move(localLoopVariable___,localLoopVariable_plus_1);

	/*************************************************/
	/* [7] build IR "for" expression from its blocks */
	/*************************************************/
	return
		T_Seq(
			T_Seq(
				localLoopVariable_equals_low,
				T_Seq(
					T_Cjump(T_le,low_,high_,loop,exitLoop),
					T_Seq(
						T_Label(loop),
						T_Seq(
							T_Seq(body,localLoopVariable_plus_plus),
							T_Cjump(T_le,localLoopVariable,high,loop,exitLoop))))),
			T_Label(exitLoop));
}

T_exp IR_transIfExp(S_table venv,S_table tenv,A_exp exp,F_frame frame)
{
	T_exp testExpression;
	T_exp thenExpression;
	Temp_label jumpToHereIfTrue  = Temp_newlabel("if_taken");
	Temp_label jumpToHereIfFalse = Temp_newlabel("if_not_taken");

	/********************************/
	/* [1] build IR test expression */
	/********************************/
	testExpression=IR_transExp(venv,tenv,exp->u.iff.test,frame);

	/****************************************/
	/* [2] build IR do_something expression */
	/****************************************/
	thenExpression=IR_transExp(venv,tenv,exp->u.iff.then, frame);

	/*******************************/
	/* [3] return IR if expression */
	/*******************************/
	return
		T_Seq(
			T_Seq(
				T_Cjump(
					T_ne,
					testExpression,
					T_Const(0),
					jumpToHereIfTrue,
					jumpToHereIfFalse),
				T_Seq(
					T_Label(jumpToHereIfTrue),
					thenExpression)),
			T_Label(jumpToHereIfFalse));
			
}

T_exp IR_transCallExp(S_table venv,S_table tenv,A_exp exp,F_frame frame)
{
	T_exp t=NULL;
	A_expList args=NULL;
	E_enventry envEntry=NULL;
	T_expList expListPtr=T_ExpList(NULL,NULL);
	T_expList expList=NULL;
	Temp_label functionLabel=NULL;

	/******************************/
	/* [0] extract function label */
	/******************************/
	envEntry = (E_enventry) S_look(venv,exp->u.call.func);
	functionLabel = envEntry->u.fun.frame->label;

	/*******************************/
	/* [1] translate each argument */
	/*******************************/
	for (args = exp->u.call.args; args != NULL; args = args->tail)
	{
		expList = T_ExpList(IR_transExp(venv,tenv,args->head,frame),expList);
	}

	/*******************************/
	/* [2] build a call expression */
	/*******************************/
	return T_Call(functionLabel,expList);
}

T_exp IR_transAllocteRecordExp(S_table venv,S_table tenv,A_exp exp,F_frame frame)
{
	int numRecordFields=0;
	A_expList initExpList;
	T_expList expList=NULL;
	T_expList expListWithNumRecordFields=NULL;

	/***********************/
	/* [1] IR the exp list */
	/***********************/
	for (initExpList=exp->u.recordInit.initExpList;initExpList;initExpList=initExpList->tail)
	{
		expList = T_ExpList(IR_transExp(venv,tenv,initExpList->head,frame),expList);
		
		/****************************************************/
		/* [2] and count the number of fields in the record */
		/****************************************************/
		numRecordFields++;
	}

	/***********************************************************/
	/* [3] Add the number of fields to the end of the exp list */
	/***********************************************************/
	for (expListWithNumRecordFields=expList;expList->tail;expList=expList->tail);
	expList->tail = T_ExpList(T_Const(numRecordFields),NULL);

	/**************************************************/
	/* [4] F_externalCall is essentially a T_Call ... */
	/**************************************************/
	return F_externalCall("Label_1_AllocateRecord",expListWithNumRecordFields);
}

T_exp IR_transAllocteArrayExp(S_table venv,S_table tenv,A_exp exp)
{
	T_expList expListWithArraySize=NULL;

	/************************************************************/
	/* [1] Add the size of the array to the end of the exp list */
	/************************************************************/
	expListWithArraySize =
		T_ExpList(
			T_Const(exp->u.arrayInit.initializedValue),
			T_ExpList(T_Const(exp->u.arrayInit.size),NULL));

	/**************************************************/
	/* [2] F_externalCall is essentially a T_Call ... */
	/**************************************************/
	return F_externalCall("Label_2_AllocateArray",expListWithArraySize);
}

/****************/
/* IR_transExp */
/****************/
T_exp IR_transExp(S_table venv,S_table tenv,A_exp exp,F_frame frame)
{
	struct expty e;

	switch (exp->kind) {
	case (A_opExp):            return IR_transOpExp(           venv,tenv,exp,frame);
	case (A_ifExp):            return IR_transIfExp(           venv,tenv,exp,frame);
	case (A_forExp):           return IR_transForExp(          venv,tenv,exp,frame);
	case (A_letExp):           return IR_transLetExp(          venv,tenv,exp,frame);
	case (A_intExp):           return IR_transIntExp(          venv,tenv,exp);
	case (A_nilExp):           return IR_transNilExp(          venv,tenv,exp);
	case (A_seqExp):           return IR_transSeqExp(          venv,tenv,exp,frame);
	case (A_varExp):           e =    IR_transVarExp(          venv,tenv,exp->u.var,frame); return e.exp;
	case (A_callExp):          return IR_transCallExp(         venv,tenv,exp,frame);
	case (A_floatExp):         return IR_transFloatExp(        venv,tenv,exp);
	case (A_assignExp):        return IR_transAssignExp(       venv,tenv,exp,frame);
	case (A_allocateArrayExp): return IR_transAllocteArrayExp( venv,tenv,exp);
	case (A_allocateRecordExp):return IR_transAllocteRecordExp(venv,tenv,exp,frame);
	}
}

/*************/
/* AST_To_IR */
/*************/
T_exp AST_To_IR(A_exp AST)
{
	F_frame main;
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

	/****************************************************/
	/* [2] enter system functions: printFloat, printInt */
	/****************************************************/
	S_enter(baseVariablesEnv,S_Symbol("PrintInt"),   E_FunEntry(NULL,NULL,F_newFrame(Temp_newlabel("PrintInt"),1)));
	S_enter(baseVariablesEnv,S_Symbol("PrintFloat"), E_FunEntry(NULL,NULL,F_newFrame(Temp_newlabel("PrintFloat"),1)));
	S_enter(baseVariablesEnv,S_Symbol("PrintString"),E_FunEntry(NULL,NULL,F_newFrame(Temp_newlabel("PrintString"),1)));

	/******************************/
	/* [3] open new frame: "main" */
	/******************************/
	main = F_newFrame(Temp_newlabel("main"),0);

	/********************************/
	/* [4] trans the entire program */
	/********************************/
	return IR_transExp(baseVariablesEnv,baseTypesEnv,AST,main);
}
