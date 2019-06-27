#ifndef __WRITE_ASSEMBLEY_OUTPUT_FILENAME_H__
#define __WRITE_ASSEMBLEY_OUTPUT_FILENAME_H__

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_01_util.h"

void Write_Assembley_Output_File(
	string pseudo_assembley_filename,
	int Temporaries_To_Registers_Map[],
	string Mips_Asm_Output_Filename);

#endif
