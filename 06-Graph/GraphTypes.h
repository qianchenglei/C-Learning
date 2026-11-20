//
// 06-Graph 公用类型：邻接表（ALGraph）与邻接矩阵（MGraph）共用的那一份。
// 只放与存储方式无关的定义：顶点数据类型、原料层的边、原料层的 V/E 表。
// 不放 VertexNode / EdgeNode / ALGraph / MGraph / 任何一个指针结构。
//

#ifndef C_LEARNING_GRAPH_TYPES_H
#define C_LEARNING_GRAPH_TYPES_H

/* 顶点里存什么数据 —— 两版共用，改这里两版一起变 */
typedef int VertexType;

/* 原料层的一条边：起点编号、终点编号（无向图只存一条，有向图存弧） */
typedef struct {
    int U;
    int V;
} Edge;

/* 原料层：V 表 + E 表。不依赖任何指针，可落盘，可喂给任意存储结构 */
typedef struct RawGraph {
    const VertexType *VFrom;
    const Edge       *EFrom;
    int VexNum;
    int EdgeNum;
} RowGraph;

#endif // C_LEARNING_GRAPH_TYPES_H
