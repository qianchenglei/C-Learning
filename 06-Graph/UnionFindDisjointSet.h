//
// Created by 14266 on 2026/11/23.
//

#ifndef C_LEARNING_UNIONFINDDISJOINTSET_H
#define C_LEARNING_UNIONFINDDISJOINTSET_H
#include <stdio.h>
#include <stdbool.h>

typedef struct UFDSet {
    int *Parent;
    /* Parent[i] = i 的父节点编号。
       Parent[i] == i 表示 i 没有上级，它就是根（族长）。
       只存编号，所以是 int*；元素数据不在这里。 */
    int *FindRank;
    /* 合并优先级（秩）：数字大的一方当根，避免树越合越深。
      开了路径压缩后树会被压平，所以它只是"高度上界"，不是真实高度。
      不做按秩合并就置 NULL。 */
    int ElementNum;
    /* 元素总数 = Parent 数组长度。创建后不变。
      Destroy 和任何遍历都必须用它当长度。 */
    int NumSets;
    /* 当前集合个数。初始化 = ElementNum，每次成功合并减 1，全连通时 == 1。
      警告：它随合并变小，绝不能当数组长度用。 */
}UFDSet;

void UFDSInit(UFDSet *UFS,int ElementNum);
int UFDSFindRoot(UFDSet *UFS,int ExpElement);
bool UFDSUnion(UFDSet *UFS,int ExpUnionElementA,int ExpUnionElementB);
void UFDSDestroy(UFDSet *UFS);
#endif //C_LEARNING_UNIONFINDDISJOINTSET_H
