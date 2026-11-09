//
// Created by 14266 on 2026/11/10.
//
#include "Graph.h"
#include "TestThing.h"
#include <assert.h>

static VertexNode *FindById(ALGraph *G, int id) {
    for (VertexNode *v = G->Head->NextVertex; v; v = v->NextVertex)
        if (v->Id == id) return v;
    return NULL;
}
static int DegreeOf(VertexNode *v) {
    int n = 0;
    for (EdgeNode *e = v->FirstEdge; e; e = e->NextEdge) n++;
    return n;
}
static bool LinkedTo(VertexNode *a, VertexNode *b) {
    for (EdgeNode *e = a->FirstEdge; e; e = e->NextEdge)
        if (e->ToVertex == b) return true;   /* 指针直接比 */
    return false;
}

void SmokeTest(void) {
    VertexType V[4] = {1000, 2000, 3000, 4000};
    Edge       E[4] = {{0,1},{0,2},{1,2},{2,3}};   /* 三角 + 尾巴 */
    RowGraph   src  = { V, E, 4, 4 };

    ALGraph G;
    InitALGraph(&G);

    /* ① 空图 / dummy */
    assert(G.Head && G.Head->Id == -1 && G.Head->NextVertex == NULL);
    assert(G.VexNum == 0 && G.EdgeNum == 0);

    CreateALGraph(&G, &src);

    /* ② 计数 */
    assert(G.VexNum == 4 && G.EdgeNum == 4);

    /* ③ 顶点链正序 + 数据对得上 V 表 */
    int n = 0;
    for (VertexNode *v = G.Head->NextVertex; v; v = v->NextVertex) {
        assert(v->Id == n);
        assert(v->VexData == V[n]);
        n++;
    }
    assert(n == 4);

    /* ④ 度数 2 / 2 / 3 / 1，v3 是悬挂点 */
    assert(DegreeOf(FindById(&G,0)) == 2);
    assert(DegreeOf(FindById(&G,1)) == 2);
    assert(DegreeOf(FindById(&G,2)) == 3);
    assert(DegreeOf(FindById(&G,3)) == 1);

    /* ⑤ ∑链长 == 2|E| */
    int sum = 0;
    for (VertexNode *v = G.Head->NextVertex; v; v = v->NextVertex)
        sum += DegreeOf(v);
    assert(sum == 2 * G.EdgeNum);

    /* ⑥ 每条边两端互指 */
    for (int k = 0; k < src.EdgeNum; k++) {
        VertexNode *a = FindById(&G, E[k].U), *b = FindById(&G, E[k].V);
        assert(a && b);
        assert(LinkedTo(a, b) && LinkedTo(b, a));
    }

    /* ⑦ 顺着 ToVertex 走得通：0 → 2 → 3 */
    assert(LinkedTo(FindById(&G,0), FindById(&G,2)));
    assert(LinkedTo(FindById(&G,2), FindById(&G,3)));

    printf("smoke OK: |V|=%d |E|=%d sum(deg)=%d\n", G.VexNum, G.EdgeNum, sum);
}