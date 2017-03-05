/**************************************/
/* FILE NAME: FILE_05_MatReader_AST.c */
/**************************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_07_MatReader_AST.h"

/***************/
/* DEFINITIONS */
/***************/
#define MAX_NUM_COLS 5

/****************/
/* STRUCT TYPES */
/****************/
struct AST_RowVec_
{
	AST_Number RowVec[MAX_NUM_COLS];
};

/*********/
/* CTORS */
/*********/
AST_RowVec AST_Alloc_RowVec2(AST_Number x,AST_Number y)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_RowVec p = (AST_RowVec) checked_malloc(sizeof(*p));

	/****************/
	/* CLEAR MEMORY */
	/****************/
	memset(p->RowVec,0,sizeof(p->RowVec));
	
	/************/
	/* COPY ... */
	/************/
	p->RowVec[0]=x;
	p->RowVec[1]=y;
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}
AST_RowVec AST_Alloc_RowVec3(AST_Number x,AST_Number y,AST_Number z)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_RowVec p = (AST_RowVec) checked_malloc(sizeof(*p));

	/****************/
	/* CLEAR MEMORY */
	/****************/
	memset(p->RowVec,0,sizeof(p->RowVec));
	
	/************/
	/* COPY ... */
	/************/
	p->RowVec[0]=x;
	p->RowVec[1]=y;
	p->RowVec[2]=z;
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}

AST_RowVec AST_Alloc_RowVec4(AST_Number x,AST_Number y,AST_Number z,AST_Number w)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_RowVec p = (AST_RowVec) checked_malloc(sizeof(*p));

	/****************/
	/* CLEAR MEMORY */
	/****************/
	memset(p->RowVec,0,sizeof(p->RowVec));
	
	/************/
	/* COPY ... */
	/************/
	p->RowVec[0]=x;
	p->RowVec[1]=y;
	p->RowVec[2]=z;
	p->RowVec[3]=w;
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}

/*********/
/* CTORS */
/*********/
AST_Mat AST_Alloc_Mat1x2(AST_RowVec R1)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_Mat p = AllocateMatrix();

	/****************/
	/* CLEAR MEMORY */
	/****************/
	ClearMatrix(p);
	
	/**************/
	/* ROW & COLS */
	/**************/
	SetNumRows(p,1);
	SetNumCols(p,2);
	
	/************/
	/* COPY ... */
	/************/
	SetMatEntry(p,0,0,R1->RowVec[0]);
	SetMatEntry(p,0,1,R1->RowVec[1]);
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}
AST_Mat AST_Alloc_Mat1x3(AST_RowVec R1)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_Mat p = AllocateMatrix();

	/****************/
	/* CLEAR MEMORY */
	/****************/
	ClearMatrix(p);
	
	/**************/
	/* ROW & COLS */
	/**************/
	SetNumRows(p,1);
	SetNumCols(p,3);
	
	/************/
	/* COPY ... */
	/************/
	SetMatEntry(p,0,0,R1->RowVec[0]);
	SetMatEntry(p,0,1,R1->RowVec[1]);
	SetMatEntry(p,0,2,R1->RowVec[2]);
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}
AST_Mat AST_Alloc_Mat1x4(AST_RowVec R1)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_Mat p = AllocateMatrix();

	/****************/
	/* CLEAR MEMORY */
	/****************/
	ClearMatrix(p);
	
	/**************/
	/* ROW & COLS */
	/**************/
	SetNumRows(p,1);
	SetNumCols(p,4);
	
	/************/
	/* COPY ... */
	/************/
	SetMatEntry(p,0,0,R1->RowVec[0]);
	SetMatEntry(p,0,1,R1->RowVec[1]);
	SetMatEntry(p,0,2,R1->RowVec[2]);
	SetMatEntry(p,0,3,R1->RowVec[3]);
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}

/*********/
/* CTORS */
/*********/
AST_Mat AST_Alloc_Mat2x2(AST_RowVec R1,AST_RowVec R2)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_Mat p = AllocateMatrix();

	/****************/
	/* CLEAR MEMORY */
	/****************/
	ClearMatrix(p);
	
	/**************/
	/* ROW & COLS */
	/**************/
	SetNumRows(p,2);
	SetNumCols(p,2);
	
	/************/
	/* COPY ... */
	/************/
	SetMatEntry(p,0,0,R1->RowVec[0]);
	SetMatEntry(p,0,1,R1->RowVec[1]);
	SetMatEntry(p,1,0,R2->RowVec[0]);
	SetMatEntry(p,1,1,R2->RowVec[1]);
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}
AST_Mat AST_Alloc_Mat2x3(AST_RowVec R1,AST_RowVec R2)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_Mat p = AllocateMatrix();

	/****************/
	/* CLEAR MEMORY */
	/****************/
	ClearMatrix(p);
	
	/**************/
	/* ROW & COLS */
	/**************/
	SetNumRows(p,2);
	SetNumCols(p,3);
	
	/************/
	/* COPY ... */
	/************/
	SetMatEntry(p,0,0,R1->RowVec[0]);
	SetMatEntry(p,0,1,R1->RowVec[1]);
	SetMatEntry(p,0,2,R1->RowVec[2]);
	SetMatEntry(p,1,0,R2->RowVec[0]);
	SetMatEntry(p,1,1,R2->RowVec[1]);
	SetMatEntry(p,1,2,R2->RowVec[2]);
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}
AST_Mat AST_Alloc_Mat2x4(AST_RowVec R1,AST_RowVec R2)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_Mat p = AllocateMatrix();

	/****************/
	/* CLEAR MEMORY */
	/****************/
	ClearMatrix(p);
	
	/**************/
	/* ROW & COLS */
	/**************/
	SetNumRows(p,2);
	SetNumCols(p,4);
	
	/************/
	/* COPY ... */
	/************/
	SetMatEntry(p,0,0,R1->RowVec[0]);
	SetMatEntry(p,0,1,R1->RowVec[1]);
	SetMatEntry(p,0,2,R1->RowVec[2]);
	SetMatEntry(p,0,3,R1->RowVec[3]);
	SetMatEntry(p,1,0,R2->RowVec[0]);
	SetMatEntry(p,1,1,R2->RowVec[1]);
	SetMatEntry(p,1,2,R2->RowVec[2]);
	SetMatEntry(p,1,3,R2->RowVec[3]);
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}

/*********/
/* CTORS */
/*********/
AST_Mat AST_Alloc_Mat3x2(AST_RowVec R1,AST_RowVec R2,AST_RowVec R3)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_Mat p = AllocateMatrix();

	/****************/
	/* CLEAR MEMORY */
	/****************/
	ClearMatrix(p);
	
	/**************/
	/* ROW & COLS */
	/**************/
	SetNumRows(p,3);
	SetNumCols(p,2);
	
	/************/
	/* COPY ... */
	/************/
	SetMatEntry(p,0,0,R1->RowVec[0]);
	SetMatEntry(p,0,1,R1->RowVec[1]);
	SetMatEntry(p,1,0,R2->RowVec[0]);
	SetMatEntry(p,1,1,R2->RowVec[1]);
	SetMatEntry(p,2,0,R3->RowVec[0]);
	SetMatEntry(p,2,1,R3->RowVec[1]);
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}
AST_Mat AST_Alloc_Mat3x3(AST_RowVec R1,AST_RowVec R2,AST_RowVec R3)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_Mat p = AllocateMatrix();

	/****************/
	/* CLEAR MEMORY */
	/****************/
	ClearMatrix(p);
	
	/**************/
	/* ROW & COLS */
	/**************/
	SetNumRows(p,3);
	SetNumCols(p,3);
	
	/************/
	/* COPY ... */
	/************/
	SetMatEntry(p,0,0,R1->RowVec[0]);
	SetMatEntry(p,0,1,R1->RowVec[1]);
	SetMatEntry(p,0,2,R1->RowVec[2]);
	SetMatEntry(p,1,0,R2->RowVec[0]);
	SetMatEntry(p,1,1,R2->RowVec[1]);
	SetMatEntry(p,1,2,R2->RowVec[2]);
	SetMatEntry(p,2,0,R3->RowVec[0]);
	SetMatEntry(p,2,1,R3->RowVec[1]);
	SetMatEntry(p,2,2,R3->RowVec[2]);
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}
AST_Mat AST_Alloc_Mat3x4(AST_RowVec R1,AST_RowVec R2,AST_RowVec R3)
{
	/**************/
	/* ALLOCATION */
	/**************/
	AST_Mat p = AllocateMatrix();

	/****************/
	/* CLEAR MEMORY */
	/****************/
	ClearMatrix(p);
	
	/**************/
	/* ROW & COLS */
	/**************/
	SetNumRows(p,3);
	SetNumCols(p,3);
	
	/************/
	/* COPY ... */
	/************/
	SetMatEntry(p,0,0,R1->RowVec[0]);
	SetMatEntry(p,0,1,R1->RowVec[1]);
	SetMatEntry(p,0,2,R1->RowVec[2]);
	SetMatEntry(p,0,3,R1->RowVec[3]);
	SetMatEntry(p,1,0,R2->RowVec[0]);
	SetMatEntry(p,1,1,R2->RowVec[1]);
	SetMatEntry(p,1,2,R2->RowVec[2]);
	SetMatEntry(p,1,3,R2->RowVec[3]);
	SetMatEntry(p,2,0,R3->RowVec[0]);
	SetMatEntry(p,2,1,R3->RowVec[1]);
	SetMatEntry(p,2,2,R3->RowVec[2]);
	SetMatEntry(p,2,3,R3->RowVec[3]);
	
	/**********/
	/* RETURN */
	/**********/
	return p;
}

/*********/
/* CTORS */
/*********/
AST_Number AST_Alloc_Number(int nominator,int denominator)
{
	AST_Number p = AllocateFraction();
	
	SetNominator(p,nominator);
	SetDenominator(p,denominator);
	
	return p;
}

