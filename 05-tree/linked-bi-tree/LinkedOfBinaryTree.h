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
typedef struct ThreadBinaryTree {
    struct ThreadBinaryTree *Left;
    int Left_Symbol;
    ElementType data;
    int Right_Symbol;
    struct ThreadBinaryTree *Right;
}BinaryTreeNode,BinaryTree,ThreadBinaryTree;

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
void ThreadingBiTree(BinaryTree *Root);

/* 中序线索树上的操作：找首结点、找后继、无线索化遍历 */
BinaryTree *FirstNode(BinaryTree *p);
BinaryTree *NextNode(BinaryTree *p);
void InOrderThread(BinaryTree *root);

#endif //LINKED_OF_A_BINARY_TREE_LINKEDOFBINARYTREE_H
