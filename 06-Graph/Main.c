//
// Created by 14266 on 2026/11/9.
//
#include "TestThing.h"
#include "TestDfs.h"
#include "TestBfs.h"
#include "TestDirected.h"
#include "TestTopo.h"

int main(void) {
    SmokeTest();
    CrudSmokeTest();
    BfsSmokeTest();
    DfsTest();
    BfsTest();
    DirectedCreateTest();
    DirectedCrudTest();
    TopoDagTest();
    TopoMultiSourceTest();
    TopoChainTest();
    TopoCycleTest();
    TopoReadOnlyTest();
    return 0;
}
