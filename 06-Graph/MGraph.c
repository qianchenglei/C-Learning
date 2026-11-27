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
/* 把邻接矩阵里的边导成 Edge 数组，返回边的条数（供 Kruskal 用） */
static int CollectEdgesFromMGraph(const MGraph *MG, Edge *EdgeOut, int EdgeOutCapacity)
{
    int EdgeCount = 0;

    for (int RowIdx = 0; RowIdx < MG->IdCap; RowIdx++) {
        if (MG->Vex[RowIdx] == NOVEX) continue;        /* 空位顶点，跳过 */

        for (int ColIdx = 0; ColIdx < MG->IdCap; ColIdx++) {
            if (MG->Vex[ColIdx] == NOVEX) continue;    /* 空位顶点，跳过 */

            EdgeType EdgeWeight = MG->Edge[RowIdx * MG->IdCap + ColIdx];
            if (EdgeWeight == NOEDGE) continue;        /* 没有这条边 */

            /* 无向图：只取上三角，否则每条边会被读两遍 */
            if (!MG->Directed && ColIdx <= RowIdx) continue;

            if (EdgeCount >= EdgeOutCapacity) return EdgeCount;

            EdgeOut[EdgeCount].U      = RowIdx;
            EdgeOut[EdgeCount].V      = ColIdx;
            EdgeOut[EdgeCount].Weight = EdgeWeight;
            EdgeCount++;
        }
    }
    return EdgeCount;
}
static int CompareEdgeByWeight(const void *APrt, const void *BPrt) {
    const Edge *A = (const Edge *)APrt;
    const Edge *B = (const Edge *)BPrt;
    if (A->Weight < B->Weight) return -1;
    if (A->Weight > B->Weight) return 1;
    return 0;
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

long MST_MGraph_Kruskal(MGraph *MG) {
    if (MG == NULL || MG->IdCap <= 0) return -1;
    int EdgeCapacity=MG->IdCap*MG->IdCap;
    Edge *EFrom = (Edge*)malloc(sizeof(Edge)*EdgeCapacity);
    if (EFrom == NULL) return -1;
    int EdgeCount = CollectEdgesFromMGraph(MG,EFrom,EdgeCapacity);
    qsort(EFrom,EdgeCount,sizeof(Edge),CompareEdgeByWeight);
    UFDSet UFDS;
    UFDSInit(&UFDS,MG->IdCap);
    long TotalCost = 0;
    int PackedCount = 0;
    int NeedCount = MG->VexNum-1;
    for(int EdgeIdx = 0; EdgeIdx < EdgeCount&&PackedCount<NeedCount; EdgeIdx++) {
       if ( UFDSUnion(&UFDS,EFrom[EdgeIdx].U,EFrom[EdgeIdx].V)) {
           TotalCost += EFrom[EdgeIdx].Weight;
           PackedCount++;
           printf("  边 %d - %d   权 %d\n", EFrom[EdgeIdx].U, EFrom[EdgeIdx].V, EFrom[EdgeIdx].Weight);

       }
    }
    free(EFrom);
    UFDSDestroy(&UFDS);
    if (PackedCount != NeedCount) return -1;
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

