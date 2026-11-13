//
// Created by 14266 on 2026/11/9.
//

#include "Graph.h"

#include <string.h>

static void LinkOneToOther(VertexNode *A, EdgeNode *Edge_A) {
    Edge_A->NextEdge = A->FirstEdge;
    A->FirstEdge = Edge_A;
}

static VertexNode *InitVertexNode(VertexType Data, int Id) {
    VertexNode *Vertex = (VertexNode *) malloc(sizeof(VertexNode));
    if (Vertex == NULL) { return NULL; }
    Vertex->VexData = Data;
    Vertex->Id = Id;
    Vertex->NextVertex = NULL;
    Vertex->FirstEdge = NULL;
    return Vertex;
}

static EdgeNode *InitEdgeNode(VertexNode *to) {
    EdgeNode *Edge = (EdgeNode *) malloc(sizeof(EdgeNode));
    if (Edge == NULL) { return NULL; }
    Edge->ToVertex = to;
    Edge->NextEdge = NULL;
    return Edge;
}

static void FindEdge(ALGraph *G, const VertexNode *A, const VertexNode *B, EdgeNode **Back_Edge, EdgeNode **Back_Prev) {
    (*Back_Prev) = NULL;
    (*Back_Edge) = NULL;
    EdgeNode *A_Prev = NULL, *A_Edge = A->FirstEdge;
    while (A_Edge != NULL && A_Edge->ToVertex != B) {
        A_Prev = A_Edge;
        A_Edge = A_Edge->NextEdge;
    }
    if (A_Edge == NULL) { return; }
    (*Back_Prev) = A_Prev;
    (*Back_Edge) = A_Edge;
}
static void DFS(VertexNode *V, bool *Visited) {
    Visited[V->Id] = true;
    for (EdgeNode *e = V->FirstEdge; e != NULL; e = e->NextEdge) {
        if (!Visited[e->ToVertex->Id]) { DFS(e->ToVertex, Visited); }
    }
}
void InitALGraph(ALGraph *G) {
    G->VexNum = 0;
    G->EdgeNum = 0;
    G->Head = InitVertexNode(0, -1);
}

void CreateALGraph(ALGraph *G, const RowGraph *Src) {
    VertexNode *FlaxableIdx[Src->VexNum];
    VertexNode *Tail = G->Head;
    for (int i = 0; i < Src->VexNum; i++) {
        Tail->NextVertex = InitVertexNode(Src->VFrom[i], i);
        Tail = Tail->NextVertex;
        FlaxableIdx[i] = Tail;
        G->VexNum++;
    }
    for (int i = 0; i < Src->EdgeNum; i++) {
        VertexNode *A = FlaxableIdx[Src->EFrom[i].U];
        VertexNode *B = FlaxableIdx[Src->EFrom[i].V];

        EdgeNode *Edge_A = InitEdgeNode(B);
        LinkOneToOther(A, Edge_A);

        EdgeNode *Edge_B = InitEdgeNode(A);
        LinkOneToOther(B, Edge_B);
        G->EdgeNum++;
    }
}

void InsertALGraphEdge(ALGraph *G, VertexNode *A, VertexNode *B) {
    for (EdgeNode *e = A->FirstEdge; e != NULL; e = e->NextEdge) {
        if (e->ToVertex == B) { return; }
    }
    EdgeNode *A_Start = InitEdgeNode(B);
    EdgeNode *B_Start = InitEdgeNode(A);
    if (A_Start == NULL || B_Start == NULL) {
        free(A_Start);
        free(B_Start);
        return;
    }
    LinkOneToOther(A, A_Start);
    LinkOneToOther(B, B_Start);
    G->EdgeNum++;
}

void DeleteALGraphEdge(ALGraph *G, VertexNode *A, VertexNode *B) {
    EdgeNode *A_Prev = NULL, *A_Edge = NULL;
    EdgeNode *B_Prev = NULL, *B_Edge = NULL;
    FindEdge(G, A, B, &A_Edge, &A_Prev);
    FindEdge(G, B, A, &B_Edge, &B_Prev);

    if (A_Edge == NULL || B_Edge == NULL) { return; }
    if (A_Prev == NULL) {
        A->FirstEdge = A_Edge->NextEdge;
    } else {
        A_Prev->NextEdge = A_Edge->NextEdge;
    }
    if (B_Prev == NULL) {
        B->FirstEdge = B_Edge->NextEdge;
    } else {
        B_Prev->NextEdge = B_Edge->NextEdge;
    }
    free(A_Edge);
    free(B_Edge);
    G->EdgeNum--;
}

void InsertVertexNode(ALGraph *G, VertexType Data) {
    VertexNode *Tail = G->Head;
    int MaxId = -1;
    while (Tail->NextVertex != NULL) {
        Tail = Tail->NextVertex;
        if (MaxId < Tail->Id) { MaxId = Tail->Id; }
    }
    VertexNode *Cur = (VertexNode *) malloc(sizeof(VertexNode));
    if (Cur == NULL) { return; }
    Cur->VexData = Data;
    Cur->Id = MaxId + 1;
    Cur->FirstEdge = NULL;
    Cur->NextVertex = NULL;
    Tail->NextVertex = Cur;
    G->VexNum++;
}

void DeleteVertexNode(ALGraph *G, VertexNode *Node) {
    while (Node->FirstEdge != NULL) {
        VertexNode *Temp = Node->FirstEdge->ToVertex;
        DeleteALGraphEdge(G, Node, Temp);
    }
    VertexNode *Prev = G->Head;
    while (Prev->NextVertex != Node) {
        Prev = Prev->NextVertex;
    }
    Prev->NextVertex = Node->NextVertex;
    free(Node);
    G->VexNum--;
}

void PrintALGraph(ALGraph *G) {
    printf("ALGraph |V|=%d |E|=%d\n", G->VexNum, G->EdgeNum);
    for (VertexNode *v = G->Head->NextVertex; v != NULL; v = v->NextVertex) {
        printf("%3d(VexData=%d):", v->Id, v->VexData);
        for (EdgeNode *e = v->FirstEdge; e != NULL; e = e->NextEdge) {
            printf("->%d", e->ToVertex->Id);
        }
        printf("\n");
    }
}

void DFSTreverse(ALGraph *G) {
    VertexNode *Tail = G->Head;
    int MaxId = -1;
    while (Tail->NextVertex != NULL) {
        Tail = Tail->NextVertex;
        if (MaxId < Tail->Id) { MaxId = Tail->Id; }
    }
    bool *Visited=(bool *)malloc(MaxId+1*sizeof(bool));
    memset(Visited,0,G->VexNum*sizeof(bool));
    for (VertexNode *v = Tail->NextVertex; v != NULL; v = v->NextVertex) {
        if (!Visited[v->Id]) { DFS(v,Visited); }
    }
    free(Visited);
}
