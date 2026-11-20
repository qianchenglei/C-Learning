//
// Created by 14266 on 2026/11/16.
//
/* 拓扑排序验收：拓扑序不唯一，所以核心断言是「偏序」而不是固定序列。
 * 唯一可以断言完整序列的是链式图 0→1→2→3，它只有一种解。 */
#include "ALGraph.h"
#include "TestTopo.h"
#include <assert.h>

static VertexNode *FindById(ALGraph *ALG, int id) {
    for (VertexNode *v = ALG->Head->NextVertex; v; v = v->NextVertex)
        if (v->Id == id) return v;
    return NULL;
}

static int OutDegreeOf(VertexNode *v) {
    int n = 0;
    for (EdgeNode *e = v->FirstEdge; e; e = e->NextEdge) n++;
    return n;
}

/* Pos[id] = 该顶点在 Order 里的下标；-1 表示压根没排出来 */
static void BuildPos(const int *Order, int n, int *Pos) {
    for (int i = 0; i < 8; i++) Pos[i] = -1;
    for (int i = 0; i < n; i++) Pos[Order[i]] = i;
}

/* 核心断言：每条边 u→v 都必须 u 在前、v 在后。
 * 这一条同时抓三类错：顺序排反、顶点漏排、环没检出（两个都没出现）。 */
static void AssertEdgeOrder(const Edge *E, int m, const int *Pos) {
    for (int k = 0; k < m; k++) {
        assert(Pos[E[k].U] >= 0 && Pos[E[k].V] >= 0);
        assert(Pos[E[k].U] < Pos[E[k].V]);
    }
}

/* 每个顶点必须出现且只出现一次 */
static void AssertFullCoverage(const int *Order, int n, const int *Pos, int VexNum) {
    for (int i = 0; i < VexNum; i++) assert(Pos[i] >= 0);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            assert(Order[i] != Order[j]);
}

/* 菱形 DAG：0→1, 0→2, 1→3, 2→3
 * 中间两个谁先出队不确定，但 0 必须第一、3 必须最后 —— 这两条是确定的。 */
void TopoDagTest(void) {
    setbuf(stdout, NULL);

    VertexType V[4] = {10, 20, 30, 40};
    Edge       E[4] = {{0,1},{0,2},{1,3},{2,3}};
    RowGraph   src  = { V, E, 4, 4 };

    ALGraph ALG;
    InitALGraph(&ALG, 1);
    CreateALGraph(&ALG, &src, 1);

    int Order[4] = {-1, -1, -1, -1};
    assert(TopoSort(&ALG, Order));        /* 无环必须返回 true */

    int Pos[8];
    BuildPos(Order, 4, Pos);
    AssertFullCoverage(Order, 4, Pos, 4);
    AssertEdgeOrder(E, 4, Pos);

    assert(Order[0] == 0);              /* 入度 0 且唯一，只能是它先出 */
    assert(Order[3] == 3);              /* 入度 2 且无出边，只能垫底 */

    printf("  [T] 菱形 DAG 偏序正确：%d %d %d %d\n",
           Order[0], Order[1], Order[2], Order[3]);
}

/* 多源：0→2, 1→2。入度为 0 的有两个。
 * 这一条专门验「扫一遍，把所有入度为 0 的都入队」——
 * 如果只放一个源点进去，另一个分支会整个丢掉，count 就凑不满。 */
void TopoMultiSourceTest(void) {
    setbuf(stdout, NULL);

    VertexType V[3] = {10, 20, 30};
    Edge       E[2] = {{0,2},{1,2}};
    RowGraph   src  = { V, E, 3, 2 };

    ALGraph ALG;
    InitALGraph(&ALG, 1);
    CreateALGraph(&ALG, &src, 1);

    int Order[3] = {-1, -1, -1};
    assert(TopoSort(&ALG, Order));

    int Pos[8];
    BuildPos(Order, 3, Pos);
    AssertFullCoverage(Order, 3, Pos, 3);
    AssertEdgeOrder(E, 2, Pos);
    assert(Order[2] == 2);              /* 两个源点都办完，2 才轮到 */

    printf("  [T] 多源偏序正确：%d %d %d\n", Order[0], Order[1], Order[2]);
}

/* 链式 0→1→2→3：唯一拓扑序，可以断言完整序列 */
void TopoChainTest(void) {
    setbuf(stdout, NULL);

    VertexType V[4] = {10, 20, 30, 40};
    Edge       E[3] = {{0,1},{1,2},{2,3}};
    RowGraph   src  = { V, E, 4, 3 };

    ALGraph ALG;
    InitALGraph(&ALG, 1);
    CreateALGraph(&ALG, &src, 1);

    int Order[4] = {-1, -1, -1, -1};
    assert(TopoSort(&ALG, Order));
    assert(Order[0] == 0 && Order[1] == 1 && Order[2] == 2 && Order[3] == 3);

    printf("  [T] 链式唯一序：%d %d %d %d\n",
           Order[0], Order[1], Order[2], Order[3]);
}

/* 三节点环 0→1→2→0：入度全是 1，初始队列是空的，
 * 一个顶点都出不来，Order 一个字节都不该被写。 */
void TopoCycleTest(void) {
    setbuf(stdout, NULL);

    VertexType V[3] = {10, 20, 30};
    Edge       E[3] = {{0,1},{1,2},{2,0}};
    RowGraph   src  = { V, E, 3, 3 };

    ALGraph ALG;
    InitALGraph(&ALG, 1);
    CreateALGraph(&ALG, &src, 1);

    int Order[3] = {-1, -1, -1};
    bool ok = TopoSort(&ALG, Order);

    assert(!ok);                        /* ← 判环的核心断言 */
    assert(Order[0] == -1 && Order[1] == -1 && Order[2] == -1);

    printf("  [T] 三节点环被检出，Order 未被写入 OK\n");
}

/* 图只读：跑完之后边数、出度全都不许变。
 * InDegree 是函数内的临时数组，不能残留在图里 ——
 * 所以同一张图连跑两次，结果必须一模一样。 */
void TopoReadOnlyTest(void) {
    setbuf(stdout, NULL);

    VertexType V[4] = {10, 20, 30, 40};
    Edge       E[4] = {{0,1},{0,2},{1,3},{2,3}};
    RowGraph   src  = { V, E, 4, 4 };

    ALGraph ALG;
    InitALGraph(&ALG, 1);
    CreateALGraph(&ALG, &src, 1);

    int degBefore[4];
    for (int i = 0; i < 4; i++) degBefore[i] = OutDegreeOf(FindById(&ALG, i));

    int O1[4] = {-1, -1, -1, -1};
    int O2[4] = {-1, -1, -1, -1};
    assert(TopoSort(&ALG, O1));
    assert(TopoSort(&ALG, O2));          /* 第二次不能被第一次污染 */

    assert(ALG.VexNum == 4 && ALG.EdgeNum == 4);
    for (int i = 0; i < 4; i++) {
        assert(OutDegreeOf(FindById(&ALG, i)) == degBefore[i]);
        assert(O1[i] == O2[i]);
    }

    printf("  [T] 图未被修改，两次调用结果一致 OK\n");
}
