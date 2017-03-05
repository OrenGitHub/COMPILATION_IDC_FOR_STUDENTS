#ifndef __FRACTION_H__
#define __FRACTION_H__

/*********************************/
/* FILE NAME: FILE_02_Fraction.h */
/*********************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <assert.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/

/*********/
/* TYPES */
/*********/
typedef struct Fraction_ *Fraction;

/*************/
/* FUNCTIONS */
/*************/
void FractionToLowestTerms(Fraction f);
void SetNominator(Fraction f,int nominator);
void SetDenominator(Fraction f,int denominator);
Fraction New_Fraction(int nominator,int denominator);

#endif
