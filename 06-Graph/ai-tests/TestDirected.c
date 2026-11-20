//
// Created by 14266 on 2026/11/16.
//
/* 有向图验收：核心只有一条 —— u→v 成立时，v→u 不该跟着存在。
 * 无向图那套断言（∑度 = 2|E|、两端互指）在有向图上全部失效，不能照搬。 */
#include "Graph.h"
#include "TestDirected.h"
#include <assert.h>

static VertexNode *FindById(ALGraph *G, int id) {
    for (VertexNode *v = G->Head->NextVertex; v; v = v->NextVertex)
        if (v->Id == id) return v;
    return NULL;
}

static int OutDegree(VertexNode *v) {
    int n = 0;
    for (EdgeNode *e = v->FirstEdge; e; e = e->NextEdge) n++;
    return n;
}

/* 入度扫不了单点：指向 Target 的边散在别人链上，只能全图跑一遍。
 * 这和拓扑排序里算入度是同一套动作，先在这儿写熟。 */
static int InDegree(ALGraph *G, VertexNode *Target) {
    int n = 0;
    for (VertexNode *v = G->Head->NextVertex; v; v = v->NextVertex)
        for (EdgeNode *e = v->FirstEdge; e; e = e->NextEdge)
            if (e->ToVertex == Target) n++;
    return n;
}

static bool LinkedTo(VertexNode *a, VertexNode *b) {
    for (EdgeNode *e = a->FirstEdge; e; e = e->NextEdge)
        if (e->ToVertex == b) return true;
    return false;
}

static int SumOutDegree(ALGraph *G) {
    int sum = 0;
    for (VertexNode *v = G->Head->NextVertex; v; v = v->NextVertex) sum += OutDegree(v);
    return sum;
}

/* 建图：菱形 DAG  0→1, 0→2, 1→3, 2→3
 * 无向时它有 8 个 EdgeNode，有向时只有 4 个 —— 后半句是全部意义所在。 */
void DirectedCreateTest(void) {
    setbuf(stdout, NULL);

    VertexType V[4] = {10, 20, 30, 40};
    Edge       E[4] = {{0,1},{0,2},{1,3},{2,3}};
    RowGraph   src  = { V, E, 4, 4 };

    ALGraph G;
    InitALGraph(&G, 1);
    CreateALGraph(&G, &src, 1);

    /* ① 标记位与账本 */
    assert(G.Directed == 1);
    assert(G.VexNum == 4 && G.EdgeNum == 4);

    VertexNode *v0 = FindById(&G,0), *v1 = FindById(&G,1);
    VertexNode *v2 = FindById(&G,2), *v3 = FindById(&G,3);
    assert(v0 && v1 && v2 && v3);

    /* ② 出度 2 / 1 / 1 / 0，∑出度 == |E|（不是 2|E|） */
    assert(OutDegree(v0) == 2);
    assert(OutDegree(v1) == 1);
    assert(OutDegree(v2) == 1);
    assert(OutDegree(v3) == 0);
    assert(SumOutDegree(&G) == G.EdgeNum);

    /* ③ 入度 0 / 1 / 1 / 2，∑入度同样 == |E| */
    assert(InDegree(&G, v0) == 0);
    assert(InDegree(&G, v1) == 1);
    assert(InDegree(&G, v2) == 1);
    assert(InDegree(&G, v3) == 2);

    /* ④ 每条边只许单向存在 */
    for (int k = 0; k < src.EdgeNum; k++) {
        VertexNode *a = FindById(&G, E[k].U);
        VertexNode *b = FindById(&G, E[k].V);
        assert(a && b);
        assert(LinkedTo(a, b));
        assert(!LinkedTo(b, a));       /* ← 有向图的关键断言 */
    }

    printf("directed create OK: |V|=%d |E|=%d sum(outdeg)=%d\n",
           G.VexNum, G.EdgeNum, SumOutDegree(&G));
}

/* 增删：有向图里「反向」是另一条边，不是同一条 */
void DirectedCrudTest(void) {
    setbuf(stdout, NULL);

    VertexType V[4] = {10, 20, 30, 40};
    Edge       E[4] = {{0,1},{0,2},{1,3},{2,3}};
    RowGraph   src  = { V, E, 4, 4 };

    ALGraph G;
    InitALGraph(&G, 1);
    CreateALGraph(&G, &src, 1);

    VertexNode *v0 = FindById(&G,0), *v1 = FindById(&G,1);
    VertexNode *v2 = FindById(&G,2), *v3 = FindById(&G,3);
    int edges = G.EdgeNum;

    /* ⑤ 插 3→0：只加一条，v0 的出度不该动 */
    InsertALGraphEdge(&G, v3, v0);
    assert(G.EdgeNum == edges + 1);
    assert(OutDegree(v3) == 1);
    assert(OutDegree(v0) == 2);        /* 仍是 0→1, 0→2 */
    assert(LinkedTo(v3, v0));
    assert(!LinkedTo(v0, v3));         /* 反边不能顺手插出来 */
    assert(InDegree(&G, v0) == 1);
    printf("  [C] 有向插入只加一条边 OK\n");

    /* ⑥ 重复插同一条：拒 */
    InsertALGraphEdge(&G, v3, v0);
    assert(G.EdgeNum == edges + 1);
    assert(OutDegree(v3) == 1);
    printf("  [C] 重复插入被拒 OK\n");

    /* ⑦ 反向不是重复：0→3 是另一条边，必须插得进去 */
    InsertALGraphEdge(&G, v0, v3);
    assert(G.EdgeNum == edges + 2);
    assert(LinkedTo(v0, v3) && LinkedTo(v3, v0));
    assert(OutDegree(v0) == 3 && OutDegree(v3) == 1);
    printf("  [C] 反向边算两条边 OK\n");

    /* ⑧ 删 0→3：只摘这一条，3→0 必须留着 */
    DeleteALGraphEdge(&G, v0, v3);
    assert(G.EdgeNum == edges + 1);
    assert(!LinkedTo(v0, v3));
    assert(LinkedTo(v3, v0));          /* ← 有向图删除的关键断言 */
    assert(OutDegree(v0) == 2);
    assert(InDegree(&G, v3) == 2);     /* 1→3, 2→3 */
    printf("  [D] 有向删除不牵连反向边 OK\n");

    /* ⑨ 删不存在的边：账本和结构都不许动 */
    int edgeBefore = G.EdgeNum, sumBefore = SumOutDegree(&G);
    DeleteALGraphEdge(&G, v1, v0);     /* 1→0 从来没有过 */
    assert(G.EdgeNum == edgeBefore);
    assert(SumOutDegree(&G) == sumBefore);
    assert(LinkedTo(v3, v0));
    printf("  [D] 删除不存在的边是 no-op OK\n");

    /* ⑩ 删回纯 DAG，入度回到 0/1/1/2 */
    DeleteALGraphEdge(&G, v3, v0);
    assert(G.EdgeNum == edges);
    assert(OutDegree(v3) == 0);
    assert(InDegree(&G, v0) == 0);
    assert(InDegree(&G, v3) == 2);
    printf("directed crud OK: |V|=%d |E|=%d\n", G.VexNum, G.EdgeNum);
}
