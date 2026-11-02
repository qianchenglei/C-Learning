#ifndef COMMON_STACK_H
#define COMMON_STACK_H

#include <stdbool.h>

/* 存 void* 的通用栈：树结点、链表结点、任何指针都能装。
   元素类型不固定，所以不做类型检查，取出时自行强转。 */
#define STACK_MAX 100

typedef struct {
    void *data[STACK_MAX];
    int top;                 /* -1 为空，指向栈顶元素 */
} Stack;

void InitStack(Stack *S);
bool StackEmpty(const Stack *S);
bool StackFull(const Stack *S);
bool Push(Stack *S, void *x);
bool Pop(Stack *S, void **x);
bool GetTop(const Stack *S, void **x);
int  StackLength(const Stack *S);

#endif /* COMMON_STACK_H */
