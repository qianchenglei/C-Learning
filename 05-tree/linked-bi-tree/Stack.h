//
// Created by 14266 on 2026/11/2.
//

#ifndef LINKED_OF_A_BINARY_TREE_STACK_H
#define LINKED_OF_A_BINARY_TREE_STACK_H
#define MaxStackSize 100
#include "LinkedOfBinaryTree.h"

typedef BinaryTreeNode *StackElement;

typedef struct Stack {
    StackElement data[MaxStackSize];
    int top;
}Stack;

void InitStack(Stack *S);
bool StackEmpty(const Stack *S);
bool StackFull(const Stack *S);
bool Push(Stack *S, StackElement data);
bool Pop(Stack *S, StackElement *data);
bool GetTop(const Stack *S, StackElement *data);
int  StackLength(const Stack *S);

#endif //LINKED_OF_A_BINARY_TREE_STACK_H
