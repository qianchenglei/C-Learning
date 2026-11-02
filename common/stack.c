#include "stack.h"

void InitStack(Stack *S) {
    if (S == NULL) return;
    S->top = -1;
}

bool StackEmpty(const Stack *S) { return S->top == -1; }
bool StackFull(const Stack *S)  { return S->top == STACK_MAX - 1; }

bool Push(Stack *S, void *x) {
    if (StackFull(S)) return false;
    S->data[++S->top] = x;          /* 先抬，后放 */
    return true;
}

bool Pop(Stack *S, void **x) {
    if (StackEmpty(S)) return false;
    *x = S->data[S->top];           /* 先取 */
    S->data[S->top] = NULL;         /* 清残留，便于调试 */
    S->top--;                       /* 后降 */
    return true;
}

bool GetTop(const Stack *S, void **x) {
    if (StackEmpty(S)) return false;
    *x = S->data[S->top];
    return true;
}

int StackLength(const Stack *S) { return S->top + 1; }
