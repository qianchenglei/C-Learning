//
// 矩阵版 Prim 验收：小图手算 + AE 实机网络 + 起点无关性 + 不连通图
//
#include "MGraph.h"
#include "TestPrim.h"
#include "TestHelper.h"
#include <assert.h>

void PrimSmallGraphTest(void) {
    setbuf(stdout, NULL);

    /* 4 个点、5 条边：
         0-1(1) 1-2(2) 2-3(3) 能连成一条链，总权 6
         0-3(4) 0-2(5) 是两条"更贵的近路"，会被跳过 */
    VertexType V[4] = {0, 1, 2, 3};
    Edge E[5] = {
        {0,1,1}, {1,2,2}, {2,3,3}, {0,3,4}, {0,2,5}
    };
    RowGraph RG = { V, E, 4, 5 };

    MGraph MG;
    InitMGraph(&MG);
    CreateMGraph(&MG, &RG, 0);

    long TotalCost = MST_MGraph_Prim(&MG, 0);

    assert(TotalCost == 6);              /* 1 + 2 + 3 */
    printf("  [P] 4 点小图：总权 = %ld（手算 1+2+3=6）OK\n", TotalCost);

    DestroyMGraph(&MG);
}

void PrimAEGraphTest(void) {
    setbuf(stdout, NULL);

    MGraph MG;
    InitMGraph(&MG);
    CreateMGraph(&MG, &AESource, 0);

    long TotalCost = MST_MGraph_Prim(&MG, 0);

    /* 19 点需要 18 条边；总权按权值分布累加：
       1x1 + 2x8 + 3x4 + 4x1 + 5x2 + 6x1 + 7x1 = 56 */
    assert(TotalCost == 56);
    printf("  [P] AE 19 点：总权 = %ld（预期 56）OK\n", TotalCost);

    DestroyMGraph(&MG);
}

void PrimStartIndependenceTest(void) {
    setbuf(stdout, NULL);

    MGraph MG;
    InitMGraph(&MG);
    CreateMGraph(&MG, &AESource, 0);

    /* MST 没有"原点"：换起点，总权必须一样 */
    long CostFromV0  = MST_MGraph_Prim(&MG, 0);
    long CostFromV9  = MST_MGraph_Prim(&MG, 9);
    long CostFromV18 = MST_MGraph_Prim(&MG, 18);

    assert(CostFromV0 == 56);
    assert(CostFromV9 == 56);
    assert(CostFromV18 == 56);
    printf("  [P] 起点无关：0 / 9 / 18 三个起点总权都是 56 OK\n");

    DestroyMGraph(&MG);
}

void PrimDisconnectedTest(void) {
    setbuf(stdout, NULL);

    /* 4 个点，但只有 0-1 和 2-3 两条边 —— 断成两片 */
    VertexType V[4] = {0, 1, 2, 3};
    Edge E[2] = {
        {0,1,1}, {2,3,1}
    };
    RowGraph RG = { V, E, 4, 2 };

    MGraph MG;
    InitMGraph(&MG);
    CreateMGraph(&MG, &RG, 0);

    long TotalCost = MST_MGraph_Prim(&MG, 0);

    /* 从 0 出发只能吃到 1，然后找不到 INF 以下的候选 -> break */
    assert(TotalCost == 1);
    printf("  [P] 不连通图：只吃到 0-1，总权 = %ld，未越界 OK\n", TotalCost);

    DestroyMGraph(&MG);
}
