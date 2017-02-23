#ifndef __REGISTER_ALLOCATION_H__
#define __REGISTER_ALLOCATION_H__

/************************************/
/* FILE NAME: Register_Allocation.h */
/************************************/

/*****************/
/* INCLUDE FILES */
/*****************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_15_Temporaries_and_Labels.h"

void Register_Allocation(char *interference_graph_filename, int Temporaries_To_Registers_Map[MAX_NUM_TEMPORARIES]);

#endif
