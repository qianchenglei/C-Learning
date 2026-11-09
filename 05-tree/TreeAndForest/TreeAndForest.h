#ifndef  TREE_AND_FOREST_TREEANDFOREST_H
#define TREE_AND_FOREST_TREEANDFOREST_H
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#define ElemType char
typedef struct BiTreeNode {
    struct BiTreeNode *Left;
    ElemType Data;
    struct BiTreeNode *Right;
}BiTreeNode,BiTree;
typedef struct Forest {
    BiTree *root;
    int Forestsize;
}Forest;

void InItBinaryTree(BiTree **Root);
void CreateBinaryTree(BiTree **Root,const ElemType **Seq);
bool IsEmpty(BiTree *Root);

#endif