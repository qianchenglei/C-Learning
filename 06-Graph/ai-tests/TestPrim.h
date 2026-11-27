//
// 矩阵版 Prim 验收
//   ① 4 点小图：手算总权可对（6）
//   ② AE 实机网络：18 条边、总权 56
//   ③ 换起点：总权不变（MST 没有"原点"）
//   ④ 不连通图：只吃掉能到达的部分，不崩
//
#ifndef C_LEARNING_TESTPRIM_H
#define C_LEARNING_TESTPRIM_H

void PrimSmallGraphTest(void);
void PrimAEGraphTest(void);
void PrimStartIndependenceTest(void);
void PrimDisconnectedTest(void);

#endif //C_LEARNING_TESTPRIM_H
