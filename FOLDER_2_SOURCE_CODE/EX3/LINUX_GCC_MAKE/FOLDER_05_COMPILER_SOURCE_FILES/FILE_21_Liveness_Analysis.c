/**********/
/* main.c */
/**********/

/****************************************/
/* WARNING DISABLE: sprintf - I love it */
/****************************************/
#pragma warning (disable: 4996)

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "util.h"
#include "PSEUDO_MIPS_ASM_AST.h"
#include "errormsg.h"
#include "parse.h"
#include "temp.h"

/***************/
/* DEFINITIONS */
/***************/
#define MAX_NUM_ASM_COMMANDS 4000

/********************/
/* GLOBAL VARIABLES */
/********************/
int low[MAX_NUM_TEMPORARIES];
int high[MAX_NUM_TEMPORARIES];

/********************/
/* GLOBAL VARIABLES */
/********************/
int in[MAX_NUM_ASM_COMMANDS];
int out[MAX_NUM_ASM_COMMANDS];
int def[MAX_NUM_ASM_COMMANDS];
int use[MAX_NUM_ASM_COMMANDS][2];
int in_tag[MAX_NUM_ASM_COMMANDS];
int out_tag[MAX_NUM_ASM_COMMANDS];

/********************/
/* GLOBAL VARIABLES */
/********************/
static PSEUDO_MIPS_ASM_AST_expList AST=NULL;

/********************/
/* GLOBAL VARIABLES */
/********************/
FILE *pseudo_assembley_fl;
FILE *liveness_analysis_fl;
FILE *interference_graph_fl;

/********************/
/* GLOBAL VARIABLES */
/********************/
int numCommands=0;

/********************/
/* GLOBAL VARIABLES */
/********************/
int out_edges[MAX_NUM_ASM_COMMANDS][2];

/********************/
/* GLOBAL VARIABLES */
/********************/
int MapSerialNumberOfLabel_To_ItsCommandNumber[MAX_NUM_ASM_COMMANDS];

void Build_Use_and_Def_from_Exp_Add(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.add.var1->type == TEMPORARY_VAR){def[command]    = exp->u.add.var1->u.temp;}
	if (exp->u.add.var2->type == TEMPORARY_VAR){use[command][0] = exp->u.add.var2->u.temp;}
	if (exp->u.add.var3->type == TEMPORARY_VAR){use[command][1] = exp->u.add.var3->u.temp;}
}
void Build_Use_and_Def_from_Exp_Sub(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.sub.var1->type == TEMPORARY_VAR){def[command]    = exp->u.sub.var1->u.temp;}
	if (exp->u.sub.var2->type == TEMPORARY_VAR){use[command][0] = exp->u.sub.var2->u.temp;}
	if (exp->u.sub.var3->type == TEMPORARY_VAR){use[command][1] = exp->u.sub.var3->u.temp;}
}
void Build_Use_and_Def_from_Exp_Mul(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.mul.var1->type == TEMPORARY_VAR){def[command]    = exp->u.mul.var1->u.temp;}
	if (exp->u.mul.var2->type == TEMPORARY_VAR){use[command][0] = exp->u.mul.var2->u.temp;}
	if (exp->u.mul.var3->type == TEMPORARY_VAR){use[command][1] = exp->u.mul.var3->u.temp;}
}
void Build_Use_and_Def_from_Exp_Div(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.div.var1->type == TEMPORARY_VAR){def[command]    = exp->u.div.var1->u.temp;}
	if (exp->u.div.var2->type == TEMPORARY_VAR){use[command][0] = exp->u.div.var2->u.temp;}
	if (exp->u.div.var3->type == TEMPORARY_VAR){use[command][1] = exp->u.div.var3->u.temp;}
}
void Build_Use_and_Def_from_Exp_Beq(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.beq.var1->type == TEMPORARY_VAR){use[command][0] = exp->u.beq.var1->u.temp;}
	if (exp->u.beq.var2->type == TEMPORARY_VAR){use[command][1] = exp->u.beq.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Bne(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.bne.var1->type == TEMPORARY_VAR){use[command][0] = exp->u.bne.var1->u.temp;}
	if (exp->u.bne.var2->type == TEMPORARY_VAR){use[command][1] = exp->u.bne.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Bgt(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.bgt.var1->type == TEMPORARY_VAR){use[command][0] = exp->u.bgt.var1->u.temp;}
	if (exp->u.bgt.var2->type == TEMPORARY_VAR){use[command][1] = exp->u.bgt.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Blt(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.blt.var1->type == TEMPORARY_VAR){use[command][0] = exp->u.blt.var1->u.temp;}
	if (exp->u.blt.var2->type == TEMPORARY_VAR){use[command][1] = exp->u.blt.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Bge(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.bge.var1->type == TEMPORARY_VAR){use[command][0] = exp->u.bge.var1->u.temp;}
	if (exp->u.bge.var2->type == TEMPORARY_VAR){use[command][1] = exp->u.bge.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Ble(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.ble.var1->type == TEMPORARY_VAR){use[command][0] = exp->u.ble.var1->u.temp;}
	if (exp->u.ble.var2->type == TEMPORARY_VAR){use[command][1] = exp->u.ble.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Load(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.load.var1->type == TEMPORARY_VAR){def[command]    = exp->u.load.var1->u.temp;}
	if (exp->u.load.var2->type == TEMPORARY_VAR){use[command][0] = exp->u.load.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Store(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.store.var1->type == TEMPORARY_VAR){use[command][0] = exp->u.store.var1->u.temp;}
	if (exp->u.store.var2->type == TEMPORARY_VAR){use[command][1] = exp->u.store.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Move(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.move.var1->type == TEMPORARY_VAR){def[command]    = exp->u.move.var1->u.temp;}
	if (exp->u.move.var2->type == TEMPORARY_VAR){use[command][0] = exp->u.move.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Add_Immediate(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.add_immediate.var1->type == TEMPORARY_VAR){def[command]    = exp->u.add_immediate.var1->u.temp;}
	if (exp->u.add_immediate.var2->type == TEMPORARY_VAR){use[command][0] = exp->u.add_immediate.var2->u.temp;}
}
void Build_Use_and_Def_from_Exp_Load_Immediate(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	if (exp->u.load_immediate.var->type == TEMPORARY_VAR){def[command] = exp->u.load_immediate.var->u.temp;}
}

/*******************/
/* EMPTY Use & Def */
/*******************/
void Build_Use_and_Def_from_Exp_Label(        PSEUDO_MIPS_ASM_AST_exp exp,int command){}
void Build_Use_and_Def_from_Exp_Jump_Label(   PSEUDO_MIPS_ASM_AST_exp exp,int command){}
void Build_Use_and_Def_from_Exp_Jump_And_link(PSEUDO_MIPS_ASM_AST_exp exp,int command){}
void Build_Use_and_Def_from_Exp_Jump_Register(PSEUDO_MIPS_ASM_AST_exp exp,int command){}

/******************************/
/* Build_Use_and_Def_from_Exp */
/******************************/
void Build_Use_and_Def_from_Exp(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	switch (exp->type) {
	case (PSEUDO_MIPS_ASM_AST_ADD_EXP_TYPE):			Build_Use_and_Def_from_Exp_Add(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_SUB_EXP_TYPE):			Build_Use_and_Def_from_Exp_Sub(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_MUL_EXP_TYPE):			Build_Use_and_Def_from_Exp_Mul(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_DIV_EXP_TYPE):			Build_Use_and_Def_from_Exp_Div(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_BEQ_EXP_TYPE):			Build_Use_and_Def_from_Exp_Beq(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_BNE_EXP_TYPE):			Build_Use_and_Def_from_Exp_Bne(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_BGT_EXP_TYPE):			Build_Use_and_Def_from_Exp_Bgt(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_BGE_EXP_TYPE):			Build_Use_and_Def_from_Exp_Blt(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_BLT_EXP_TYPE):			Build_Use_and_Def_from_Exp_Bge(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_BLE_EXP_TYPE):			Build_Use_and_Def_from_Exp_Ble(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_LOAD_EXP_TYPE):			Build_Use_and_Def_from_Exp_Load(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_MOVE_EXP_TYPE):			Build_Use_and_Def_from_Exp_Move(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_LABEL_EXP_TYPE):			Build_Use_and_Def_from_Exp_Label(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_STORE_EXP_TYPE):			Build_Use_and_Def_from_Exp_Store(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_LABEL_EXP_TYPE):		Build_Use_and_Def_from_Exp_Jump_Label(exp,command);		break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_AND_LINK_EXP_TYPE):	Build_Use_and_Def_from_Exp_Jump_And_link(exp,command);	break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_REGISTER_EXP_TYPE):	Build_Use_and_Def_from_Exp_Jump_Register(exp,command);	break;
	case (PSEUDO_MIPS_ASM_AST_ADD_IMMEDIATE_EXP_TYPE):	Build_Use_and_Def_from_Exp_Add_Immediate(exp,command);	break;
	case (PSEUDO_MIPS_ASM_AST_LOAD_IMMEDIATE_EXP_TYPE):	Build_Use_and_Def_from_Exp_Load_Immediate(exp,command);	break;
	}
}

/***********/
/* Default */
/***********/
void Build_Control_Flow_Graph_Default(int command)
{
	out_edges[command][0]=command+1;
	out_edges[command][1]=-1;
}

/**********/
/* Binops */
/**********/
void Build_Control_Flow_Graph_Add(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}
void Build_Control_Flow_Graph_Sub(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}
void Build_Control_Flow_Graph_Mul(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}
void Build_Control_Flow_Graph_Div(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}

/***********************/
/* Load / Move / Store */
/***********************/
void Build_Control_Flow_Graph_Load( PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}
void Build_Control_Flow_Graph_Move( PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}
void Build_Control_Flow_Graph_Store(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}

/**********************************/
/* Add Immediate / Load Immediate */
/**********************************/
void Build_Control_Flow_Graph_Add_Immediate( PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}
void Build_Control_Flow_Graph_Load_Immediate(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}

/*********/
/* Label */
/*********/
void Build_Control_Flow_Graph_Label(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Default(command);}

/************/
/* Branches */
/************/
void Build_Control_Flow_Graph_Branch(int command, int label_serial_number)
{
	out_edges[command][0]=command+1;
	out_edges[command][1]=MapSerialNumberOfLabel_To_ItsCommandNumber[label_serial_number];
}

/************/
/* Branches */
/************/
void Build_Control_Flow_Graph_Beq(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Branch(command,exp->u.beq.label.serial_number);}
void Build_Control_Flow_Graph_Bne(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Branch(command,exp->u.bne.label.serial_number);}
void Build_Control_Flow_Graph_Bgt(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Branch(command,exp->u.bgt.label.serial_number);}
void Build_Control_Flow_Graph_Blt(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Branch(command,exp->u.blt.label.serial_number);}
void Build_Control_Flow_Graph_Bge(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Branch(command,exp->u.bge.label.serial_number);}
void Build_Control_Flow_Graph_Ble(PSEUDO_MIPS_ASM_AST_exp exp,int command){Build_Control_Flow_Graph_Branch(command,exp->u.ble.label.serial_number);}

/********/
/* Jump */
/********/
void Build_Control_Flow_Graph_Jump_Label(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	out_edges[command][0]=MapSerialNumberOfLabel_To_ItsCommandNumber[exp->u.jump_label.serial_number];
	out_edges[command][1]=-1;
}

void Build_Control_Flow_Graph_Jump_And_link(PSEUDO_MIPS_ASM_AST_exp exp,int command){}
void Build_Control_Flow_Graph_Jump_Register(PSEUDO_MIPS_ASM_AST_exp exp,int command){}

void Build_Control_Flow_Graph_From_Exp(PSEUDO_MIPS_ASM_AST_exp exp,int command)
{
	switch (exp->type) {
	case (PSEUDO_MIPS_ASM_AST_ADD_EXP_TYPE):			Build_Control_Flow_Graph_Add(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_SUB_EXP_TYPE):			Build_Control_Flow_Graph_Sub(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_MUL_EXP_TYPE):			Build_Control_Flow_Graph_Mul(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_DIV_EXP_TYPE):			Build_Control_Flow_Graph_Div(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_BEQ_EXP_TYPE):			Build_Control_Flow_Graph_Beq(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_BNE_EXP_TYPE):			Build_Control_Flow_Graph_Bne(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_BGT_EXP_TYPE):			Build_Control_Flow_Graph_Bgt(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_BGE_EXP_TYPE):			Build_Control_Flow_Graph_Blt(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_BLT_EXP_TYPE):			Build_Control_Flow_Graph_Bge(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_BLE_EXP_TYPE):			Build_Control_Flow_Graph_Ble(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_LOAD_EXP_TYPE):			Build_Control_Flow_Graph_Load(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_MOVE_EXP_TYPE):			Build_Control_Flow_Graph_Move(exp,command);				break;
	case (PSEUDO_MIPS_ASM_AST_LABEL_EXP_TYPE):			Build_Control_Flow_Graph_Label(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_STORE_EXP_TYPE):			Build_Control_Flow_Graph_Store(exp,command);			break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_LABEL_EXP_TYPE):		Build_Control_Flow_Graph_Jump_Label(exp,command);		break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_AND_LINK_EXP_TYPE):	Build_Control_Flow_Graph_Jump_And_link(exp,command);	break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_REGISTER_EXP_TYPE):	Build_Control_Flow_Graph_Jump_Register(exp,command);	break;
	case (PSEUDO_MIPS_ASM_AST_ADD_IMMEDIATE_EXP_TYPE):	Build_Control_Flow_Graph_Add_Immediate(exp,command);	break;
	case (PSEUDO_MIPS_ASM_AST_LOAD_IMMEDIATE_EXP_TYPE):	Build_Control_Flow_Graph_Load_Immediate(exp,command);	break;
	}
}

int EQUAL(int a[MAX_NUM_ASM_COMMANDS],int b[MAX_NUM_ASM_COMMANDS])
{
	int i=0;
	int ret=1;

	for (i=0;i<MAX_NUM_ASM_COMMANDS;i++)
	{
		if (a[i] != b[i]) ret = 0;
	}

	return ret;
}

void Map_Serial_Number_Of_Labels_To_Their_Command(void)
{
	int command=0;
	PSEUDO_MIPS_ASM_AST_expList expList;

	for (expList=AST;expList;expList=expList->tail,command++)
	{
		if (expList->head->type == PSEUDO_MIPS_ASM_AST_LABEL_EXP_TYPE)
		{
			MapSerialNumberOfLabel_To_ItsCommandNumber[expList->head->u.label.serial_number] = command;
		}
	}
}

void Update_Total_Number_Of_Commands(void)
{
	PSEUDO_MIPS_ASM_AST_expList expList;

	for (expList=AST;expList;expList=expList->tail)
	{
		numCommands++;
	}
}

void Build_Use_And_Def(void)
{
	int command=0;
	PSEUDO_MIPS_ASM_AST_expList expList;

	for (expList=AST,command=0;expList;expList=expList->tail,command++)
	{
		Build_Use_and_Def_from_Exp(expList->head,command);
	}
}

void Build_Control_Flow_Graph(int out_edges[MAX_NUM_ASM_COMMANDS][2])
{
	int command=0;
	PSEUDO_MIPS_ASM_AST_expList expList;

	for (expList=AST,command=0;expList;expList=expList->tail,command++)
	{
		Build_Control_Flow_Graph_From_Exp(expList->head,command);
	}
}

/*************************************/
/* Write Liveness Range Of Temporary */
/*************************************/
void WriteLivenessRangeOfTemporary(int temp)
{
	int n=0;
	int firstTime=0;

	fprintf(liveness_analysis_fl,"Temp_%d = [ ",temp);

	firstTime=1;
	low[temp]=-1;
	high[temp]=-1;

	for (n=0;n<numCommands;n++)
	{
		if ((in[n] == 1) || (out[n] == 1))
		{
			if (firstTime)
			{
				firstTime=0;
				low[temp]=n;
			}
			high[temp]=n;
			fprintf(liveness_analysis_fl,"%d ",n);
		}
	}

	fprintf(liveness_analysis_fl,"]\n");
}

/****************************/
/* Build_Interference_Graph */
/****************************/
void Build_Interference_Graph(int numTemporaries)
{
	int i=0;
	int j=0;
	
	fprintf(interference_graph_fl,"graph\n{\n");

	for (i=0;i<numTemporaries;i++)
	{
		for (j=i+1;j<numTemporaries;j++)
		{
			if ((low[i] >= 0) && (low[j] >= 0))
			{
				if ((low[i] <= high[j]) && (low[j] <= high[i]))
				{
					fprintf(interference_graph_fl,"%d -- %d;\n",i,j);
				}
			}
		}
	}

	fprintf(interference_graph_fl,"}\n");
}

/********/
/* main */
/********/
void Liveness_Analysis(
	string Pseudo_Assembley_Filename,
	string Liveness_Analysis_Filename,
	string Interference_Graph_Filename)
{
	int n=0;
	int temp=0;
	int numTemporaries=TEMP_numTemporariesAllocated();

	/******************/
	/* [0] Open Files */
	/******************/
	pseudo_assembley_fl=fopen(Pseudo_Assembley_Filename,"rt");
	liveness_analysis_fl=fopen(Liveness_Analysis_Filename,"w+t");
	interference_graph_fl=fopen(Interference_Graph_Filename,"w+t");

	/***********************/
	/* [1] Initializations */
	/***********************/
	memset(in,-1,sizeof(in));
	memset(use,-1,sizeof(use));
	memset(def,-1,sizeof(def));
	memset(out,-1,sizeof(out));
	memset(in_tag,-1,sizeof(in_tag));
	memset(out_tag,-1,sizeof(out_tag));
	memset(out_edges,-1,sizeof(out_edges));

	/**********************************/
	/* [2] Build Abstract Syntax Tree */
	/**********************************/
	AST = Pseudo_Assembley_To_AST(Pseudo_Assembley_Filename);

	/*************************/
	/* [3] Build use and def */
	/*************************/
	Build_Use_And_Def();

	/************************************/
	/* [4] Count the number of commands */
	/************************************/
	Update_Total_Number_Of_Commands();

	/*************************************/
	/* [5] map labels to command numbers */
	/*************************************/
	Map_Serial_Number_Of_Labels_To_Their_Command();

	/************************/
	/* [6] Build flow graph */
	/************************/
	Build_Control_Flow_Graph(out_edges);

	/**************************************************/
	/* [7] Liveness analysis - one variable at a time */
	/**************************************************/
	/*******************************************************************/
	/* NOTE: since we do it one variable at a time:                    */
	/*                                                                 */
	/*       [a] each in[n] is either 1 or 0, to indicate              */
	/*       if the current temporary is live-in at command n, or not  */
	/*                                                                 */
	/*       [b] each out[n] is either 1 or 0, to indicate             */
	/*       if the current temporary is live-out at command n, or not */
	/*                                                                 */
	/*******************************************************************/
	for (temp=0;temp<numTemporaries;temp++)
	{
		/***************/
		/* for each n: */
		/***************/
		for (n=0;n<numCommands;n++)
		{
			/***********************/
			/* in[n]  := EMPTY-SET */
			/* out[n] := EMPTY-SET */
			/***********************/
			in[n]=-1;
			out[n]=-1;
		}

		do
		{
			/***************/
			/* for each n: */
			/***************/
			for (n=0;n<numCommands;n++)
			{
				/*********************/
				/* in'[n]  := in[n]  */
				/* out'[n] := out[n] */
				/*********************/
				in_tag[ n] = in[ n];
				out_tag[n] = out[n];

				/********************************************/
				/* in[n]  := use[n] UNION (out[n] \ def[n]) */
				/********************************************/
				if ((use[n][0] == temp) || (use[n][1] == temp) || ((out[n] == 1) && (def[n] != temp)))
				{
					in[n]=1;
				}

				/********************************************************/
				/* out[n]  := UNION( in[s] ) over all successors s of n */
				/********************************************************/
				/******************************************************************************/
				/* NOTE: in MIPS, or any other reasonable architecture, there are             */
				/*       maximum 2 successors for each command (in the case of branch / jump) */
				/*       and only 1 successor of the rest of the commands..                   */
				/******************************************************************************/
				if ((in[out_edges[n][0]] == 1) || (in[out_edges[n][1]] == 1))
				{
					out[n]=1;
				}

			}
		}
		while ((!EQUAL(in,in_tag)) || (!EQUAL(out,out_tag)));

		/**************************************************/
		/* [8] Write Liveness Ranges Of Current Temporary */
		/**************************************************/
		WriteLivenessRangeOfTemporary(temp);
	}

	/************************************/
	/* [9] Construct Interference Graph */
	/************************************/
	Build_Interference_Graph(numTemporaries);

	/*******************/
	/* [9] Close Files */
	/*******************/
	fclose(pseudo_assembley_fl);
	fclose(liveness_analysis_fl);
	fclose(interference_graph_fl);
}
