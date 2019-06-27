/*********************/
/* FILE NAME: temp.c */
/*********************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "FILE_15_Temporaries_and_Labels.h"

/***************/
/* DEFINITIONS */
/***************/
#define MAX_LINE_LENGTH_OF_INTERFERENCE_GRAPH_FILE 80
#define MAX_NUM_COLORS 8

/**************/
/* STRUCTURES */
/**************/
typedef struct adj_list
{
	int node_serial_number;
	struct adj_list *next;
}
adj_list;

/********************/
/* GLOBAL VARIABLES */
/********************/
adj_list *Graph[MAX_NUM_TEMPORARIES];

void AddEdge(int i, int j)
{
	adj_list *p = (adj_list *) malloc(sizeof(*p));

	adj_list *temp = Graph[i];

	p->next = temp;
	p->node_serial_number = j;

	Graph[i] = p;
}

void Load_Interference_Graph(char *interference_graph_filename)
{
	int i=0;
	int j=0;

	char buffer[MAX_LINE_LENGTH_OF_INTERFERENCE_GRAPH_FILE];

	/*****************/
	/* [0] open file */
	/*****************/
	FILE *fl=fopen(interference_graph_filename,"rt");

	/***************************************/
	/* [1] read and ignore graphviz header */
	/***************************************/
	fgets(buffer,MAX_LINE_LENGTH_OF_INTERFERENCE_GRAPH_FILE,fl);
	fgets(buffer,MAX_LINE_LENGTH_OF_INTERFERENCE_GRAPH_FILE,fl);

	/*******************************/
	/* [2] load interference graph */
	/*******************************/
	while (buffer[0] != '}')
	{
		/*******************************/
		/* [a] read one edge from file */
		/*******************************/
		fgets(buffer,MAX_LINE_LENGTH_OF_INTERFERENCE_GRAPH_FILE,fl);

		/***************************/
		/* [b] edge format in file */
		/***************************/
		sscanf(buffer,"%d -- %d\n",&i,&j);

		/*******************************/
		/* [c] Add edges (i,j) & (j,i) */
		/*******************************/
		AddEdge(i,j);
		AddEdge(j,i);
	}
}

void Greedy_Color_Interference_Graph(int colors[MAX_NUM_TEMPORARIES])
{
	int i=0;
	adj_list *iterator=NULL;
	int least_possible_color=0;
	int used_colors[MAX_NUM_COLORS];

	/******************************/
	/* [1] Loop over all vertices */
	/******************************/
	for (i=0;i<MAX_NUM_TEMPORARIES;i++)
	{
		/********************************************/
		/* [2] initially all colors are free to use */
		/********************************************/
		memset(used_colors,0,sizeof(used_colors));

		/*************************************************/
		/* [3] see what colors are used by my neighbours */
		/*************************************************/
		for (iterator=Graph[i];iterator;iterator=iterator->next)
		{
			used_colors[colors[iterator->node_serial_number]] = 1;
		}

		/**************************************************/
		/* [4] color a node with the least possible color */
		/**************************************************/
		for (least_possible_color=0;least_possible_color<MAX_NUM_COLORS;least_possible_color++)
		{
			if (used_colors[least_possible_color] == 0)
			{
				/************************************/
				/* [5] least_possible_color is free */
				/************************************/
				colors[i] = least_possible_color;
				break;
			}
		}
	}
}

void Register_Allocation(char *interference_graph_filename, int Temporaries_To_Registers_Map[MAX_NUM_TEMPORARIES])
{
	/******************************************/
	/* [0] Clear Temporaries_To_Registers_Map */
	/******************************************/
	memset(Temporaries_To_Registers_Map,0,MAX_NUM_TEMPORARIES*sizeof(int));

	/*******************************/
	/* [1] Load Interference Graph */
	/*******************************/
	Load_Interference_Graph(interference_graph_filename);

	/*************************************************************************************/
	/* [2] Assign registers $t0 to $t7 to temporaries, by a greedy coloring of the nodes */
	/*************************************************************************************/
	Greedy_Color_Interference_Graph(Temporaries_To_Registers_Map);
}
