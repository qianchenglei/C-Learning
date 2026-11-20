//
// 邻接矩阵读表验收：用 AE 实机网络（19 点 / 24 条无向边）喂 CreateMGraph
// 验的是「同一份 RowGraph，矩阵跟链表说的是同一张图」
//
#include "MGraph.h"
#include "TestMGraph.h"
#include "TestHelper.h"
#include <assert.h>

/* 某一行里有几个 1 = 该顶点的度（无向）/ 出度（有向） */
static int CountRowOnes(const MGraph *MG, int RowIdx) {
    int OneCount = 0;
    for (int ColIdx = 0; ColIdx < MG->IdCap; ColIdx++) {
        if (MG->Edge[RowIdx * MG->IdCap + ColIdx] == 1) { OneCount++; }
    }
    return OneCount;
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

    /* ③ 每条边两端都有 1（无向对称） */
    for (int EdgeIdx = 0; EdgeIdx < 24; EdgeIdx++) {
        int FromIdx = AEEdgeList[EdgeIdx].U;
        int ToIdx   = AEEdgeList[EdgeIdx].V;
        assert(MG.Edge[FromIdx * MG.IdCap + ToIdx] == 1);
        assert(MG.Edge[ToIdx * MG.IdCap + FromIdx] == 1);
    }
    printf("  [M] 24 条边两端互指、对称 OK\n");

    /* ④ 全表 1 的个数 == 48 == 2|E| */
    int OneCount = 0;
    for (int SlotIdx = 0; SlotIdx < MG.IdCap * MG.IdCap; SlotIdx++) {
        if (MG.Edge[SlotIdx] == 1) { OneCount++; }
    }
    assert(OneCount == 48);
    printf("  [M] 全表 1 的个数 = %d = 2x24 OK\n", OneCount);

    /* ⑤ 无自环：对角线没有 1 */
    for (int Idx = 0; Idx < MG.IdCap; Idx++) { assert(MG.Edge[Idx * MG.IdCap + Idx] != 1); }
    printf("  [M] 对角线无自环 OK\n");

    /* ⑥ 几个关键顶点的度 */
    assert(CountRowOnes(&MG, 0) == 6);   /* v0 ME控制器：集散点 */
    assert(CountRowOnes(&MG, 5) == 5);   /* v5 物流接口 */
    assert(CountRowOnes(&MG, 8) == 1);   /* v8 数据库：悬挂点 */
    printf("  [M] 度验算 v0=6 / v5=5 / v8=1 OK\n");

    printf("mgraph-readtable OK: |V|=%d |E|=%d ones=%d\n", MG.VexNum, MG.EdgeNum, OneCount);
}
