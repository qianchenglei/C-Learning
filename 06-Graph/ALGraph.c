//
// Created by 14266 on 2026/11/9.
//

#include "ALGraph.h"
#include "queue.h"
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

static void FindEdge(ALGraph *ALG, const VertexNode *A, const VertexNode *B, EdgeNode **Back_Edge, EdgeNode **Back_Prev) {
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
static void DFS(VertexNode *V, bool *Visited, VisitFn Visit) {
    Visited[V->Id] = true;
    Visit(V);
    for (EdgeNode *e = V->FirstEdge; e != NULL; e = e->NextEdge) {
        if (!Visited[e->ToVertex->Id]) { DFS(e->ToVertex, Visited, Visit); }
    }
}
void InitALGraph(ALGraph *ALG,int Directed) {
    ALG->VexNum = 0;
    ALG->EdgeNum = 0;
    ALG->Directed = Directed;
    ALG->Head = InitVertexNode(0, -1);
}

void CreateALGraph(ALGraph *ALG, const RowGraph *Src, int Directed) {
    VertexNode *FlaxableIdx[Src->VexNum];
    VertexNode *Tail = ALG->Head;
    switch (Directed) {
        case 0: {
            ALG->Directed = 0;
            break;
        }
        case 1: {
            ALG->Directed = 1;
            break;
        }
        default: {return;}
    }
    for (int i = 0; i < Src->VexNum; i++) {
        Tail->NextVertex = InitVertexNode(Src->VFrom[i], i);
        Tail = Tail->NextVertex;
        FlaxableIdx[i] = Tail;
        ALG->VexNum++;
    }
    for (int i = 0; i < Src->EdgeNum; i++) {
        VertexNode *A = FlaxableIdx[Src->EFrom[i].U];
        VertexNode *B = FlaxableIdx[Src->EFrom[i].V];

        EdgeNode *Edge_A = InitEdgeNode(B);
        LinkOneToOther(A, Edge_A);

        if (Directed == 0) {
            EdgeNode *Edge_B = InitEdgeNode(A);
            LinkOneToOther(B, Edge_B);
        }
        ALG->EdgeNum++;
    }
}

void InsertALGraphEdge(ALGraph *ALG, VertexNode *A, VertexNode *B) {
    for (EdgeNode *e = A->FirstEdge; e != NULL; e = e->NextEdge) {
        if (e->ToVertex == B) { return; }
    }
    EdgeNode *A_Start = InitEdgeNode(B);
    EdgeNode *B_Start=NULL;
    if (ALG->Directed==0) {
        B_Start = InitEdgeNode(A);
    }
    if (A_Start == NULL ||(ALG->Directed==0 && B_Start == NULL)) {
        free(A_Start);
        free(B_Start);
        return;
    }
    LinkOneToOther(A, A_Start);
    if (ALG->Directed==0) {
        LinkOneToOther(B, B_Start);
    }
    ALG->EdgeNum++;
}

void DeleteALGraphEdge(ALGraph *ALG, VertexNode *A, VertexNode *B) {
    EdgeNode *A_Prev = NULL, *A_Edge = NULL;
    FindEdge(ALG, A, B, &A_Edge, &A_Prev);
    if (A_Edge == NULL ) { return; }
    if (A_Prev == NULL) {
        A->FirstEdge = A_Edge->NextEdge;
    } else {
        A_Prev->NextEdge = A_Edge->NextEdge;
    }
    free(A_Edge);
    ALG->EdgeNum--;
    if (ALG->Directed==0){
        EdgeNode *B_Prev = NULL, *B_Edge = NULL;
        FindEdge(ALG, B, A, &B_Edge, &B_Prev);
        if (B_Edge == NULL ) { return; }
        if (B_Prev == NULL) {
            B->FirstEdge = B_Edge->NextEdge;
        } else {
            B_Prev->NextEdge = B_Edge->NextEdge;
        }
        free(B_Edge);
    }

}

void InsertVertexNode(ALGraph *ALG, VertexType Data) {
    VertexNode *Tail = ALG->Head;
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
    ALG->VexNum++;
}

void DeleteVertexNode(ALGraph *ALG, VertexNode *Node) {
    while (Node->FirstEdge != NULL) {
        VertexNode *Temp = Node->FirstEdge->ToVertex;
        DeleteALGraphEdge(ALG, Node, Temp);
    }
    VertexNode *Prev = ALG->Head;
    while (Prev->NextVertex != Node) {
        Prev = Prev->NextVertex;
    }
    Prev->NextVertex = Node->NextVertex;
    free(Node);
    ALG->VexNum--;
}

void PrintALGraph(ALGraph *ALG) {
    printf("ALGraph |V|=%d |E|=%d\n", ALG->VexNum, ALG->EdgeNum);
    for (VertexNode *v = ALG->Head->NextVertex; v != NULL; v = v->NextVertex) {
        printf("%3d(VexData=%d):", v->Id, v->VexData);
        for (EdgeNode *e = v->FirstEdge; e != NULL; e = e->NextEdge) {
            printf("->%d", e->ToVertex->Id);
        }
        printf("\n");
    }
}

void DFSTraverse(ALGraph *ALG, VisitFn Visit) {
    VertexNode *Tail = ALG->Head;
    int MaxId = -1;
    while (Tail->NextVertex != NULL) {
        Tail = Tail->NextVertex;
        if (MaxId < Tail->Id) { MaxId = Tail->Id; }
    }
    bool *Visited = (bool *)malloc((MaxId + 1) * sizeof(bool));
    if (Visited == NULL) { return; }
    memset(Visited, 0, (MaxId + 1) * sizeof(bool));
    for (VertexNode *v = ALG->Head->NextVertex; v != NULL; v = v->NextVertex) {
        if (!Visited[v->Id]) { DFS(v, Visited, Visit); }
    }
    free(Visited);
}

void BFSTraverse(ALGraph *ALG, VisitFn Visit) {
    VertexNode *Tail = ALG->Head;
    int MaxId = -1;
    while (Tail->NextVertex != NULL) {
        Tail = Tail->NextVertex;
        if (MaxId < Tail->Id) { MaxId = Tail->Id; }
    }
    bool *Visited = (bool *)malloc((MaxId + 1) * sizeof(bool));
    if (Visited == NULL) { return; }
    memset(Visited, 0, (MaxId + 1) * sizeof(bool));
    for (VertexNode *v = ALG->Head->NextVertex; v != NULL; v = v->NextVertex) {
        if (Visited[v->Id]){continue;}

        Visited[v->Id] = true;
        Queue queue;
        memset(&queue, 0, (sizeof(queue)));
        EnQueue(&queue,v);

        while (!QueueEmpty(&queue)) {
            VertexNode *Cur =NULL;
            DeQueue(&queue,(void**)&Cur);
            Visit(Cur);
            for (EdgeNode *e = Cur->FirstEdge; e != NULL; e = e->NextEdge) {
                if (!Visited[e->ToVertex->Id]) {
                    Visited[e->ToVertex->Id] = true;
                    EnQueue(&queue,e->ToVertex);
                }
            }
        }
    }
    free(Visited);
}

bool TopoSort(ALGraph *ALG, int *Order) {
    VertexNode *Tail = ALG->Head;
    int MaxId = -1;
    while (Tail->NextVertex != NULL) {
        Tail = Tail->NextVertex;
        if (MaxId < Tail->Id) { MaxId = Tail->Id; }
    }
    int *InDegree = (int*)malloc((MaxId+1)*sizeof(int));
    if (InDegree == NULL) { return false; }
    memset(InDegree, 0, (MaxId+1) * sizeof(int));
    for (VertexNode *V =ALG->Head->NextVertex;V;V=V->NextVertex) {
        for (EdgeNode *E = V->FirstEdge;E;E=E->NextEdge) {
            InDegree[E->ToVertex->Id]++;
        }
    }
    Queue Queue;
    InitQueue(&Queue);
    for (VertexNode *v=ALG->Head->NextVertex;v;v=v->NextVertex) {
        if (InDegree[v->Id] == 0) {
            EnQueue(&Queue,v);
        }
    }
    int Cut=0;
    while (!QueueEmpty(&Queue)) {
        VertexNode *Cur =NULL;
        DeQueue(&Queue,(void**)&Cur);
        Order[Cut++]=Cur->Id;
        for (EdgeNode *e = Cur->FirstEdge; e != NULL; e = e->NextEdge) {
            if (--InDegree[e->ToVertex->Id] == 0) {
                EnQueue(&Queue,e->ToVertex);
            }
        }
    }
    free(InDegree);
    return Cut==ALG->VexNum;
}
