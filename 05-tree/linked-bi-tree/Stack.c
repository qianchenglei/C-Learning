//
// Created by 14266 on 2026/11/2.
//
#include "Stack.h"
#include <string.h>   /* memset */
#include <stddef.h>   /* NULL */

void InitStack(Stack *S) {
    if (S == NULL) {
        return;
    }
    S->top = -1;
    memset(S->data, 0, sizeof(S->data));
}

bool StackEmpty(const Stack *S) {
    if (S->top == -1) {
        return true;
    }else {
        return false;
    }
}

bool StackFull(const Stack *S) {
    if (S->top == MaxStackSize - 1) {
        return true;
    }else {
        return false;
    }
}

bool Push(Stack *S, StackElement data) {
    if (S->top == MaxStackSize - 1) {
        return false;
    }
    S->data[++S->top] = data;
    return true;
}

bool Pop(Stack *S, StackElement *data) {
    if (S->top == -1) {
        return false;
    }
    *data = S->data[S->top];
    S->data[S->top]= NULL;
    S->top--;
    return true;
}

bool GetTop(const Stack *S, StackElement *data) {
    if (S->top == -1) {
        return false;
    }
    *data = S->data[S->top];
    return true;
}

int StackLength(const Stack *S) {
    if (S->top == -1) {
        return 0;
    }
    return S->top + 1;
}
