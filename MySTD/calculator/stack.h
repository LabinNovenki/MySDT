#ifndef _STACK_H
#define _STACK_H

#define MAX_STACK 100

//¶ÑÕ»µÄÊµÏÖ 
typedef struct STACK{
	void* st[MAX_STACK];
	int top = -1; 
}STACK;


int push(STACK *stack, void* element);
void* pop(STACK *stack);
int popa(STACK *stack);
#endif
