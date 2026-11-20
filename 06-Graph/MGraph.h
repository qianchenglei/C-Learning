//
// Created by 14266 on 2026/11/20.
//

#ifndef C_LEARNING_MGRAPH_H
#define C_LEARNING_MGRAPH_H
#include<stdio.h>
#include<stdlib.h>
#include "GraphTypes.h"

typedef int MGraphDataType;
typedef int EdgeType;
#define NOVEX (-1)
typedef struct MGraph {
    MGraphDataType *Ver;
    EdgeType *Edge;
    int IdCap;//矩阵边长=MaxId+1
    int VexNum;
    int EdgeNum;
}MGraph;

void InitMGraph(MGraph *MG);
void CreateMGraph(MGraph *MG,RowGraph );
#endif //C_LEARNING_MGRAPH_H
