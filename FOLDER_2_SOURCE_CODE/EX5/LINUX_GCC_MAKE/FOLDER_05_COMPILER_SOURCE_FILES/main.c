/*********************/
/* FILE NAME: main.c */
/*********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_01_util.h"
#include "FILE_02_symbol.h"
#include "FILE_06_StarKist_AST.h"
#include "FILE_03_StarKist_ErrorMsg.h"
#include "FILE_08_semant.h"
#include "FILE_12_IR.h"
#include "FILE_13_IR_tree.h"
#include "FILE_15_Temporaries_and_Labels.h"
#include "asm.h"
#include "parse.h"
#include "FILE_20_PseudoAsm_To_Simulation.h"
#include "FILE_21_Liveness_Analysis.h"
#include "FILE_25_RegAlloc.h"
#include "Write_Assembley_Output_Filename.h"

/***************/
/* DEFINITIONS */
/***************/
#define PSEUDO_ASM_FILENAME         "../FOLDER_09_INTERMEDIATE_FILES/PseudoAsm.txt"
#define GRAPHVIZ_IR_FILENAME        "../FOLDER_09_INTERMEDIATE_FILES/IR_Graph.txt"
#define SIMULATION_C_FILENAME       "../FOLDER_09_INTERMEDIATE_FILES/simulation.c"
#define GRAPHVIZ_AST_FILENAME       "../FOLDER_09_INTERMEDIATE_FILES/AST_Graph.txt"
#define LIVENESS_ANALYSIS_FILENAME  "../FOLDER_09_INTERMEDIATE_FILES/Liveness_Analysis.txt"
#define INTERFERENCE_GRAPH_FILENAME "../FOLDER_09_INTERMEDIATE_FILES/Interference_Graph.txt"

/********************/
/* GLOBAL VARIABLES */
/********************/
static A_exp AST=NULL;
static T_exp IR_tree = NULL;
string Tiger_Program_Filename;
string Mips_Asm_Output_Filename;
int Temporaries_To_Registers_Map[MAX_NUM_TEMPORARIES];

/********/
/* main */
/********/
int main(int argc,char **argv)
{
	/***********************/
	/* [0] Initializations */
	/***********************/
	Tiger_Program_Filename=argv[1];
	Mips_Asm_Output_Filename=argv[2];

	/***************************************************/
	/* [1] Build Abstract Syntax Tree Of Tiger Program */
	/***************************************************/
	AST = Tiger_Program_To_AST(Tiger_Program_Filename);
	// ABSYN_PrintTree(AST,GRAPHVIZ_AST_FILENAME);

	/*************************/
	/* [2] Semantic Analysis */
	/*************************/
	Semantic_Analysis(AST);

	/***********************************/
	/* [3] Intermediate Representation */
	/***********************************/
	IR_tree = AST_To_IR(AST);
	IR_PrintTree(IR_tree,GRAPHVIZ_IR_FILENAME);

	/***********************/
	/* [4] Code Generation */
	/***********************/
	IR_To_Pseudo_Assembley(
		IR_tree,
		PSEUDO_ASM_FILENAME);

	/***********************************************/
	/* [5] Generate PC Simulation for unit testing */
	/***********************************************/
	Pseudo_Assembley_To_Simulation(
		PSEUDO_ASM_FILENAME,
		SIMULATION_C_FILENAME);

	/**********************************************/
	/* [6] Liveness Analysis & Interference Graph */
	/**********************************************/
	Liveness_Analysis(
		PSEUDO_ASM_FILENAME,
		LIVENESS_ANALYSIS_FILENAME,
		INTERFERENCE_GRAPH_FILENAME);

	/***************************/
	/* [7] Register Allocation */
	/***************************/
	Register_Allocation(
		INTERFERENCE_GRAPH_FILENAME,
		Temporaries_To_Registers_Map);

	/****************************/
	/* [8] Write Assembley File */
	/****************************/
	Write_Assembley_Output_File(
		PSEUDO_ASM_FILENAME,
		Temporaries_To_Registers_Map,
		Mips_Asm_Output_Filename);
}

