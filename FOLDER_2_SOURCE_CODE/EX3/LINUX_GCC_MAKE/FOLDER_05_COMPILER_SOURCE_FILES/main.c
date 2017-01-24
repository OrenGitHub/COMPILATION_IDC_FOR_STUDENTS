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
#include "asm.h"
#include "IR.h"
#include "util.h"
#include "tree.h"
#include "symbol.h"
#include "semant.h"
#include "absyn.h"
#include "errormsg.h"
#include "parse.h"
#include "Liveness_Analysis.h"
#include "Register_Allocation.h"
#include "Pseudo_Assembley_To_Simulation.h"
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
	ABSYN_PrintTree(AST,GRAPHVIZ_AST_FILENAME);

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

