//
// 测试公用小工具的实现（原来在 5 个测试文件里各写一份）
//
#include "TestHelper.h"

const VertexType AEVexData[AE_VEX_NUM] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
};

// 边权 = 链路代价（相对值，非绝对延迟）：
//   1-2  末端设备最后一跳（同机柜直连）
//   3-4  区内跨柜
//   5-6  跨区主干
//   7-9  跨层干线 / 冗余对角线（越大越不会被 MST 选中）
const Edge AEEdgeList[AE_EDGE_NUM] = {
    {0,1, 2}, {0,2, 4}, {0,3, 5}, {0,5, 6}, {1,4, 3}, {4,2, 2}, {4,0, 3}, {4,5, 5}, {9,0, 7},
    {5,6, 2}, {5,7, 3}, {7,8, 1}, {5,15, 6},
    {3,11, 2},
    {9,10, 3}, {9,14, 4}, {14,13, 2}, {13,12, 3}, {10,12, 5},
    {15,16, 2}, {16,17, 2}, {17,18, 2}, {18,16, 4}, {18,15, 3}
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
