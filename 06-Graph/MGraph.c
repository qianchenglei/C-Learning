//
// Created by 14266 on 2026/11/20.
//
#include  "MGraph.h"
static int FindVerInMG(MGraph *MG,VertexType ExpStartVer) {
    for(int i=0;i<MG->VexNum;i++) {
        if(MG->Vex[i] == ExpStartVer) {
            return i;
        }
    }
    return -1;
}
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
        int EdgeWeight = RG->EFrom[i].Weight;
        MG->Edge[(FromIdx*MG->IdCap)+ToIdx] = EdgeWeight;
        if (!MG->Directed) {
            MG->Edge[(ToIdx*MG->IdCap)+FromIdx] = EdgeWeight;
        }
        MG->EdgeNum++;
    }
}

void PrintMGraph(const MGraph *MG) {
    printf("-");
    for(int C=0;C<MG->IdCap;C++) {
        printf("%4d ",C);
    }
    printf("\n");
    for (int R=0; R<MG->IdCap; R++) {
        printf("%4d ",R);
        for(int C=0;C<MG->IdCap;C++) {
            int Weight = MG->Edge[R*MG->IdCap+C];
            if(Weight == NOEDGE) {
                printf("    -");
            }else {
                printf("%4d ", Weight);
            }
        }
        printf("\n");
    }
}

long MST_MGraph_Prim(MGraph *MG, VertexType ExpStartVer) {
    int Idx=FindVerInMG(MG,ExpStartVer);
    int *LowerCost = (int*)malloc(sizeof(int)*MG->IdCap);
    int *ParentVer= (int*)malloc(sizeof(int)*MG->IdCap);
    bool *Visited = (bool*)malloc(sizeof(bool)*MG->IdCap);
    memset(Visited,false,sizeof(bool)*MG->IdCap);
    for (int Col = 0; Col < MG->IdCap; Col++) {
        int Weight = MG->Edge[Idx*MG->IdCap+Col];
        LowerCost[Col] = (Weight==NOEDGE)?INF:Weight;
        ParentVer[Col] = (Weight==NOEDGE)?-1:Idx;
    }
    Visited[Idx] = true;
    LowerCost[Idx] = 0;
    ParentVer[Idx] = -1;
    long TotalCost = 0;
    int  EdgeCount = 0;
    for (int R = 0; R < MG->IdCap-1; R++) {
        int MinCost = INF,KIdx=-1;
        for (int Col = 0; Col < MG->IdCap; Col++) {
            if (!Visited[Col]&&LowerCost[Col]<MinCost) {
                MinCost = LowerCost[Col];
                KIdx = Col;
            }
        }
        if (KIdx == -1) {break;}
        Visited[KIdx] = true;
        TotalCost += MinCost;
        EdgeCount++;
        printf("  边 %2d - %2d   权 %2d\n", ParentVer[KIdx], KIdx, MinCost);
        for (int Col = 0; Col < MG->IdCap; Col++) {
            if (Visited[Col]) { continue; }
            int Weight = MG->Edge[KIdx * MG->IdCap + Col];
            if (Weight != NOEDGE && Weight < LowerCost[Col]) {
                LowerCost[Col]   = Weight;
                ParentVer[Col] = KIdx;
            }
        }
    }
    printf("  MST: %d 条边，总权 %ld\n", EdgeCount, TotalCost);
    free(LowerCost);
    free(ParentVer);
    free(Visited);
    return TotalCost;
}

void DestroyMGraph(MGraph *MG) {
    free(MG->Vex);
    free(MG->Edge);
    MG->Vex = NULL;
    MG->Edge = NULL;
    MG->IdCap = 0;
    MG->VexNum = 0;
    MG->EdgeNum = 0;
    MG->Directed = -1;
}

