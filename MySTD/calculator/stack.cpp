#include "stack.h"
#include <cstdlib>
//
// Created by ASUS on 2021/3/26.
//
int push(STACK *stack, void* element){
    stack->top ++;
    if(stack->top >= MAX_STACK)
    {
//		printf("the stack is full!\n");
        return 1;
    }
    stack->st[stack->top] = element;
//	printf("push:%c\n", ch);
    return 0;
}


void* pop(STACK *stack){
    if(stack->top <= -1)
    {
//		printf("the stack is empty!\n");
        void * res = nullptr;
        return res;
    }
//	printf("pop:%d\n", stack->st[stack->top]);
    void * res = stack->st[stack->top];
    stack->top -- ;
    return res;
}


int popa(STACK *stack){
    //弹出堆栈所有元素
    stack->top = -1;
    return 0;
}
