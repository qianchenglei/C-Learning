//
// Created by 14266 on 2026/11/9.
//
#include <stdio.h>
#include "TestThing.h"
#include "TestDfs.h"
#include "TestBfs.h"
#include "TestDirected.h"
#include "TestTopo.h"
#include "TestMGraph.h"
#include "TestUnionFind.h"
#include "TestPrim.h"
#include "TestKruskal.h"

int main(void) {
#ifndef NDEBUG
    /* Debug 构建（默认）：跑完全部验收测试 */
    SmokeTest();
    CrudSmokeTest();
    BfsSmokeTest();
    DfsTest();
    BfsTest();
    BfsAeGraphTest();
    DirectedCreateTest();
    DirectedCrudTest();
    TopoDagTest();
    TopoMultiSourceTest();
    TopoChainTest();
    TopoCycleTest();
    TopoReadOnlyTest();
    MGraphReadTableTest();
    UFDInitTest();
    UFDFindRootTest();
    UFDPathCompressionTest();
    UFDUnionTest();
    UFDKruskalTest();
    PrimSmallGraphTest();
    PrimAEGraphTest();
    PrimStartIndependenceTest();
    PrimDisconnectedTest();
    KruskalSmallGraphTest();
    KruskalAEGraphTest();
    KruskalMatchesPrimTest();
    KruskalDisconnectedTest();
#else
    /* Release 构建（定义 NDEBUG）：测试不参与运行 */
    printf("06_Graph: Release build, tests are disabled (NDEBUG).\n");
#endif
    return 0;
}
