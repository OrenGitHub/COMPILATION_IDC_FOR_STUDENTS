#ifndef __STACK_H__
#define __STACK_H__

typedef struct Stack {
	char c;
	int state;
	struct Stack *next;
} Stack;

void PrintStack(Stack *stack);
Stack *Top(Stack *stack);
void Push(Stack *stack,int state,char c);
void Pop(Stack *stack);
#endif