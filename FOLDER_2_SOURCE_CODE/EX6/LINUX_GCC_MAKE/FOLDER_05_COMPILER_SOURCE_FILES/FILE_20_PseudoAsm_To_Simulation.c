/************************************/
/* Pseudo_Assembley_To_Simulation.c */
/************************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_01_util.h"
#include "FILE_03_StarKist_ErrorMsg.h"
#include "FILE_06_StarKist_AST.h"
#include "FILE_15_Temporaries_and_Labels.h"
#include "parse.h"
#include "frame.h"

#define MAX_NAME_LENGTH_OF_TEMPORARY_OR_REGISTER 16
/********************/
/* GLOBAL VARIABLES */
/********************/
PSEUDO_MIPS_ASM_AST_expList AST=NULL;

/********************/
/* GLOBAL VARIABLES */
/********************/
FILE *fl;

/********************/
/* GLOBAL VARIABLES */
/********************/
int indexGlobal=0;

string Temporary_Or_Register(PSEUDO_MIPS_ASM_AST_Var var)
{
	string temp_or_register = (string) malloc(MAX_NAME_LENGTH_OF_TEMPORARY_OR_REGISTER);
	char temp_buffer[MAX_NAME_LENGTH_OF_TEMPORARY_OR_REGISTER];

	if (var->type == TEMPORARY_VAR)
	{
		sprintf(temp_or_register,"Temp_%d",var->u.temp);
	}
	if (var->type == REGISTER_VAR)
	{
		strcpy(temp_or_register,var->u.reg);
	}

	return temp_or_register;
}

void CodeGenerationExp_VfTable(PSEUDO_MIPS_ASM_AST_exp exp)
{
	int offset=0;
	PSEUDO_MIPS_ASM_AST_LabelList list = NULL;

	fprintf(fl,"\tint %s[] = {",exp->u.vftable.name);
	for (list = exp->u.vftable.list;list;list = list->tail)
	{
		fprintf(fl,"0,");
	}
	fprintf(fl,"};\n");

	fprintf(fl,"\t__asm\n\t{\n");
	
	for (list = exp->u.vftable.list;list;list = list->tail,offset+=4)
	{
		fprintf(fl,"\t\tmov eax, %s\n",list->head);
		fprintf(fl,"\t\tmov %s+%d, eax\n",exp->u.vftable.name,offset);
	}
			
	fprintf(fl,"\t}\n\n");
}

void CodeGenerationExp_StartOfCode(CodeGenerationExp_StartOfCode)
{
	/**************************************************/
	/* [1] Declare dummy variables for easy debugging */
	/**************************************************/
	fprintf(fl,"\tint b1=1;\n");
	fprintf(fl,"\tint b2=2;\n");
	fprintf(fl,"\tint b3=3;\n");
	fprintf(fl,"\tint b4=4;\n");
	fprintf(fl,"\tint b5=5;\n");
	fprintf(fl,"\tint b6=6;\n");

	/**************************/
	/* [2] Initialize sp & fp */
	/**************************/
	fprintf(fl,"\tint *AlonzoMorales = (sp = &b3);\n");
	fprintf(fl,"\tint *KamrashAlura  = (fp = &b2);\n\n");	
}
void CodeGenerationExp_StringVar(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(
		fl,
		"\tconst char *%s = %s;\n\n",
		exp->u.string_var.var,
		exp->u.string_var.value);
}
void CodeGenerationExp_Load_Byte(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.load_byte.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.load_byte.var2);

	fprintf(
		fl,
		"\t%s = (int *) (*((char *) %s));\n\n",
		temporary_or_register_1,
		temporary_or_register_2);	
}
void CodeGenerationExp_Store_Byte(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.store_byte.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.store_byte.var2);

	fprintf(
		fl,
		"\t*(((char *) %s)+0) = ((char) %s);\n\n",
		temporary_or_register_2,
		temporary_or_register_1);	
}
void CodeGenerationExp_Load_Address(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.load_address.var1);

	fprintf(
		fl,
		"\t%s = (int *) %s;\n\n",
		temporary_or_register_1,
		exp->u.load_address.var2);	
}
void CodeGenerationExp_Add(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.add.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.add.var2);
	string temporary_or_register_3 = Temporary_Or_Register(exp->u.add.var3);

	fprintf(
		fl,
		"\t%s =(int *) (((int) %s) + ((int) %s));\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		temporary_or_register_3);
}
void CodeGenerationExp_Sub(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.sub.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.sub.var2);
	string temporary_or_register_3 = Temporary_Or_Register(exp->u.sub.var3);

	fprintf(
		fl,
		"\t%s =(int *) (((int) %s) - ((int) %s));\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		temporary_or_register_3);
}
void CodeGenerationExp_Mul(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.mul.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.mul.var2);
	string temporary_or_register_3 = Temporary_Or_Register(exp->u.mul.var3);

	fprintf(
		fl,
		"\t%s =(int *) (((int) %s) * ((int) %s));\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		temporary_or_register_3);
}
void CodeGenerationExp_Div(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.div.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.div.var2);
	string temporary_or_register_3 = Temporary_Or_Register(exp->u.div.var3);

	fprintf(
		fl,
		"\t%s =(int *) (((int) %s) / ((int) %s));\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		temporary_or_register_3);
}
void CodeGenerationExp_Beq(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.beq.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.beq.var2);

	fprintf(
		fl,
		"\tif (((int) (%s)) == ((int) (%s)))\n\t{\n\t\tgoto %s;\n\t}\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		exp->u.beq.label.name);
}
void CodeGenerationExp_Bne(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.bne.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.bne.var2);

	fprintf(
		fl,
		"\tif (((int) (%s)) != ((int) (%s)))\n\t{\n\t\tgoto %s;\n\t}\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		exp->u.bne.label.name);
}
void CodeGenerationExp_Bgt(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.bgt.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.bgt.var2);

	fprintf(
		fl,
		"\tif (((int) (%s)) > ((int) (%s)))\n\t{\n\t\tgoto %s;\n\t}\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		exp->u.bgt.label.name);
}
void CodeGenerationExp_Blt(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.blt.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.blt.var2);

	fprintf(
		fl,
		"\tif (((int) (%s)) < ((int) (%s)))\n\t{\n\t\tgoto %s;\n\t}\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		exp->u.blt.label.name);
}
void CodeGenerationExp_Bge(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.bge.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.bge.var2);

	fprintf(
		fl,
		"\tif (((int) (%s)) >= ((int) (%s)))\n\t{\n\t\tgoto %s;\n\t}\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		exp->u.bge.label.name);
}
void CodeGenerationExp_Ble(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.ble.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.ble.var2);

	fprintf(
		fl,
		"\tif (((int) (%s)) <= ((int) (%s)))\n\t{\n\t\tgoto %s;\n\t}\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		exp->u.ble.label.name);
}
void CodeGenerationExp_Load(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.load.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.load.var2);

	fprintf(
		fl,
		"\t%s = (int *) *(%s + %d);\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		exp->u.load.offset / F_wordSize);
}
void CodeGenerationExp_Move(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.move.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.move.var2);

	fprintf(
		fl,
		"\t%s = %s;\n\n",
		temporary_or_register_1,
		temporary_or_register_2);
}
void CodeGenerationExp_Label(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(
		fl,
		"%s:\n\n",
		exp->u.label.name);
}
void CodeGenerationExp_Store(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.move.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.move.var2);

	fprintf(
		fl,
		"\t*(%s) = (int) (%s+(%d));\n\n",
		temporary_or_register_2,
		temporary_or_register_1,
		exp->u.store.offset / F_wordSize);
}

void CodeGenerationExp_Jump_Label(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(
		fl,
		"\tgoto %s;\n\n",
		exp->u.jump_label.name);
}

void CodeGenerationExp_Jump_And_link_Reg(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(
		fl,
		"\t__asm\n\t{\n\t\tcall _here%d\n\t\t_here%d: pop eax\n\t\tadd eax,15\n\t\tmov ra,eax\n\t}\n\n",
		indexGlobal,
		indexGlobal);

	fprintf(
		fl,
		"\t__asm\n\t{\n\t\tjmp %s\n\t}\n\n",
		exp->u.jump_and_link_reg);

	indexGlobal++;
}
void CodeGenerationExp_Jump_And_link(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(
		fl,
		"\t__asm\n\t{\n\t\tcall _here%d\n\t\t_here%d: pop eax\n\t\tadd eax,14\n\t\tmov ra,eax\n\t}\n\n",
		indexGlobal,
		indexGlobal);

	fprintf(
		fl,
		"\tgoto %s;\n\n",
		exp->u.jump_and_link);

	fprintf(
		fl,
		"\t__asm\n\t{\n\t\tnop\n\t\tnop\n\t\tnop\n\t}\n\n");

	indexGlobal++;
}
void CodeGenerationExp_Jump_Register(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(
		fl,
		"\t__asm\n\t{\n\t\tjmp %s\n\t}\n\n",
		exp->u.jump_register);
}

void CodeGenerationExp_Add_Immediate(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register_1 = Temporary_Or_Register(exp->u.load.var1);
	string temporary_or_register_2 = Temporary_Or_Register(exp->u.load.var2);

	fprintf(
		fl,
		"\t%s = (int *) ((int) %s + %d);\n\n",
		temporary_or_register_1,
		temporary_or_register_2,
		exp->u.add_immediate.value);
}
void CodeGenerationExp_Load_Immediate(PSEUDO_MIPS_ASM_AST_exp exp)
{
	string temporary_or_register = Temporary_Or_Register(exp->u.load_immediate.var);

	fprintf(
		fl,
		"\t%s = (int *) %d;\n\n",
		temporary_or_register,
		exp->u.load_immediate.value);
}

void CodeGenerationExp_Print_Int(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(fl,"\t%s\n\n","printf(\"\%d \",(int) a0);");
}
void CodeGenerationExp_Print_Char(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(fl,"\t%s\n\n","printf(\"\%c \",(char) a0);");
}
void CodeGenerationExp_Allocate(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(fl,"\t%s\n\n","v0 = (int *) malloc((int) a0);");
}
void CodeGenerationExp_Exit(PSEUDO_MIPS_ASM_AST_exp exp)
{
	fprintf(fl,"\t%s\n\n","exit(0);");
}

void CodeGenerationExp(PSEUDO_MIPS_ASM_AST_exp exp)
{
	switch (exp->type) {
	case (PSEUDO_MIPS_ASM_AST_ADD_EXP_TYPE):			CodeGenerationExp_Add(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_SUB_EXP_TYPE):			CodeGenerationExp_Sub(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_MUL_EXP_TYPE):			CodeGenerationExp_Mul(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_DIV_EXP_TYPE):			CodeGenerationExp_Div(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_BEQ_EXP_TYPE):			CodeGenerationExp_Beq(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_BNE_EXP_TYPE):			CodeGenerationExp_Bne(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_BGT_EXP_TYPE):			CodeGenerationExp_Bgt(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_BGE_EXP_TYPE):			CodeGenerationExp_Bge(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_BLT_EXP_TYPE):			CodeGenerationExp_Blt(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_BLE_EXP_TYPE):			CodeGenerationExp_Ble(exp);            break;
	case (PSEUDO_MIPS_ASM_AST_LOAD_EXP_TYPE):			CodeGenerationExp_Load(exp);           break;
	case (PSEUDO_MIPS_ASM_AST_MOVE_EXP_TYPE):			CodeGenerationExp_Move(exp);           break;
	case (PSEUDO_MIPS_ASM_AST_LABEL_EXP_TYPE):			CodeGenerationExp_Label(exp);          break;
	case (PSEUDO_MIPS_ASM_AST_STORE_EXP_TYPE):			CodeGenerationExp_Store(exp);          break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_LABEL_EXP_TYPE):		CodeGenerationExp_Jump_Label(exp);     break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_AND_LINK_EXP_TYPE):	CodeGenerationExp_Jump_And_link(exp);  break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_AND_LINK_REG_EXP_TYPE):	CodeGenerationExp_Jump_And_link_Reg(exp);  break;
	case (PSEUDO_MIPS_ASM_AST_JUMP_REGISTER_EXP_TYPE):	CodeGenerationExp_Jump_Register(exp);  break;
	case (PSEUDO_MIPS_ASM_AST_ADD_IMMEDIATE_EXP_TYPE):	CodeGenerationExp_Add_Immediate(exp);  break;
	case (PSEUDO_MIPS_ASM_AST_LOAD_IMMEDIATE_EXP_TYPE):	CodeGenerationExp_Load_Immediate(exp); break;
	case (PSEUDO_MIPS_ASM_AST_LOAD_BYTE_EXP_TYPE):		CodeGenerationExp_Load_Byte(exp);      break;
	case (PSEUDO_MIPS_ASM_AST_STORE_BYTE_EXP_TYPE):		CodeGenerationExp_Store_Byte(exp);     break;
	case (PSEUDO_MIPS_ASM_AST_PRINT_INT_EXP_TYPE):		CodeGenerationExp_Print_Int(exp);      break;
	case (PSEUDO_MIPS_ASM_AST_PRINT_CHAR_EXP_TYPE):		CodeGenerationExp_Print_Char(exp);     break;
	case (PSEUDO_MIPS_ASM_AST_ALLOCATE_EXP_TYPE):		CodeGenerationExp_Allocate(exp);       break;
	case (PSEUDO_MIPS_ASM_AST_EXIT_EXP_TYPE):			CodeGenerationExp_Exit(exp);           break;
	case (PSEUDO_MIPS_ASM_AST_STRING_VAR_EXP_TYPE):		CodeGenerationExp_StringVar(exp);      break;
	case (PSEUDO_MIPS_ASM_AST_VFTABLE_EXP_TYPE):		CodeGenerationExp_VfTable(exp);        break;
	case (PSEUDO_MIPS_ASM_AST_LOAD_ADDRESS_EXP_TYPE):	CodeGenerationExp_Load_Address(exp);   break;
	case (PSEUDO_MIPS_ASM_AST_START_OF_CODE_EXP_TYPE):	CodeGenerationExp_StartOfCode(exp);    break;
	}
}

void AST_To_Simulation(PSEUDO_MIPS_ASM_AST_expList AST,string simulation_filename)
{
	int i;

	PSEUDO_MIPS_ASM_AST_expList expList;

	/*************************************/
	/* [1] Open simulation.c for writing */
	/*************************************/
	fl=fopen(simulation_filename,"w+t");
	if (fl == NULL) return;

	/***********************/
	/* [2] Include headers */
	/***********************/
	fprintf(fl,"#include <stdio.h>\n\n");
	fprintf(fl,"#include <stdlib.h>\n\n");
	fprintf(fl,"#include <memory.h>\n\n");

	/**************************************/
	/* [3] Declare temporaries as (int *) */
	/**************************************/
	for (i=0;i<TEMP_numTemporariesAllocated();i++)
	{
		fprintf(fl,"int *Temp_%d;\n\n",i);
	}

	/**********************************************/
	/* [4] Declare dedicated registers as (int *) */
	/**********************************************/
	fprintf(fl,"int *sp;\n\n");
	fprintf(fl,"int *fp;\n\n");
	fprintf(fl,"int *ra;\n\n");
	fprintf(fl,"int *rv;\n\n");
	fprintf(fl,"int *a0;\n\n");
	fprintf(fl,"int *a1;\n\n");
	fprintf(fl,"int *a2;\n\n");
	fprintf(fl,"int *a3;\n\n");
	fprintf(fl,"int *v0;\n\n");
	fprintf(fl,"int *v1;\n\n");

	/**********************************************/
	/* [5] Declare dedicated registers as (int *) */
	/**********************************************/
	fprintf(fl,"int *t0;\n\n");
	fprintf(fl,"int *t1;\n\n");
	fprintf(fl,"int *t2;\n\n");
	fprintf(fl,"int *t3;\n\n");
	fprintf(fl,"int *t4;\n\n");
	fprintf(fl,"int *t5;\n\n");
	fprintf(fl,"int *t6;\n\n");
	fprintf(fl,"int *t7;\n\n");

	/****************************/
	/* [6] Function main starts */
	/****************************/
	fprintf(fl,"void main()\n\n");
 	fprintf(fl,"{\n\n");

	/**************************************************/
	/* [7] Declare dummy variables for easy debugging */
	/**************************************************/
	//fprintf(fl,"\tint b1=1;\n");
	//fprintf(fl,"\tint b2=2;\n");
	//fprintf(fl,"\tint b3=3;\n");
	//fprintf(fl,"\tint b4=4;\n");
	//fprintf(fl,"\tint b5=5;\n");
	//fprintf(fl,"\tint b6=6;\n");

	/**************************/
	/* [8] Initialize sp & fp */
	/**************************/
	//fprintf(fl,"\tsp = &b3;\n");
	//fprintf(fl,"\tfp = &b2;\n");

	/*****************************/
	/* [9] Generate C Simulation */
	/*****************************/
	for (expList=AST;expList;expList=expList->tail)
	{
		CodeGenerationExp(expList->head);
	}

	/***************************/
	/* [10] Function main ends */
	/***************************/
	fprintf(fl,"}\n\n");
	fclose(fl);
}

/**********************************/
/* Pseduo_Assembley_To_Simulation */
/**********************************/
void Pseudo_Assembley_To_Simulation(string Pseudo_Assembley_Filename,string simulation_filename)
{
	/**********************************/
	/* [1] Build Abstract Syntax Tree */
	/**********************************/
	AST=Pseudo_Assembley_To_AST(Pseudo_Assembley_Filename);

	/***************************/
	/* [2] AST To simulation.c */
	/***************************/
	AST_To_Simulation(AST,simulation_filename);
}
