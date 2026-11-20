//
// 测试公用小工具：五个测试文件里重复出现的查询 / 计数，集中到这一份。
// 只给 ai-tests 用，不进生产代码。
//
#ifndef C_LEARNING_TESTHELPER_H
#define C_LEARNING_TESTHELPER_H

#include "ALGraph.h"

/* AE 实机网络样本：19 个顶点、24 条无向边（简单图口径，两对重边各留一条） */
#define AE_VEX_NUM  19
#define AE_EDGE_NUM 24
extern const VertexType AEVexData[AE_VEX_NUM];
extern const Edge       AEEdgeList[AE_EDGE_NUM];
extern const RowGraph   AESource;

/* 按 Id 找顶点；找不到返回 NULL */
VertexNode *FindVertexById(ALGraph *ALG, int Id);

/* 该顶点边链上的结点数：无向图 = 度，有向图 = 出度 */
int VertexDegree(VertexNode *V);

/* From 的边链里是否有指向 To 的那一条（指针直接比） */
bool VertexLinkedTo(VertexNode *From, VertexNode *To);

/* 全图所有顶点边链结点数之和：无向 = 2|E|，有向 = |E| */
int GraphSumDegree(ALGraph *ALG);

/* 指向 Target 的边有多少条：入边散在别人链上，只能全图扫一遍 */
int GraphInDegree(ALGraph *ALG, VertexNode *Target);

#endif //C_LEARNING_TESTHELPER_H
