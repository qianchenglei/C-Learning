//
// 邻接矩阵读表验收：用 AE 实机网络（19 点 / 24 条带权无向边）喂 CreateMGraph
// 验的是「同一份 RowGraph，矩阵跟链表说的是同一张图，且权值原样搬过来」
//
#include "MGraph.h"
#include "TestMGraph.h"
#include "TestHelper.h"
#include <assert.h>

/* 某一行里有几条边 = 该顶点的度（无向）/ 出度（有向） */
static int CountRowEdges(const MGraph *MG, int RowIdx) {
    int EdgeCount = 0;
    for (int ColIdx = 0; ColIdx < MG->IdCap; ColIdx++) {
        if (MG->Edge[RowIdx * MG->IdCap + ColIdx] != NOEDGE) { EdgeCount++; }
    }
    return EdgeCount;
}

void MGraphReadTableTest(void) {
    setbuf(stdout, NULL);

    /* AE 样本（19 点 / 24 边）定义在 TestHelper.c，两个测试共用 */

    MGraph MG;
    InitMGraph(&MG);
    CreateMGraph(&MG, &AESource, 0);   /* 0 = 无向 */

    /* ① 三个数先对 */
    assert(MG.IdCap == 19);
    assert(MG.VexNum == 19);
    assert(MG.EdgeNum == 24);
    printf("  [M] |V|=%d |E|=%d IdCap=%d\n", MG.VexNum, MG.EdgeNum, MG.IdCap);

    /* ② 顶点数据原样搬过来 */
    for (int Idx = 0; Idx < 19; Idx++) { assert(MG.Vex[Idx] == AEVexData[Idx]); }
    printf("  [M] V 表逐项一致 OK\n");

    /* ③ 每条边的权值两端对称，且等于原料里的 Weight */
    for (int EdgeIdx = 0; EdgeIdx < 24; EdgeIdx++) {
        int FromIdx  = AEEdgeList[EdgeIdx].U;
        int ToIdx    = AEEdgeList[EdgeIdx].V;
        int EdgeCost = AEEdgeList[EdgeIdx].Weight;
        assert(MG.Edge[FromIdx * MG.IdCap + ToIdx] == EdgeCost);
        assert(MG.Edge[ToIdx * MG.IdCap + FromIdx] == EdgeCost);
    }
    printf("  [M] 24 条边两端互指、权值对称 OK\n");

    /* ④ 全表非 NOEDGE 的格子 == 48 == 2|E|，且权值总和 == 2 x 81 */
    int EdgeSlotCount = 0;
    long WeightSum = 0;
    for (int SlotIdx = 0; SlotIdx < MG.IdCap * MG.IdCap; SlotIdx++) {
        if (MG.Edge[SlotIdx] != NOEDGE) {
            EdgeSlotCount++;
            WeightSum += MG.Edge[SlotIdx];
        }
    }
    assert(EdgeSlotCount == 48);
    assert(WeightSum == 162);          /* 无向图双向各存一次 -> 2 x 81 */
    printf("  [M] 非空格子 = %d = 2x24，权值总和 = %ld = 2x81 OK\n", EdgeSlotCount, WeightSum);

    /* ⑤ 无自环：对角线必须全是 NOEDGE */
    for (int Idx = 0; Idx < MG.IdCap; Idx++) { assert(MG.Edge[Idx * MG.IdCap + Idx] == NOEDGE); }
    printf("  [M] 对角线无自环 OK\n");

    /* ⑥ 几个关键顶点的度 */
    assert(CountRowEdges(&MG, 0) == 6);   /* v0 ME控制器：集散点 */
    assert(CountRowEdges(&MG, 5) == 5);   /* v5 物流接口 */
    assert(CountRowEdges(&MG, 8) == 1);   /* v8 数据库：悬挂点 */
    printf("  [M] 度验算 v0=6 / v5=5 / v8=1 OK\n");

    printf("mgraph-readtable OK: |V|=%d |E|=%d slots=%d weightsum=%ld\n",
           MG.VexNum, MG.EdgeNum, EdgeSlotCount, WeightSum);

    DestroyMGraph(&MG);
}
