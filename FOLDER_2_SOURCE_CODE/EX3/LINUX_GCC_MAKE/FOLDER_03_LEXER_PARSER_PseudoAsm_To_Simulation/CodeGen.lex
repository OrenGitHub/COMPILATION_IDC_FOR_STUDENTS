%{
/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "util.h"
#include "PSEUDO_MIPS_ASM_AST_errormsg.h"
#include "PSEUDO_MIPS_ASM_AST.h"
#include "FILE_18_PseudoAsm_To_Simulation_Parser.h"

int PSEUDO_MIPS_ASM_AST_charPos=1;

int zzwrap(void)
{
	PSEUDO_MIPS_ASM_AST_charPos=1;
	return 1;
}

void PSEUDO_MIPS_ASM_AST_adjust(void)
{
	PSEUDO_MIPS_ASM_AST_EM_tokPos=PSEUDO_MIPS_ASM_AST_charPos;
	PSEUDO_MIPS_ASM_AST_charPos+=zzleng;
}

%}

%option prefix="zz"

%%
" "										{PSEUDO_MIPS_ASM_AST_adjust(); continue;}
\t										{PSEUDO_MIPS_ASM_AST_adjust(); continue;}
"main:"									{PSEUDO_MIPS_ASM_AST_adjust(); continue;}
\n										{PSEUDO_MIPS_ASM_AST_adjust(); PSEUDO_MIPS_ASM_AST_EM_newline(); printf("\n"); continue;}
li" "$v0,1"\n\n\t"syscall		{PSEUDO_MIPS_ASM_AST_adjust(); printf("PRINT INT");return PRINT_INT;}
li" "$v0,9"\n\n\t"syscall		{PSEUDO_MIPS_ASM_AST_adjust(); printf("ALLOCATE");return ALLOCATE;}
li" "$v0,11"\n\n\t"syscall		{PSEUDO_MIPS_ASM_AST_adjust(); printf("PRINT_CHAR");return PRINT_CHAR;}
li" "$v0,10"\n\n\t"syscall		{PSEUDO_MIPS_ASM_AST_adjust(); printf("EXIT");   return EXIT;}
","										{PSEUDO_MIPS_ASM_AST_adjust(); printf(", ");     return COMMA;}
":"										{PSEUDO_MIPS_ASM_AST_adjust(); printf(":");      return COLON;}
lw										{PSEUDO_MIPS_ASM_AST_adjust(); printf("LOAD ");  return LOAD;}
sw										{PSEUDO_MIPS_ASM_AST_adjust(); printf("STORE "); return STORE;}
li										{PSEUDO_MIPS_ASM_AST_adjust(); printf("LOADI "); return LOAD_IMMEDIATE;}
j										{PSEUDO_MIPS_ASM_AST_adjust(); printf("JUMP ");  return JUMP;}
jr										{PSEUDO_MIPS_ASM_AST_adjust(); printf("JUMP ");  return JUMP;}
jal										{PSEUDO_MIPS_ASM_AST_adjust(); printf("JAL ");   return JUMP_AND_LINK;}
add										{PSEUDO_MIPS_ASM_AST_adjust(); printf("ADD ");   return ADD;}
addi									{PSEUDO_MIPS_ASM_AST_adjust(); printf("ADDI ");  return ADD_IMMEDIATE;}
sub										{PSEUDO_MIPS_ASM_AST_adjust(); printf("SUB ");   return SUB;}
mul										{PSEUDO_MIPS_ASM_AST_adjust(); printf("MUL ");   return MUL;}
mov										{PSEUDO_MIPS_ASM_AST_adjust(); printf("MOVE ");  return MOVE;}
beq										{PSEUDO_MIPS_ASM_AST_adjust(); printf("BEQ ");   return BEQ;}
bne										{PSEUDO_MIPS_ASM_AST_adjust(); printf("BNE ");   return BNE;}
bgt										{PSEUDO_MIPS_ASM_AST_adjust(); printf("BGT ");   return BGT;}
bge										{PSEUDO_MIPS_ASM_AST_adjust(); printf("BGE ");   return BGE;}
blt										{PSEUDO_MIPS_ASM_AST_adjust(); printf("BLT ");   return BLT;}
ble										{PSEUDO_MIPS_ASM_AST_adjust(); printf("BLE ");   return BLE;}
"$"[a-zA-Z]+[0-9a-zA-Z]+				{PSEUDO_MIPS_ASM_AST_adjust(); zzlval.gval.sval=String(zztext+1); printf("REGISTER( %s ) ",zzlval.gval.sval); return REGISTER;}
"("										{PSEUDO_MIPS_ASM_AST_adjust(); printf(" ( "); return LPAREN;}
")"										{PSEUDO_MIPS_ASM_AST_adjust(); printf(" ) "); return RPAREN;}
Temp_[0-9]+[0-9]*						{
											PSEUDO_MIPS_ASM_AST_adjust();
											zzlval.gval.temp_serial_number=atoi(zztext+strlen("Temp_"));

											printf("TEMP( %d ) ",zzlval.gval.temp_serial_number);

											return TEMP;
										}
([0-9]+[0-9]*)|("-"[0-9]+[0-9]*)		{
											PSEUDO_MIPS_ASM_AST_adjust();
											zzlval.gval.ival=atoi(zztext);
											printf("INT( %d ) ",zzlval.gval.ival);
											return INT;}
Label_[0-9]+[_][a-zA-Z]+[a-zA-Z_]*		{
											char *s;
											PSEUDO_MIPS_ASM_AST_adjust();
										
											strcpy(zzlval.gval.label.name,zztext);
											s=zztext+strlen("Label_");
											while (*s != '_') {s++;}
											*s = 0;
											zzlval.gval.label.serial_number=atoi(zztext+strlen("Label_"));
											*s = '_';

											printf("LABEL( %s ) with SERIAL NUMBER = %d\n",zztext,zzlval.gval.label.serial_number);

											return LABEL;
										}
\"[0-9a-zA-Z ]*\"						{PSEUDO_MIPS_ASM_AST_adjust(); zzlval.gval.sval=String(zztext); return STRING;}
[0-9]+"."[0-9]*							{PSEUDO_MIPS_ASM_AST_adjust(); zzlval.gval.fval=(float) atof(zztext); return FLOAT;}
"."[0-9]+								{PSEUDO_MIPS_ASM_AST_adjust(); zzlval.gval.fval=(float) atof(zztext); return FLOAT;}
.										{PSEUDO_MIPS_ASM_AST_adjust(); PSEUDO_MIPS_ASM_AST_EM_error(PSEUDO_MIPS_ASM_AST_EM_tokPos,"illegal token");}
