/**********************/
/* FILE NAME: Stack.c */
/**********************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "Stack.h"

void PrintStack(Stack *stack)
{
	Stack *ptr;

	printf("[%2d] ",stack->state);

	for (ptr=stack->next;ptr;ptr=ptr->next)
	{
		if (ptr->c == 'y')
		{
			printf("INT ");
		}
		else
		{
			printf("  %c ",ptr->c);
		}
		printf("[%2d] ",ptr->state);
	}

	printf("\n");
}

Stack *Top(Stack *stack)
{
	Stack *temp=stack;

	while (temp ->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

void Push(Stack *stack,int state,char c)
{
	Stack *temp = (Stack *) malloc(sizeof(Stack));
	if (temp == NULL) return;

	temp->c = c;
	temp->state=state;
	temp->next = NULL;

	(Top(stack))->next = temp;
}

void Pop(Stack *stack)
{
	Stack *temp=stack;
	if (stack->next == NULL) return;

	while (temp->next->next != NULL)
	{
		temp = temp->next;
	}
	
	free(temp->next);
	temp->next = NULL;
}
