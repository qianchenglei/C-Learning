//
// Created by 14266 on 2026/11/9.
//

#include "Graph.h"
static VertexNode* InitVertexNode(VertexType Data, int Id) {
    VertexNode *Vertex = (VertexNode*) malloc(sizeof(VertexNode));
    if (Vertex == NULL) {return NULL;}
    Vertex->VexData = Data;
    Vertex->Id = Id;
    Vertex->NextVertex=NULL;
    Vertex->FirstEdge = NULL;
    return Vertex;
}
static EdgeNode* InitEdgeNode(VertexNode *to) {
    EdgeNode *Edge = (EdgeNode*) malloc(sizeof(EdgeNode));
    if (Edge == NULL) {return NULL;}
    Edge->ToVertex = to;
    Edge->NextEdge = NULL;
    return Edge;
}
void InitALGraph(ALGraph *G) {
    G->VexNum = 0;
    G->EdgeNum = 0;
    G->Head=InitVertexNode(0,-1);
}

void CreateALGraph(ALGraph *G, RowGraph *Src) {
    VertexNode *FlaxableIdx[Src->VexNum];
    VertexNode *Tail=G->Head;
    for (int i = 0; i < Src->VexNum; i++) {
        Tail->NextVertex=InitVertexNode(Src->VFrom[i],i);
        Tail=Tail->NextVertex;
        FlaxableIdx[i]=Tail;
        G->VexNum++;
    }
    for (int i = 0; i < Src->EdgeNum; i++) {
        VertexNode *A=FlaxableIdx[Src->EFrom[i].U];
        VertexNode *B=FlaxableIdx[Src->EFrom[i].V];

        EdgeNode *Edge_A=InitEdgeNode(B);
        Edge_A->NextEdge=A->FirstEdge;
        A->FirstEdge=Edge_A;

        EdgeNode *Edge_B=InitEdgeNode(A);
        Edge_B->NextEdge=B->FirstEdge;
        B->FirstEdge=Edge_B;

        G->EdgeNum++;
    }
}

void InsertALGraphEdge(ALGraph *G,VertexNode *A,VertexNode *B) {
    for (EdgeNode *e = A->FirstEdge; e != NULL; e = e->NextEdge) {
        if (e->ToVertex == B) {return ;}
    }
    EdgeNode* A_Start = InitEdgeNode(B);
    EdgeNode *B_Start = InitEdgeNode(A);
    if (A_Start == NULL||B_Start==NULL) {
        free(A_Start);
        free(B_Start);
        return ;
    }
    A_Start->NextEdge=A->FirstEdge;
    A->FirstEdge=A_Start;
    B_Start->NextEdge=B->FirstEdge;
    B->FirstEdge=B_Start;
    G->EdgeNum++;
}
