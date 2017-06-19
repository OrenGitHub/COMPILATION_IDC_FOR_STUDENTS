/*********************/
/* FILE NAME: temp.c */
/*********************/

/****************************************/
/* WARNING DISABLE: sprintf - I love it */
/****************************************/
#pragma warning (disable: 4996)

/*****************/
/* INCLUDE FILES */
/*****************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_01_util.h"
#include "FILE_02_symbol.h"
#include "FILE_09_GenericTable.h"
#include "FILE_15_Temporaries_and_Labels.h"

/***************/
/* DEFINITIONS */
/***************/
#define MAX_NAME_LENGTH_OF_LABEL 100
#define LOG_2_MAX_NUM_TEMPORARIES 16

/********************/
/* GLOBAL VARIABLES */
/********************/
static int labels = 3;

/**************/
/* STRUCTURES */
/**************/
struct Temp_temp_ {int num;};

static int temps = 0;

int TEMP_numTemporariesAllocated(void)
{
	return temps;
}

string Temp_labelstring(Temp_label s)
{
	return S_name(s);
}

Temp_label Temp_newlabel(const char *LabelNameSuffix)
{
	char buf[MAX_NAME_LENGTH_OF_LABEL];
	
	sprintf(buf,"Label_%d_%s",labels++,LabelNameSuffix);
	
	return Temp_namedlabel(String(buf));
}

/* The label will be created only if it is not found. */
Temp_label Temp_namedlabel(string s)
{
	return S_Symbol(s);
}

Temp_temp Temp_newtemp(const char *name)
{
	Temp_temp p = (Temp_temp) checked_malloc(sizeof (*p));
	
	p->num=temps++;
	{
		char r[LOG_2_MAX_NUM_TEMPORARIES];

		if (strcmp(name,"") == 0)
		{
			sprintf(r, "%s_%d","Temp",p->num);
		}
		else
		{
			strcpy(r,name);
		}
		Temp_enter(Temp_name(), p, String(r));
	}
	
	return p;
}

struct Temp_map_ {TAB_table tab; Temp_map under;};

Temp_map Temp_name(void) {
 static Temp_map m = NULL;
 if (!m) m=Temp_empty();
 return m;
}

Temp_map newMap(TAB_table tab, Temp_map under) {
  Temp_map m = checked_malloc(sizeof(*m));
  m->tab=tab;
  m->under=under;
  return m;
}

Temp_map Temp_empty(void) {
  return newMap(TAB_empty(), NULL);
}

Temp_map Temp_layerMap(Temp_map over, Temp_map under) {
  if (over==NULL)
      return under;
  else return newMap(over->tab, Temp_layerMap(over->under, under));
}

void Temp_enter(Temp_map m, Temp_temp t, string s) {
  assert(m && m->tab);
  TAB_enter(m->tab,t,s);
}

string Temp_look(Temp_map m, Temp_temp t) {
  string s;
  assert(m && m->tab);
  s = TAB_look(m->tab, t);
  if (s) return s;
  else if (m->under) return Temp_look(m->under, t);
  else return NULL;
}

Temp_tempList Temp_TempList(Temp_temp h, Temp_tempList t) 
{Temp_tempList p = (Temp_tempList) checked_malloc(sizeof (*p));
 p->head=h; p->tail=t;
 return p;
}

Temp_labelList Temp_LabelList(Temp_label h, Temp_labelList t)
{Temp_labelList p = (Temp_labelList) checked_malloc(sizeof (*p));
 p->head=h; p->tail=t;
 return p;
}
