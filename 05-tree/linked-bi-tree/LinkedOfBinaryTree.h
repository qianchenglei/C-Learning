//
// Created by 14266 on 2026/10/31.
//
#pragma once
#ifndef LINKED_OF_A_BINARY_TREE_LINKEDOFBINARYTREE_H
#define LINKED_OF_A_BINARY_TREE_LINKEDOFBINARYTREE_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"
typedef char ElementType;
typedef struct BinaryTreeNode {
    struct BinaryTreeNode *Left;
    ElementType data;
    struct BinaryTreeNode *Right;
}BinaryTreeNode,BinaryTree;

void Init(BinaryTree **root);
void BuildBiTree(BinaryTree **root, const ElementType **Seq);
bool IsBiTreeEmpty(const BinaryTree *Root);
int  BiTreeDepth(const BinaryTree *Root);
void PreOrder(BinaryTree *Node);
void InOrder(BinaryTree *Node);
void PostOrder(BinaryTree *Node);
int  NodeCount(const BinaryTree *Node);
int  LeafCount(const BinaryTree *Node);
bool IsComplete(const BinaryTree *Root);


#endif //LINKED_OF_A_BINARY_TREE_LINKEDOFBINARYTREE_H
