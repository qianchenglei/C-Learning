//
// BFS 验收测试（跟 TestDfs 对称）
// 除了"访问到 + 不重复"，还验证一件事：**访问顺序必须按层**
//
#include "TestBfs.h"
#include "Graph.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXREC 64

static int g_order[MAXREC];
static int g_count;

static void RecordVisit(VertexNode *v) {
    if (g_count < MAXREC) { g_order[g_count] = v->Id; }
    g_count++;
}

static void PrintOrder(const char *tag) {
    printf("  [%s] 顺序:", tag);
    int shown = (g_count < MAXREC) ? g_count : MAXREC;
    for (int i = 0; i < shown; i++) { printf(" %d", g_order[i]); }
    printf("   (共 %d 个)\n", g_count);
}

/* 数量对 + 每个 ID 只出现一次 + 范围合法 */
static void CheckOrder(int expect) {
    assert(g_count == expect);

    bool seen[MAXREC];
    memset(seen, 0, sizeof seen);

    int shown = (g_count < MAXREC) ? g_count : MAXREC;
    for (int i = 0; i < shown; i++) {
        assert(g_order[i] >= 0 && g_order[i] < MAXREC);
        assert(!seen[g_order[i]]);
        seen[g_order[i]] = true;
    }
}

/* 在顺序数组里找某个 ID 第一次出现的位置，找不到返回 -1 */
static int PosOf(int id) {
    int shown = (g_count < MAXREC) ? g_count : MAXREC;
    for (int i = 0; i < shown; i++) {
        if (g_order[i] == id) { return i; }
    }
    return -1;
}

void BfsTest(void) {
    setbuf(stdout, NULL);

    /* ========== 用例 1：连通图（三角 + 尾巴） ========== */
    {
        VertexType V[4] = {10, 20, 30, 40};
        Edge       E[4] = {{0,1}, {0,2}, {1,2}, {2,3}};
        RowGraph   src  = {V, E, 4, 4};

        ALGraph G;
        InitALGraph(&G, 0);
        CreateALGraph(&G, &src, 0);
        assert(G.VexNum == 4);
        assert(G.EdgeNum == 4);

        g_count = 0;
        BFSTraverse(&G, RecordVisit);
        PrintOrder("BFS-1 连通");

        CheckOrder(4);
        printf("  [BFS-1] 4 个顶点全部访问且无重复 OK\n");

        /* 层序验证：0 是第 0 层，1、2 是第 1 层，3 是第 2 层 */
        assert(PosOf(0) == 0);          /* 起点必须第一个出来 */
        assert(PosOf(1) < PosOf(3));    /* 1 在第 1 层，必须排在 3 前面 */
        assert(PosOf(2) < PosOf(3));
        printf("  [BFS-1] 层序正确：0 → {1,2} → 3 OK\n");
    }

    /* ========== 用例 2：非连通图（两个独立分量） ========== */
    {
        VertexType V[4] = {10, 20, 30, 40};
        Edge       E[2] = {{0,1}, {2,3}};
        RowGraph   src  = {V, E, 4, 2};

        ALGraph G;
        InitALGraph(&G, 0);
        CreateALGraph(&G, &src, 0);
        assert(G.VexNum == 4);
        assert(G.EdgeNum == 2);

        g_count = 0;
        BFSTraverse(&G, RecordVisit);
        PrintOrder("BFS-2 非连通");

        CheckOrder(4);
        printf("  [BFS-2] 两个分量都覆盖 OK\n");
    }

    /* ========== 用例 3：单顶点孤立图 ========== */
    {
        VertexType V[1] = {10};
        RowGraph   src  = {V, NULL, 1, 0};

        ALGraph G;
        InitALGraph(&G, 0);
        CreateALGraph(&G, &src, 0);
        assert(G.VexNum == 1);
        assert(G.EdgeNum == 0);

        g_count = 0;
        BFSTraverse(&G, RecordVisit);
        PrintOrder("BFS-3 单点");

        CheckOrder(1);
        printf("  [BFS-3] 孤立顶点也访问 OK\n");
    }

    printf("bfs OK: 3 组用例全过\n");
}
