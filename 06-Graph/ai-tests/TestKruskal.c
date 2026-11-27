//
// 矩阵版 Kruskal 验收：小图手算 + AE 实机网络 + 与 Prim 交叉验证 + 不连通图
//
#include "MGraph.h"
#include "TestKruskal.h"
#include "TestHelper.h"
#include <assert.h>

void KruskalSmallGraphTest(void) {
    setbuf(stdout, NULL);

    /* 和 Prim 用同一张图，方便两条结果并排看：
         0-1(1) 1-2(2) 2-3(3) 连成一条链，总权 6
         0-3(4) 0-2(5) 是两条更贵的近路，Kruskal 会先收前面 3 条、
         收够 n-1=3 条就停，根本轮不到它们 */
    VertexType V[4] = {0, 1, 2, 3};
    Edge E[5] = {
        {0,1,1}, {1,2,2}, {2,3,3}, {0,3,4}, {0,2,5}
    };
    RowGraph RG = { V, E, 4, 5 };

    MGraph MG;
    InitMGraph(&MG);
    CreateMGraph(&MG, &RG, 0);

    long TotalCost = MST_MGraph_Kruskal(&MG);

    assert(TotalCost == 6);              /* 1 + 2 + 3 */
    printf("  [K] 4 点小图：总权 = %ld（手算 1+2+3=6）OK\n", TotalCost);

    DestroyMGraph(&MG);
}

void KruskalAEGraphTest(void) {
    setbuf(stdout, NULL);

    MGraph MG;
    InitMGraph(&MG);
    CreateMGraph(&MG, &AESource, 0);

    long TotalCost = MST_MGraph_Kruskal(&MG);

    /* 19 点需要 18 条边；总权按权值分布累加：
       1x1 + 2x8 + 3x4 + 4x1 + 5x2 + 6x1 + 7x1 = 56 */
    assert(TotalCost == 56);
    printf("  [K] AE 19 点：总权 = %ld（预期 56）OK\n", TotalCost);

    DestroyMGraph(&MG);
}

void KruskalMatchesPrimTest(void) {
    setbuf(stdout, NULL);

    MGraph MG;
    InitMGraph(&MG);
    CreateMGraph(&MG, &AESource, 0);

    /* 最小生成树的权值是图的性质，跟用哪个算法无关。
       两条路算出来不一样，就说明其中一条的"取最小边"逻辑有问题
       —— 比如比较函数写成了降序（那样求出来的是最大生成树）。 */
    long KruskalCost = MST_MGraph_Kruskal(&MG);
    long PrimCost    = MST_MGraph_Prim(&MG, 0);

    assert(KruskalCost == PrimCost);
    printf("  [K] 与 Prim 交叉验证：Kruskal = %ld，Prim = %ld，一致 OK\n",
           KruskalCost, PrimCost);

    DestroyMGraph(&MG);
}

void KruskalDisconnectedTest(void) {
    setbuf(stdout, NULL);

    /* 4 个点，但只有 0-1 和 2-3 两条边 —— 断成两片，
       永远选不满 n-1=3 条边 */
    VertexType V[4] = {0, 1, 2, 3};
    Edge E[2] = {
        {0,1,1}, {2,3,1}
    };
    RowGraph RG = { V, E, 4, 2 };

    MGraph MG;
    InitMGraph(&MG);
    CreateMGraph(&MG, &RG, 0);

    long TotalCost = MST_MGraph_Kruskal(&MG);

    /* 不连通时返回 -1 是约定：不能返回"部分权值 2"，
       那样调用方会以为拿到了生成树 */
    assert(TotalCost == -1);
    printf("  [K] 不连通图：返回 %ld（约定 -1，不返回部分权值）OK\n", TotalCost);

    DestroyMGraph(&MG);
}
