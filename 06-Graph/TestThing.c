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

static int SumDegree(ALGraph *G) {
    int sum = 0;
    for (VertexNode *v = G->Head->NextVertex; v; v = v->NextVertex)
        sum += DegreeOf(v);
    return sum;
}

static VertexNode *TailVertex(ALGraph *G) {
    VertexNode *v = G->Head;
    while (v->NextVertex) v = v->NextVertex;
    return v;
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

/* 增量 CRUD 验收：一条边 = 两个 EdgeNode，计数只算逻辑边 */
void CrudSmokeTest(void) {
    setbuf(stdout, NULL);   /* 断言炸掉时也能看清跑到哪一组 */

    VertexType V[4] = {1000, 2000, 3000, 4000};
    Edge       E[4] = {{0,1},{0,2},{1,2},{2,3}};
    RowGraph   src  = { V, E, 4, 4 };

    ALGraph G;
    InitALGraph(&G);
    CreateALGraph(&G, &src);

    VertexNode *v0 = FindById(&G,0), *v1 = FindById(&G,1);
    VertexNode *v2 = FindById(&G,2), *v3 = FindById(&G,3);
    assert(v0 && v1 && v2 && v3);

    int edges = G.EdgeNum, sum = SumDegree(&G);
    int deg1 = DegreeOf(v1), deg3 = DegreeOf(v3);

    /* ⑧ 插一条新边：两点度数各 +1、∑链长 +2、双向互指 */
    InsertALGraphEdge(&G, v1, v3);
    assert(G.EdgeNum == edges + 1);
    assert(DegreeOf(v1) == deg1 + 1 && DegreeOf(v3) == deg3 + 1);
    assert(SumDegree(&G) == sum + 2);
    assert(LinkedTo(v1,v3) && LinkedTo(v3,v1));
    printf("  [C] insert (1,3) OK\n");

    /* ⑨ 判重：重复插全不变 */
    InsertALGraphEdge(&G, v1, v3);
    assert(G.EdgeNum == edges + 1);
    assert(DegreeOf(v1) == deg1 + 1 && DegreeOf(v3) == deg3 + 1);
    assert(SumDegree(&G) == sum + 2);
    printf("  [C] duplicate insert rejected OK\n");

    /* ⑩ 删掉刚插的边：全还原 */
    DeleteALGraphEdge(&G, v1, v3);
    assert(G.EdgeNum == edges);
    assert(DegreeOf(v1) == deg1 && DegreeOf(v3) == deg3);
    assert(SumDegree(&G) == sum);
    assert(!LinkedTo(v1,v3) && !LinkedTo(v3,v1));
    printf("  [D] delete (1,3) OK\n");

    /* ⑪ 删不存在的边：两侧都没动手 */
    DeleteALGraphEdge(&G, v0, v3);
    assert(G.EdgeNum == edges && SumDegree(&G) == sum);
    assert(DegreeOf(v0) == 2 && DegreeOf(v3) == 1);
    printf("  [D] delete missing edge: no-op OK\n");

    /* ⑫ (0,1) 与 (2,3) 分别覆盖 Prev!=NULL / Prev==NULL 两种改链分支 */
    DeleteALGraphEdge(&G, v0, v1);
    assert(!LinkedTo(v0,v1) && !LinkedTo(v1,v0));
    assert(G.EdgeNum == edges - 1 && SumDegree(&G) == sum - 2);
    DeleteALGraphEdge(&G, v2, v3);
    assert(!LinkedTo(v2,v3) && !LinkedTo(v3,v2));
    assert(G.EdgeNum == edges - 2 && SumDegree(&G) == sum - 4);
    printf("  [D] mid-slot / head-slot unlink OK\n");

    /* ⑬ 插顶点：进名册、孤立、Id 接上编号 */
    int oldVex = G.VexNum;
    InsertVertexNode(&G, 5000);
    assert(G.VexNum == oldVex + 1);
    VertexNode *tail = TailVertex(&G);
    assert(tail != G.Head);
    assert(tail->VexData == 5000);
    assert(tail->NextVertex == NULL);
    assert(tail->Id == oldVex);
    assert(tail->FirstEdge == NULL);
    assert(DegreeOf(tail) == 0);
    assert(SumDegree(&G) == sum - 4);   /* 孤立点不带边 */
    printf("  [C] insert vertex (isolated) OK\n");

    PrintALGraph(&G);
    printf("crud OK: |V|=%d |E|=%d\n", G.VexNum, G.EdgeNum);
}

/* ===== 按层递归 BFS：测试脚手架，Graph.c 一字不动 ===== */
/* 先叫 TestVisit，明晚正式接口定进 Graph.h 时再换名，避免重名 */
typedef void (*TestVisit)(VertexNode *v);

static void PrintId(VertexNode *v) {
    printf("%d ", v->Id);
}

/* L = 当前这一层的顶点，n = 个数；递归的单位是「层」不是「顶点」 */
static void BFSLayer(VertexNode **L, int n, bool *Visited, int MaxId, TestVisit Visit) {
    if (n == 0) { return; }        /* ← 断点点这里：Frames 里能看见一层层栈帧 */
    VertexNode **Next = (VertexNode **)malloc((MaxId + 1) * sizeof(VertexNode *));
    if (Next == NULL) { return; }
    int NextNum = 0;
    for (int i = 0; i < n; i++) {
        Visit(L[i]);               /* 横：这一层的每个顶点，交给回调 */
        for (EdgeNode *e = L[i]->FirstEdge; e != NULL; e = e->NextEdge) {
            VertexNode *To = e->ToVertex;
            if (!Visited[To->Id]) {
                Visited[To->Id] = true;    /* 入层时盖章，别等下一层 */
                Next[NextNum++] = To;
            }
        }
    }
    BFSLayer(Next, NextNum, Visited, MaxId, Visit);   /* 竖：递归到下一层 */
    free(Next);
}

void BfsSmokeTest(void) {
    /* 故意选一条瘦长的图：层多、首批只有两个分叉，栈好看 */
    VertexType V[6] = {100, 200, 300, 400, 500, 600};
    Edge       E[6] = {{0,1},{0,2},{1,3},{2,3},{3,4},{4,5}};
    RowGraph   src  = { V, E, 6, 6 };

    ALGraph G;
    InitALGraph(&G);
    CreateALGraph(&G, &src);

    /* 账本按 MaxId+1 开，不按 VexNum（删顶点会留空洞） */
    int MaxId = -1;
    for (VertexNode *v = G.Head->NextVertex; v; v = v->NextVertex)
        if (v->Id > MaxId) MaxId = v->Id;

    bool *Visited = (bool *)calloc(MaxId + 1, sizeof(bool));
    if (Visited == NULL) { return; }
    VertexNode **L0 = (VertexNode **)malloc(sizeof(VertexNode *));
    if (L0 == NULL) { free(Visited); return; }

    L0[0] = FindById(&G, 0);
    Visited[L0[0]->Id] = true;

    printf("BFS: ");
    BFSLayer(L0, 1, Visited, MaxId, PrintId);
    printf("\n");

    for (int i = 0; i <= MaxId; i++) assert(Visited[i]);   /* 连通图应全访到 */
    printf("bfs OK: |V|=%d all visited\n", G.VexNum);

    free(L0);
    free(Visited);
}