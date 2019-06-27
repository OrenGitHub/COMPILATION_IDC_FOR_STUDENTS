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
#include "FILE_22_RegAlloc_ErrorMsg.h"
#include "FILE_24_RegAlloc_Parser.h"

int TEMPS_TO_REGS_charPos=1;

int ggwrap(void)
{
	TEMPS_TO_REGS_charPos=1;
	return 1;
}

void TEMPS_TO_REGS_adjust(void)
{
	TEMPS_TO_REGS_EM_tokPos=TEMPS_TO_REGS_charPos;
	TEMPS_TO_REGS_charPos+=ggleng;
}

%}

%option prefix="gg"

%%

" "									{TEMPS_TO_REGS_adjust(); return SPACE;}
\t									{TEMPS_TO_REGS_adjust(); return TAB;}
","									{TEMPS_TO_REGS_adjust(); return COMMA;}
"("									{TEMPS_TO_REGS_adjust(); return LPAREN;}
")"									{TEMPS_TO_REGS_adjust(); return RPAREN;}
\n									{TEMPS_TO_REGS_adjust(); TEMPS_TO_REGS_EM_newline(); return NEWLINE;}
Temp_[0-9]+[0-9]*					{
										TEMPS_TO_REGS_adjust();
										gglval.gval.temp_serial_number=atoi(ggtext+strlen("Temp_"));

										return TEMP;
									}
-[0-9]+								{
										TEMPS_TO_REGS_adjust();

										printf("%s\n",ggtext);

										printf("0x%d",&(ggtext[0]));

										gglval.gval.sval = String(ggtext);
										
										return ANY_OTHER_THING;
									}
[a-zA-Z0-9_".":+$]+					{
										TEMPS_TO_REGS_adjust();

										printf("%s\n",ggtext);

										printf("0x%d",&(ggtext[0]));

										gglval.gval.sval = String(ggtext);
										
										return ANY_OTHER_THING;
									}

