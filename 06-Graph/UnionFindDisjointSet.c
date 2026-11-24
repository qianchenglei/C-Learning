//
// Created by 14266 on 2026/11/23.
//
#include "UnionFindDisjointSet.h"

#include <stdlib.h>

void UFDSInit(UFDSet *UFS, int ElementNum) {
    UFS->FindRank=NULL;
    UFS->Parent=NULL;
    UFS->ElementNum=0;
    UFS->NumSets = 0;
    if (ElementNum <= 0) { return; }
    UFS->Parent=(int *)malloc(ElementNum*sizeof(int));
    if (UFS->Parent==NULL) {
        UFS->ElementNum = 0;
        UFS->NumSets = 0;
        return;
    }
    for (int i=0;i<ElementNum;i++) {
        UFS->Parent[i]=i;
    }
    UFS->ElementNum=ElementNum;
    UFS->NumSets=ElementNum;
}

int UFDSFindRoot(UFDSet *UFS, int ExpElement) {
    if (UFS->Parent==NULL) {return -1;}
    if (UFS->Parent[ExpElement]!=ExpElement) {
        UFS->Parent[ExpElement]=UFDSFindRoot(UFS,UFS->Parent[ExpElement]);
    }
    return UFS->Parent[ExpElement];
}

bool UFDSUnion(UFDSet *UFS, int ExpUnionElementA, int ExpUnionElementB) {
    if (UFS->Parent==NULL) {return false;}
    int ExpUnionAParent=UFDSFindRoot(UFS,ExpUnionElementA);
    int ExpUnionBParent=UFDSFindRoot(UFS,ExpUnionElementB);
    if (ExpUnionAParent != ExpUnionBParent) {
        UFS->Parent[ExpUnionAParent]=ExpUnionBParent;
        UFS->NumSets--;
        return true;
    }
    return false;
}

void UFDSDestroy(UFDSet *UFS) {
    free(UFS->Parent);
    free(UFS->FindRank);
    UFS->Parent=NULL;
    UFS->FindRank=NULL;
    UFS->NumSets=0;
    UFS->ElementNum=0;
}
