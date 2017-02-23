/********************************************/
/* FILE NAME: Write_Assembley_Output_File.c */
/********************************************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include <stdio.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_01_util.h"
#include "FILE_22_RegAlloc_ErrorMsg.h"
#include "FILE_24_RegAlloc_Parser.h"

/************************/
/* EXTERNAL DEFINITIONS */
/************************/
extern int gglex(void);
YYSTYPE gglval;

/*******************************/
/* Write_Assembley_Output_File */
/*******************************/
void Write_Assembley_Output_File(
	string pseudo_assembley_filename,
	int Temporaries_To_Registers_Map[],
	string Mips_Asm_Output_Filename)
{
	int tok;
	FILE *fl;
	
	/*********************************************/
	/* [1] open mips asm output file for writing */
	/*********************************************/
	fl=fopen(Mips_Asm_Output_Filename,"w+t");

	/***********************************/
	/* [2] open pseudo mips input file */
	/***********************************/
	TEMPS_TO_REGS_EM_reset(pseudo_assembley_filename);

	/*******************************************************************************************/
	/* [3] replace the temporaries in the pseudo mips asm file with their designated registers */
	/*******************************************************************************************/
	while (1)
	{
		/******************************/
		/* [a] get next chunk of text */
		/******************************/
		tok=gglex();

		/***********/
		/* [b] EOF */
		/***********/
		if (tok == 0) break;

		/*************************************/
		/* [c] and decide what to do with it */
		/*************************************/
		switch (tok) {
		case (SPACE):	fprintf(fl," ");	break;
		case (TAB):		fprintf(fl,"\t");	break;
		case (COMMA):	fprintf(fl,",");	break;
		case (LPAREN):	fprintf(fl,"(");	break;
		case (RPAREN):	fprintf(fl,")");	break;
		case (NEWLINE):	fprintf(fl,"\n");	break;
		case (TEMP):

			/**************************************************************/
			/* TEMPORARY: replace it with its designated register $t0-$t7 */
			/**************************************************************/
			fprintf(fl,"$t%d",Temporaries_To_Registers_Map[gglval.gval.temp_serial_number]);
			break;
			
		case (ANY_OTHER_THING):

			/**********************************************************************/
			/* ANY_OTHER_THING: just copy it as it is! also spaces, tabs, \n etc. */
			/**********************************************************************/
			fprintf(fl,"%s",gglval.gval.sval);
		}
	}

	/******************/
	/* [4] close file */
	/******************/
	fclose(fl);
}
