//
// 测试公用小工具的实现（原来在 5 个测试文件里各写一份）
//
#include "TestHelper.h"

const VertexType AEVexData[AE_VEX_NUM] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
};

const Edge AEEdgeList[AE_EDGE_NUM] = {
    {0,1},{0,2},{0,3},{0,5},{1,4},{4,2},{4,0},{4,5},{9,0},
    {5,6},{5,7},{7,8},{5,15},
    {3,11},
    {9,10},{9,14},{14,13},{13,12},{10,12},
    {15,16},{16,17},{17,18},{18,16},{18,15}
};

const RowGraph AESource = { AEVexData, AEEdgeList, AE_VEX_NUM, AE_EDGE_NUM };

VertexNode *FindVertexById(ALGraph *ALG, int Id) {
    for (VertexNode *V = ALG->Head->NextVertex; V; V = V->NextVertex) {
        if (V->Id == Id) { return V; }
    }
    return NULL;
}

int VertexDegree(VertexNode *V) {
    int EdgeCount = 0;
    for (EdgeNode *E = V->FirstEdge; E; E = E->NextEdge) { EdgeCount++; }
    return EdgeCount;
}

bool VertexLinkedTo(VertexNode *From, VertexNode *To) {
    for (EdgeNode *E = From->FirstEdge; E; E = E->NextEdge) {
        if (E->ToVertex == To) { return true; }
    }
    return false;
}

int GraphSumDegree(ALGraph *ALG) {
    int Sum = 0;
    for (VertexNode *V = ALG->Head->NextVertex; V; V = V->NextVertex) {
        Sum += VertexDegree(V);
    }
    return Sum;
}

int GraphInDegree(ALGraph *ALG, VertexNode *Target) {
    int InCount = 0;
    for (VertexNode *V = ALG->Head->NextVertex; V; V = V->NextVertex) {
        for (EdgeNode *E = V->FirstEdge; E; E = E->NextEdge) {
            if (E->ToVertex == Target) { InCount++; }
        }
    }
    return InCount;
}
