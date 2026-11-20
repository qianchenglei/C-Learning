//
// Created by 14266 on 2026/11/20.
//
#include  "MGraph.h"

void InitMGraph(MGraph *MG) {
    MG->VexNum=0;
    MG->EdgeNum=0;
    MG->Vex = NULL;
    MG->Edge = NULL;
    MG->IdCap = 0;
    MG->Directed=-1;
}

void CreateMGraph(MGraph *MG,const RowGraph *RG,int Directed) {
    MG->Directed = Directed;
    MG->IdCap = RG->VexNum;
    MG->Vex = (VertexType*)malloc(sizeof(VertexType)*MG->IdCap);
    memset(MG->Vex,NOVEX,sizeof(VertexType)*MG->IdCap);
    MG->Edge = (EdgeType*)malloc(sizeof(EdgeType)*(MG->IdCap*MG->IdCap));
    for(int i=0;i<MG->IdCap;i++) {
        MG->Vex[i] = RG->VFrom[i];
        MG->VexNum++;
    }
    for(int i=0;i<MG->IdCap*MG->IdCap;i++) {
        MG->Edge[i] = NOEDGE;
    }
    for(int i=0;i<RG->EdgeNum;i++) {

        int FromIdx,ToIdx;
        FromIdx=RG->EFrom[i].U;
        ToIdx=RG->EFrom[i].V;
        MG->Edge[(FromIdx*MG->IdCap)+ToIdx] = 1;
        if (!MG->Directed) {
            MG->Edge[(ToIdx*MG->IdCap)+FromIdx] = 1;
        }
        MG->EdgeNum++;
    }
}

