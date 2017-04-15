#ifndef __ROW_OPERATIONS_API_H__
#define __ROW_OPERATIONS_API_H__

/******************************************/
/* FILE NAME: FILE_13_RowOperations_API.h */
/******************************************/

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_12_RowOperations_AST.h"

/*******************/
/* EXTERN AST ROOT */
/*******************/
extern AST_RowOpList RowOperations_AST_ROOT;

/*************/
/* FUNCTIONS */
/*************/
AST_RowOpList Parse_Row_Operations(string Row_Operations_Filename);

#endif
