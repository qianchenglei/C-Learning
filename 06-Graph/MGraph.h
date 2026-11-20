//
// Created by 14266 on 2026/11/20.
//

#ifndef C_LEARNING_MGRAPH_H
#define C_LEARNING_MGRAPH_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "GraphTypes.h"

typedef int
EdgeType;
#define NOVEX (-1)
#define NOEDGE (-1)
typedef struct MGraph {
    VertexType *Vex;
    EdgeType *Edge;
    int IdCap;//矩阵边长=MaxId+1
    int VexNum;
    int EdgeNum;
    int Directed;//无向 0 有向 1 未初始化-1；
}MGraph;

void InitMGraph(MGraph *MG);
void CreateMGraph(MGraph *MG,const RowGraph *RG,int Directed);
#endif //C_LEARNING_MGRAPH_H
