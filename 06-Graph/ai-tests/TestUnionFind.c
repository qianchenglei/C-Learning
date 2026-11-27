//
// 并查集验收：五项
//   ① 初始化：每个元素自成一族
//   ② 查找：顺着父链爬到根
//   ③ 路径压缩：查过一次之后，路径上的点直连根
//   ④ 合并：跨集合返回 true，同集合返回 false，NumSets 只在真正合并时减一
//   ⑤ Kruskal 语义：4 点 5 边，应收 3 条、跳过 2 条会成环的
//
#include "UnionFindDisjointSet.h"
#include "TestUnionFind.h"
#include <assert.h>
#include <stdlib.h>

/* 手动把 Parent 数组改成一条链，用来验证查找与压缩（不走 Union） */
static void BuildChain(UFDSet *UFS, int ChainLength) {
    for (int Idx = 1; Idx < ChainLength; Idx++) {
        UFS->Parent[Idx] = Idx - 1;   /* Idx 的爹是 Idx-1，最后 0 是根 */
    }
}

void UFDInitTest(void) {
    setbuf(stdout, NULL);

    UFDSet UFS;
    UFDSInit(&UFS, 10);

    assert(UFS.Parent != NULL);
    assert(UFS.ElementNum == 10);
    assert(UFS.NumSets == 10);

    for (int Idx = 0; Idx < 10; Idx++) {
        assert(UFS.Parent[Idx] == Idx);   /* 自己是自己的爹 = 自成一族 */
    }

    printf("  [U] 初始化：10 个元素 / 10 个集合 / 各自为根 OK\n");

    free(UFS.Parent);
    UFS.Parent = NULL;
}

void UFDFindRootTest(void) {
    setbuf(stdout, NULL);

    UFDSet UFS;
    UFDSInit(&UFS, 5);
    BuildChain(&UFS, 5);                  /* 4→3→2→1→0 */

    assert(UFDSFindRoot(&UFS, 4) == 0);   /* 链尾爬到顶 */
    assert(UFDSFindRoot(&UFS, 2) == 0);   /* 链中爬到顶 */
    assert(UFDSFindRoot(&UFS, 0) == 0);   /* 根返回自己 */

    printf("  [U] 查找：4→3→2→1→0 爬到根 0 OK\n");

    free(UFS.Parent);
    UFS.Parent = NULL;
}

void UFDPathCompressionTest(void) {
    setbuf(stdout, NULL);

    UFDSet UFS;
    UFDSInit(&UFS, 5);
    BuildChain(&UFS, 5);

    assert(UFS.Parent[4] == 3);           /* 压缩前：4 的爹是 3 */
    assert(UFS.Parent[3] == 2);

    UFDSFindRoot(&UFS, 4);                /* 查一次，整条路径应被压平 */

    assert(UFS.Parent[4] == 0);           /* 压缩后：直连根 */
    assert(UFS.Parent[3] == 0);
    assert(UFS.Parent[2] == 0);
    assert(UFS.Parent[1] == 0);

    printf("  [U] 路径压缩：查一次之后 4/3/2/1 全部直连 0 OK\n");

    free(UFS.Parent);
    UFS.Parent = NULL;
}

void UFDUnionTest(void) {
    setbuf(stdout, NULL);

    UFDSet UFS;
    UFDSInit(&UFS, 24);
    assert(UFS.NumSets == 24);

    /* 五次互不相干的两两合并 */
    assert(UFDSUnion(&UFS, 0, 1) == true);
    assert(UFDSUnion(&UFS, 2, 3) == true);
    assert(UFDSUnion(&UFS, 4, 5) == true);
    assert(UFDSUnion(&UFS, 6, 7) == true);
    assert(UFDSUnion(&UFS, 8, 9) == true);

    assert(UFS.NumSets == 19);            /* 24 - 5 */
    printf("  [U] 合并五次：集合数 24 → 19 OK\n");

    /* 重复合并同一对：应拒绝，集合数不变 */
    assert(UFDSUnion(&UFS, 0, 1) == false);
    assert(UFS.NumSets == 19);
    printf("  [U] 重复合并同一对：返回 false、集合数不动 OK\n");

    /* 传递性：0~1、1~2 已连通之后，0~2 应被拒绝 */
    assert(UFDSUnion(&UFS, 1, 2) == true);
    assert(UFS.NumSets == 18);
    assert(UFDSUnion(&UFS, 0, 2) == false);
    assert(UFS.NumSets == 18);
    printf("  [U] 传递性：0-1-2 连通后 0~2 被拒 OK\n");

    free(UFS.Parent);
    UFS.Parent = NULL;
}

void UFDKruskalTest(void) {
    setbuf(stdout, NULL);

    UFDSet UFS;
    UFDSInit(&UFS, 4);

    /* 4 个点、5 条边，已按权值升序排好（权值只影响顺序，测试里直接给序）：
       0-1 / 1-2 / 2-3 这三条能收；
       0-3 和 0-2 会成环，应被拒 */
    const int EdgeFrom[5] = {0, 1, 2, 0, 0};
    const int EdgeTo[5]   = {1, 2, 3, 3, 2};

    int AcceptedEdgeCount = 0;
    for (int EdgeIdx = 0; EdgeIdx < 5; EdgeIdx++) {
        if (UFDSUnion(&UFS, EdgeFrom[EdgeIdx], EdgeTo[EdgeIdx])) {
            AcceptedEdgeCount++;
        }
    }

    assert(AcceptedEdgeCount == 3);       /* n - 1 = 3，恰好够连成一棵树 */
    assert(UFS.NumSets == 1);             /* 全图只剩一个集合 */
    printf("  [U] Kruskal 语义：收 3 条、拒 2 条环边、集合数 = 1 OK\n");

    free(UFS.Parent);
    UFS.Parent = NULL;
}
