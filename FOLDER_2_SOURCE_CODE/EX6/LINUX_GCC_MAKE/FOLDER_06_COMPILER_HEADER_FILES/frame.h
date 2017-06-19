#ifndef __FRAME_H__
#define __FRAME_H__

/**********************/
/* FILE NAME: frame.h */
/**********************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_01_util.h"
#include "FILE_13_IR_tree.h"
#include "FILE_15_Temporaries_and_Labels.h"

/**********************/
/* EXTERNAL VARIABLES */
/**********************/
extern const int F_wordSize;

/*********/
/* TYPES */
/*********/
typedef struct F_frame_ *F_frame;
typedef struct F_access_ *F_access;

typedef struct F_accessList_ *F_accessList;
struct F_accessList_ {F_access head; F_accessList tail;};

/**************/
/* STRUCTURES */
/**************/
struct F_frame_
{
	int size;
	Temp_label label;
	F_accessList formals;
	int numLocalVariablesInFrame;
};

/*************/
/* REGISTERS */
/*************/
Temp_temp RV(void);
Temp_temp RA(void);
Temp_temp FP(void);
Temp_temp SP(void);

F_accessList F_AccessList(F_access head,F_accessList tail);

F_frame F_newFrame(Temp_label label,int numInputParameters);
Temp_label F_name(F_frame f);
F_accessList F_formals(F_frame f);
F_access F_allocLocal(F_frame f);

void F_updateFrameSize(F_frame f,int numOutgoingArgumentsOfSomeFunctionCalledFromf);
Temp_map F_tempMap;
Temp_tempList F_registers(void);
string F_getlabel(F_frame frame);
T_exp F_Exp(F_access acc,F_frame framePtr);
F_access F_allocLocal(F_frame f);
F_accessList F_formals(F_frame f);
extern const int F_wordSize;

T_exp F_externalCall(string s,T_expList args);

#endif
