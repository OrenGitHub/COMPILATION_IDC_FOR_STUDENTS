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
#include "FILE_01_util.h"
#include "FILE_16_PseudoAsm_To_Simulation_ErrorMsg.h"
#include "FILE_19_PseudoAsm_To_Simulation_AST.h"
#include "FILE_18_PseudoAsm_To_Simulation_Parser.h"

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
int PSEUDO_MIPS_ASM_AST_charPos=1;

/******************/
/* PROVIDE ZZWRAP */
/******************/
int zzwrap(void)
{
	PSEUDO_MIPS_ASM_AST_charPos=1;
	return 1;
}

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
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
".data"									{PSEUDO_MIPS_ASM_AST_adjust(); continue;}
".word"									{PSEUDO_MIPS_ASM_AST_adjust(); continue;}
".asciiz"								{PSEUDO_MIPS_ASM_AST_adjust(); continue;}
\n										{PSEUDO_MIPS_ASM_AST_adjust(); PSEUDO_MIPS_ASM_AST_EM_newline(); printf("\n"); continue;}
\n\r									{PSEUDO_MIPS_ASM_AST_adjust(); PSEUDO_MIPS_ASM_AST_EM_newline(); printf("\n"); continue;}
\r\n									{PSEUDO_MIPS_ASM_AST_adjust(); PSEUDO_MIPS_ASM_AST_EM_newline(); printf("\n"); continue;}
".text"									{PSEUDO_MIPS_ASM_AST_adjust(); printf(".text"); return START_OF_CODE;}
li" "$v0,1[\n\r\t]*syscall				{PSEUDO_MIPS_ASM_AST_adjust(); printf("PRINT INT");return PRINT_INT;}
li" "$v0,9[\n\r\t]*syscall				{PSEUDO_MIPS_ASM_AST_adjust(); printf("ALLOCATE");return ALLOCATE;}
li" "$v0,11[\n\r\t]*syscall				{PSEUDO_MIPS_ASM_AST_adjust(); printf("PRINT_CHAR");return PRINT_CHAR;}
li" "$v0,10[\n\r\t]*syscall				{PSEUDO_MIPS_ASM_AST_adjust(); printf("EXIT");   return EXIT;}
","										{PSEUDO_MIPS_ASM_AST_adjust(); printf(", ");     return COMMA;}
":"										{PSEUDO_MIPS_ASM_AST_adjust(); printf(":");      return COLON;}
lw										{PSEUDO_MIPS_ASM_AST_adjust(); printf("LOAD ");  return LOAD;}
sw										{PSEUDO_MIPS_ASM_AST_adjust(); printf("STORE "); return STORE;}
li										{PSEUDO_MIPS_ASM_AST_adjust(); printf("LOADI "); return LOAD_IMMEDIATE;}
la										{PSEUDO_MIPS_ASM_AST_adjust(); printf("LOADA "); return LOAD_ADDRESS;}
lb										{PSEUDO_MIPS_ASM_AST_adjust(); printf("LOADB "); return LOAD_BYTE;}
sb										{PSEUDO_MIPS_ASM_AST_adjust(); printf("STOREB ");return STORE_BYTE;}
j										{PSEUDO_MIPS_ASM_AST_adjust(); printf("JUMP ");  return JUMP;}
jr										{PSEUDO_MIPS_ASM_AST_adjust(); printf("JUMP ");  return JUMP;}
jal										{PSEUDO_MIPS_ASM_AST_adjust(); printf("JAL ");   return JUMP_AND_LINK;}
jalr									{PSEUDO_MIPS_ASM_AST_adjust(); printf("JALR");   return JUMP_AND_LINK_REG;}
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
String_[0-9]+							{PSEUDO_MIPS_ASM_AST_adjust(); zzlval.gval.sval=String(zztext);   printf("STRING VAR(%s)",zzlval.gval.sval); return STRING_VAR;}
VFTable_[0-9a-zA-Z]+					{PSEUDO_MIPS_ASM_AST_adjust(); zzlval.gval.sval=String(zztext);   printf("VFTABLE(%s)",   zzlval.gval.sval); return VFTABLE;}
"$"[a-zA-Z]+[0-9a-zA-Z]+				{PSEUDO_MIPS_ASM_AST_adjust(); zzlval.gval.sval=String(zztext+1); printf("REGISTER( %s )",zzlval.gval.sval); return REGISTER;}
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
.										{
											PSEUDO_MIPS_ASM_AST_adjust();
											PSEUDO_MIPS_ASM_AST_EM_error(PSEUDO_MIPS_ASM_AST_EM_tokPos,"illegal token = %s",zztext);
										}
										
										
										
										
										
										
										
