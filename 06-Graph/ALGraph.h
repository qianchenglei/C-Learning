//
// Created by 14266 on 2026/11/9.
//

#ifndef C_LEARNING_GRAPH_H
#define C_LEARNING_GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "GraphTypes.h"



typedef struct VertexNode {
    int        Id;
    VertexType VexData;
    struct EdgeNode *FirstEdge;
    struct VertexNode  *NextVertex;
}VertexNode;

typedef struct EdgeNode{
    VertexNode *ToVertex;
    struct EdgeNode *NextEdge;

} EdgeNode;

typedef struct ALGraph {
    VertexNode *Head;
    int VexNum, EdgeNum;
    int Directed;
}ALGraph;

/* RowGraph 已搬到 GraphTypes.h，两版共用 */
typedef void (*VisitFn)(VertexNode *V);
void InitALGraph(ALGraph *ALG,int Directed);
void CreateALGraph(ALGraph *ALG,const RowGraph *Src,int Directed);
void InsertALGraphEdge(ALGraph *ALG,VertexNode *A,VertexNode *B);
void DeleteALGraphEdge(ALGraph *ALG,VertexNode *A,VertexNode *B);
void InsertVertexNode(ALGraph *ALG,VertexType Data);
void DeleteVertexNode(ALGraph *ALG,VertexNode *Node);
void PrintALGraph(ALGraph *ALG);
void DFSTraverse(ALGraph *ALG, VisitFn Visit);
void BFSTraverse(ALGraph *ALG, VisitFn Visit);
bool TopoSort(ALGraph *ALG,int *Order);
#endif //C_LEARNING_GRAPH_H
