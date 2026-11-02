#ifndef SQ_BI_TREE_H
#define SQ_BI_TREE_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MaxChindUnit 99
typedef char ElemType;
typedef struct SqBinaryTree 
{
    ElemType data [MaxChindUnit+1];
    int n;
}SqBinaryTree;

void InItBinaryTree(SqBinaryTree *T);
void CreateBinaryTree(SqBinaryTree *T,const ElemType *S);
bool IsBiTreeEmpty(const SqBinaryTree *T);
int  BiTreeDepth(const SqBinaryTree *T);
void PreOrder(const SqBinaryTree *T, int index);
void InOrder(const SqBinaryTree *T, int index);
void PostOrder(const SqBinaryTree *T, int index);
int  NodeCount(const SqBinaryTree *T);
int  LeafCount(const SqBinaryTree *T);
bool  IsComplete(const SqBinaryTree *T);
#endif