#ifndef __MAT_READER_AST_H__
#define __MAT_READER_AST_H__

/**************************************/
/* FILE NAME: FILE_07_MatReader_AST.h */
/**************************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_02_Fraction.h"
#include "FILE_03_Matrix.h"
#include "FILE_07_MatReader_AST.h"

/*********/
/* TYPES */
/*********/
typedef Matrix				AST_Mat;
typedef Fraction			AST_Number;
typedef struct AST_RowVec_	*AST_RowVec;

/*********/
/* CTORS */
/*********/
AST_Mat AST_Alloc_Mat1x2(AST_RowVec R1);
AST_Mat AST_Alloc_Mat1x3(AST_RowVec R1);
AST_Mat AST_Alloc_Mat1x4(AST_RowVec R1);

/*********/
/* CTORS */
/*********/
AST_Mat AST_Alloc_Mat2x2(AST_RowVec R1,AST_RowVec R2);
AST_Mat AST_Alloc_Mat2x3(AST_RowVec R1,AST_RowVec R2);
AST_Mat AST_Alloc_Mat2x4(AST_RowVec R1,AST_RowVec R2);

/*********/
/* CTORS */
/*********/
AST_Mat AST_Alloc_Mat3x2(AST_RowVec R1,AST_RowVec R2,AST_RowVec R3);
AST_Mat AST_Alloc_Mat3x3(AST_RowVec R1,AST_RowVec R2,AST_RowVec R3);
AST_Mat AST_Alloc_Mat3x4(AST_RowVec R1,AST_RowVec R2,AST_RowVec R3);

/*********/
/* CTORS */
/*********/
AST_Mat AST_Alloc_Mat4x2(AST_RowVec R1,AST_RowVec R2,AST_RowVec R3,AST_RowVec R4);
AST_Mat AST_Alloc_Mat4x3(AST_RowVec R1,AST_RowVec R2,AST_RowVec R3,AST_RowVec R4);
AST_Mat AST_Alloc_Mat4x4(AST_RowVec R1,AST_RowVec R2,AST_RowVec R3,AST_RowVec R4);

/*********/
/* CTORS */
/*********/
AST_Number AST_Alloc_Number(int nominator,int denominator);

#endif
