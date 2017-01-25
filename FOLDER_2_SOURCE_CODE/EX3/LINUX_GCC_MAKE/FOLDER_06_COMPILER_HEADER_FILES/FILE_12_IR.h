#ifndef __IR_H__
#define __IR_H__

/*******************/
/* FILE NAME: IR.h */
/*******************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include "frame.h"
#include "FILE_01_util.h"
#include "FILE_06_StarKist_AST.h"

/****************/
/* IR_transProg */
/****************/
T_exp AST_To_IR(A_exp AST);

typedef struct IR_level_ *IR_level;
struct IR_level_ {IR_level parent; F_frame frame;};

typedef struct IR_access_ *IR_access;
struct IR_access_ {IR_level level; F_access access;};

typedef struct IR_accessList_ *IR_accessList;
struct IR_accessList_ {IR_access head; IR_accessList tail;};

IR_accessList IR_AccessList(IR_access head,IR_accessList tail);
IR_access IR_allocLocal(IR_level);

void IR_PrintTree(T_exp IR_tree,const char *filename);

#endif