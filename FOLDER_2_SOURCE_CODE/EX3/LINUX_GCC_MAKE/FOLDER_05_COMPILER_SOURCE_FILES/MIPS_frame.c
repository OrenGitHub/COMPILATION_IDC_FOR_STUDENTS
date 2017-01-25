/***************************/
/* FILE NAME: MIPS_frame.c */
/***************************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include "frame.h"
#include "FILE_01_util.h"
#include "FILE_15_Temporaries_and_Labels.h"

/**************/
/* CONST DATA */
/**************/
const int F_wordSize=4;
const int NUM_REGISTERS=0;
const int REGISTER_SIZE_IN_WORDS=1;
const int MEMORY_SPACE_TO_HOLD_RETURN_ADDRESS=4;

/*****************/
/* frame pointer */
/*****************/
Temp_temp FP(void)
{
	static Temp_temp fp=NULL;

	if (fp == NULL)
	{
		fp = Temp_newtemp("$fp");
	}

	return fp;
}

/*****************/
/* stack pointer */
/*****************/
Temp_temp SP(void)
{
	static Temp_temp sp=NULL;

	if (sp == NULL)
	{
		sp = Temp_newtemp("$sp");
	}

	return sp;
}

/****************/
/* return value */
/****************/
Temp_temp RV(void)
{
	static Temp_temp rv=NULL;

	if (rv == NULL)
	{
		rv = Temp_newtemp("$v0");
	}

	return rv;
}

/******************/
/* return address */
/******************/
Temp_temp RA(void)
{
	static Temp_temp ra=NULL;

	if (ra == NULL)
	{
		ra = Temp_newtemp("$ra");
	}

	return ra;
}

/*********/
/* ENUMS */
/*********/
typedef enum {inFrame, inReg} accessType;

/**************/
/* STRUCTURES */
/**************/
struct F_access_
{
	accessType kind;

	union
	{
		/************/
		/* in frame */
		/************/
		int offset;

		/**********/
		/* in reg */
		/**********/
		Temp_temp reg;
	} u;
};

static F_access InFrame(int offset)
{
	/**********************/
	/* [0] allocate space */
	/**********************/
	F_access p = (F_access) checked_malloc(sizeof(*p));

	/*************/
	/* [1] write */
	/*************/
	p->kind = inFrame;
	p->u.offset = offset;

	/**************/
	/* [2] return */
	/**************/
	return p;
}

static F_access InReg(Temp_temp reg)
{
	return NULL;
}

T_exp F_Exp(F_access access,F_frame framePtr)
{
	/**********************************************************/
	/* Space is allocated as an offset from the frame pointer */
	/**********************************************************/
	return T_Mem(T_Binop(T_plus,T_Temp(FP()),T_Const(access->u.offset)));
}

F_frame F_newFrame(Temp_label label, int numInputParameters)
{
	int i=0;
	F_accessList accessList=NULL;

	/*****************************/
	/* [0] Allocate memory space */
	/*****************************/
	F_frame p = (F_frame) checked_malloc(sizeof(*p));

	/*********************/
	/* [1] Update fields */
	/*********************/
	p->label = label;

	/***************************************/
	/* [2] starting with 0 local variables */
	/***************************************/
	p->numLocalVariablesInFrame=0;

	/**************************************/
	/* [3] compute accesses of parameters */
	/**************************************/
	for (i=0;i<numInputParameters;i++)
	{
		/**********************************************************************************/
		/* NOTE: this access list is built backwards from the last parameter to the first */
		/**********************************************************************************/
		/******************************************************************************************/
		/* NOTE: the +1 is for the return address, stored between the fp and the input parameters */
		/******************************************************************************************/
		accessList = F_AccessList(InFrame((numInputParameters+1-i)*F_wordSize),accessList);
	}

	/**************************/
	/* [4] update access list */
	/**************************/
	p->formals = accessList;

	/***************************************/
	/* [5] save some other space for later */
	/***************************************/
	p->size = 0;

	/**************/
	/* [6] return */
	/**************/
	return p;
}

F_access F_allocLocal(F_frame f)
{
	int numLocalVariablesInFrame = ++(f->numLocalVariablesInFrame);

	(f->size) += F_wordSize;

	return InFrame(0-F_wordSize*numLocalVariablesInFrame);
}

T_exp F_externalCall(string s,T_expList args)
{
	return T_Call(Temp_namedlabel(s),args);
}

F_accessList F_AccessList(F_access head, F_accessList tail)
{
	F_accessList p = (F_accessList) checked_malloc(sizeof(*p));
	
	p->head = head;
	p->tail = tail;

	return p;
}
