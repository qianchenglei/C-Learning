//
// DFS 验收测试
// 遍历只负责「访问了谁」，输出交给回调 —— 测试用回调记录顺序，
// 不再靠重定向 stdout，算法函数里也不需要 printf。
//
#include "TestDfs.h"
#include "Graph.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXREC 64

static int g_order[MAXREC];
static int g_count;

/* 访问者：只记录，不打印 */
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

/* 数量对 + 每个 ID 只出现一次 + ID 在合法范围 */
static void CheckOrder(int expect) {
    assert(g_count == expect);

    bool seen[MAXREC];
    memset(seen, 0, sizeof seen);

    int shown = (g_count < MAXREC) ? g_count : MAXREC;
    for (int i = 0; i < shown; i++) {
        assert(g_order[i] >= 0 && g_order[i] < MAXREC);
        assert(!seen[g_order[i]]);      /* 同一个顶点不能被访问两次 */
        seen[g_order[i]] = true;
    }
}

void DfsTest(void) {
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
        DFSTraverse(&G, RecordVisit);
        PrintOrder("DFS-1 连通");

        CheckOrder(4);
        printf("  [DFS-1] 4 个顶点全部访问且无重复 OK\n");
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
        DFSTraverse(&G, RecordVisit);
        PrintOrder("DFS-2 非连通");

        CheckOrder(4);
        printf("  [DFS-2] 两个分量都覆盖 OK\n");
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
        DFSTraverse(&G, RecordVisit);
        PrintOrder("DFS-3 单点");

        CheckOrder(1);
        printf("  [DFS-3] 孤立顶点也访问 OK\n");
    }

    printf("dfs OK: 3 组用例全过\n");
}
