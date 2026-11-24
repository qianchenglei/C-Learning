//
// Created by 14266 on 2026/11/16.
//
/* 有向图验收：核心只有一条 —— u→v 成立时，v→u 不该跟着存在。
 * 无向图那套断言（∑度 = 2|E|、两端互指）在有向图上全部失效，不能照搬。 */
#include "ALGraph.h"
#include "TestDirected.h"
#include "TestHelper.h"
#include <assert.h>

/* 公用小工具已抽到 TestHelper.h：
 *   FindVertexById / VertexDegree / VertexLinkedTo / GraphSumDegree / GraphInDegree */

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

    VertexNode *v0 = FindVertexById(&ALG,0), *v1 = FindVertexById(&ALG,1);
    VertexNode *v2 = FindVertexById(&ALG,2), *v3 = FindVertexById(&ALG,3);
    assert(v0 && v1 && v2 && v3);

    /* ② 出度 2 / 1 / 1 / 0，∑出度 == |E|（不是 2|E|） */
    assert(VertexDegree(v0) == 2);
    assert(VertexDegree(v1) == 1);
    assert(VertexDegree(v2) == 1);
    assert(VertexDegree(v3) == 0);
    assert(GraphSumDegree(&ALG) == ALG.EdgeNum);

    /* ③ 入度 0 / 1 / 1 / 2，∑入度同样 == |E| */
    assert(GraphInDegree(&ALG, v0) == 0);
    assert(GraphInDegree(&ALG, v1) == 1);
    assert(GraphInDegree(&ALG, v2) == 1);
    assert(GraphInDegree(&ALG, v3) == 2);

    /* ④ 每条边只许单向存在 */
    for (int k = 0; k < src.EdgeNum; k++) {
        VertexNode *a = FindVertexById(&ALG, E[k].U);
        VertexNode *b = FindVertexById(&ALG, E[k].V);
        assert(a && b);
        assert(VertexLinkedTo(a, b));
        assert(!VertexLinkedTo(b, a));       /* ← 有向图的关键断言 */
    }

    printf("directed create OK: |V|=%d |E|=%d sum(outdeg)=%d\n",
           ALG.VexNum, ALG.EdgeNum, GraphSumDegree(&ALG));
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

    VertexNode *v0 = FindVertexById(&ALG,0), *v1 = FindVertexById(&ALG,1);
    VertexNode *v3 = FindVertexById(&ALG,3);
    int edges = ALG.EdgeNum;

    /* ⑤ 插 3→0：只加一条，v0 的出度不该动 */
    InsertALGraphEdge(&ALG, v3, v0);
    assert(ALG.EdgeNum == edges + 1);
    assert(VertexDegree(v3) == 1);
    assert(VertexDegree(v0) == 2);        /* 仍是 0→1, 0→2 */
    assert(VertexLinkedTo(v3, v0));
    assert(!VertexLinkedTo(v0, v3));         /* 反边不能顺手插出来 */
    assert(GraphInDegree(&ALG, v0) == 1);
    printf("  [C] 有向插入只加一条边 OK\n");

    /* ⑥ 重复插同一条：拒 */
    InsertALGraphEdge(&ALG, v3, v0);
    assert(ALG.EdgeNum == edges + 1);
    assert(VertexDegree(v3) == 1);
    printf("  [C] 重复插入被拒 OK\n");

    /* ⑦ 反向不是重复：0→3 是另一条边，必须插得进去 */
    InsertALGraphEdge(&ALG, v0, v3);
    assert(ALG.EdgeNum == edges + 2);
    assert(VertexLinkedTo(v0, v3) && VertexLinkedTo(v3, v0));
    assert(VertexDegree(v0) == 3 && VertexDegree(v3) == 1);
    printf("  [C] 反向边算两条边 OK\n");

    /* ⑧ 删 0→3：只摘这一条，3→0 必须留着 */
    DeleteALGraphEdge(&ALG, v0, v3);
    assert(ALG.EdgeNum == edges + 1);
    assert(!VertexLinkedTo(v0, v3));
    assert(VertexLinkedTo(v3, v0));          /* ← 有向图删除的关键断言 */
    assert(VertexDegree(v0) == 2);
    assert(GraphInDegree(&ALG, v3) == 2);     /* 1→3, 2→3 */
    printf("  [D] 有向删除不牵连反向边 OK\n");

    /* ⑨ 删不存在的边：账本和结构都不许动 */
    int edgeBefore = ALG.EdgeNum, sumBefore = GraphSumDegree(&ALG);
    DeleteALGraphEdge(&ALG, v1, v0);     /* 1→0 从来没有过 */
    assert(ALG.EdgeNum == edgeBefore);
    assert(GraphSumDegree(&ALG) == sumBefore);
    assert(VertexLinkedTo(v3, v0));
    printf("  [D] 删除不存在的边是 no-op OK\n");

    /* ⑩ 删回纯 DAG，入度回到 0/1/1/2 */
    DeleteALGraphEdge(&ALG, v3, v0);
    assert(ALG.EdgeNum == edges);
    assert(VertexDegree(v3) == 0);
    assert(GraphInDegree(&ALG, v0) == 0);
    assert(GraphInDegree(&ALG, v3) == 2);
    printf("directed crud OK: |V|=%d |E|=%d\n", ALG.VexNum, ALG.EdgeNum);
}
