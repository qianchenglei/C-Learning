//
// Created by 14266 on 2026/11/16.
//
/* 有向图验收：核心只有一条 —— u→v 成立时，v→u 不该跟着存在。
 * 无向图那套断言（∑度 = 2|E|、两端互指）在有向图上全部失效，不能照搬。 */
#include "ALGraph.h"
#include "TestDirected.h"
#include <assert.h>

static VertexNode *FindById(ALGraph *ALG, int id) {
    for (VertexNode *v = ALG->Head->NextVertex; v; v = v->NextVertex)
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
static int InDegree(ALGraph *ALG, VertexNode *Target) {
    int n = 0;
    for (VertexNode *v = ALG->Head->NextVertex; v; v = v->NextVertex)
        for (EdgeNode *e = v->FirstEdge; e; e = e->NextEdge)
            if (e->ToVertex == Target) n++;
    return n;
}

static bool LinkedTo(VertexNode *a, VertexNode *b) {
    for (EdgeNode *e = a->FirstEdge; e; e = e->NextEdge)
        if (e->ToVertex == b) return true;
    return false;
}

static int SumOutDegree(ALGraph *ALG) {
    int sum = 0;
    for (VertexNode *v = ALG->Head->NextVertex; v; v = v->NextVertex) sum += OutDegree(v);
    return sum;
}

/* 建图：菱形 DAG  0→1, 0→2, 1→3, 2→3
 * 无向时它有 8 个 EdgeNode，有向时只有 4 个 —— 后半句是全部意义所在。 */
void DirectedCreateTest(void) {
    setbuf(stdout, NULL);

    VertexType V[4] = {10, 20, 30, 40};
    Edge       E[4] = {{0,1},{0,2},{1,3},{2,3}};
    RowGraph   src  = { V, E, 4, 4 };

    ALGraph ALG;
    InitALGraph(&ALG, 1);
    CreateALGraph(&ALG, &src, 1);

    /* ① 标记位与账本 */
    assert(ALG.Directed == 1);
    assert(ALG.VexNum == 4 && ALG.EdgeNum == 4);

    VertexNode *v0 = FindById(&ALG,0), *v1 = FindById(&ALG,1);
    VertexNode *v2 = FindById(&ALG,2), *v3 = FindById(&ALG,3);
    assert(v0 && v1 && v2 && v3);

    /* ② 出度 2 / 1 / 1 / 0，∑出度 == |E|（不是 2|E|） */
    assert(OutDegree(v0) == 2);
    assert(OutDegree(v1) == 1);
    assert(OutDegree(v2) == 1);
    assert(OutDegree(v3) == 0);
    assert(SumOutDegree(&ALG) == ALG.EdgeNum);

    /* ③ 入度 0 / 1 / 1 / 2，∑入度同样 == |E| */
    assert(InDegree(&ALG, v0) == 0);
    assert(InDegree(&ALG, v1) == 1);
    assert(InDegree(&ALG, v2) == 1);
    assert(InDegree(&ALG, v3) == 2);

    /* ④ 每条边只许单向存在 */
    for (int k = 0; k < src.EdgeNum; k++) {
        VertexNode *a = FindById(&ALG, E[k].U);
        VertexNode *b = FindById(&ALG, E[k].V);
        assert(a && b);
        assert(LinkedTo(a, b));
        assert(!LinkedTo(b, a));       /* ← 有向图的关键断言 */
    }

    printf("directed create OK: |V|=%d |E|=%d sum(outdeg)=%d\n",
           ALG.VexNum, ALG.EdgeNum, SumOutDegree(&ALG));
}

/* 增删：有向图里「反向」是另一条边，不是同一条 */
void DirectedCrudTest(void) {
    setbuf(stdout, NULL);

    VertexType V[4] = {10, 20, 30, 40};
    Edge       E[4] = {{0,1},{0,2},{1,3},{2,3}};
    RowGraph   src  = { V, E, 4, 4 };

    ALGraph ALG;
    InitALGraph(&ALG, 1);
    CreateALGraph(&ALG, &src, 1);

    VertexNode *v0 = FindById(&ALG,0), *v1 = FindById(&ALG,1);
    VertexNode *v2 = FindById(&ALG,2), *v3 = FindById(&ALG,3);
    int edges = ALG.EdgeNum;

    /* ⑤ 插 3→0：只加一条，v0 的出度不该动 */
    InsertALGraphEdge(&ALG, v3, v0);
    assert(ALG.EdgeNum == edges + 1);
    assert(OutDegree(v3) == 1);
    assert(OutDegree(v0) == 2);        /* 仍是 0→1, 0→2 */
    assert(LinkedTo(v3, v0));
    assert(!LinkedTo(v0, v3));         /* 反边不能顺手插出来 */
    assert(InDegree(&ALG, v0) == 1);
    printf("  [C] 有向插入只加一条边 OK\n");

    /* ⑥ 重复插同一条：拒 */
    InsertALGraphEdge(&ALG, v3, v0);
    assert(ALG.EdgeNum == edges + 1);
    assert(OutDegree(v3) == 1);
    printf("  [C] 重复插入被拒 OK\n");

    /* ⑦ 反向不是重复：0→3 是另一条边，必须插得进去 */
    InsertALGraphEdge(&ALG, v0, v3);
    assert(ALG.EdgeNum == edges + 2);
    assert(LinkedTo(v0, v3) && LinkedTo(v3, v0));
    assert(OutDegree(v0) == 3 && OutDegree(v3) == 1);
    printf("  [C] 反向边算两条边 OK\n");

    /* ⑧ 删 0→3：只摘这一条，3→0 必须留着 */
    DeleteALGraphEdge(&ALG, v0, v3);
    assert(ALG.EdgeNum == edges + 1);
    assert(!LinkedTo(v0, v3));
    assert(LinkedTo(v3, v0));          /* ← 有向图删除的关键断言 */
    assert(OutDegree(v0) == 2);
    assert(InDegree(&ALG, v3) == 2);     /* 1→3, 2→3 */
    printf("  [D] 有向删除不牵连反向边 OK\n");

    /* ⑨ 删不存在的边：账本和结构都不许动 */
    int edgeBefore = ALG.EdgeNum, sumBefore = SumOutDegree(&ALG);
    DeleteALGraphEdge(&ALG, v1, v0);     /* 1→0 从来没有过 */
    assert(ALG.EdgeNum == edgeBefore);
    assert(SumOutDegree(&ALG) == sumBefore);
    assert(LinkedTo(v3, v0));
    printf("  [D] 删除不存在的边是 no-op OK\n");

    /* ⑩ 删回纯 DAG，入度回到 0/1/1/2 */
    DeleteALGraphEdge(&ALG, v3, v0);
    assert(ALG.EdgeNum == edges);
    assert(OutDegree(v3) == 0);
    assert(InDegree(&ALG, v0) == 0);
    assert(InDegree(&ALG, v3) == 2);
    printf("directed crud OK: |V|=%d |E|=%d\n", ALG.VexNum, ALG.EdgeNum);
}
