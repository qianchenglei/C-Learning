//
// Created by 14266 on 2026/11/9.
//

#ifndef C_LEARNING_GRAPH_H
#define C_LEARNING_GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef int VertexType;
typedef struct { int U, V; } Edge;

typedef struct VertexNode {
    int        Id;
    VertexType VexData;
    struct EdgeNode *FirstEdge;
    struct VertexNode  *NextVertex;
}VertexNode;

typedef struct EdgeNode{
    VertexNode *ToVertex;
    struct EdgeNode *NextEdge;
    // int Weight;
} EdgeNode;

typedef struct ALGraph {
    VertexNode *Head;
    int VexNum, EdgeNum;

}ALGraph;

typedef struct RawGraph {
    const VertexType *VFrom;
    const Edge *EFrom;
    int VexNum, EdgeNum;
}RowGraph;

void InitALGraph(ALGraph *G);
void CreateALGraph(ALGraph *G,RowGraph *Src);
void InsertALGraphEdge(ALGraph *G,VertexNode *A,VertexNode *B);
#endif //C_LEARNING_GRAPH_H
