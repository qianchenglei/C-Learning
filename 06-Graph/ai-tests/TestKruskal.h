//
// 矩阵版 Kruskal 验收
//   ① 4 点小图：手算总权可对（6），和 Prim 用同一张图
//   ② AE 实机网络：18 条边、总权 56
//   ③ 与 Prim 交叉验证：同一张图，两种算法总权必须相等
//   ④ 不连通图：选不满 n-1 条边，必须返回 -1（而不是返回部分权值）
//
#ifndef C_LEARNING_TESTKRUSKAL_H
#define C_LEARNING_TESTKRUSKAL_H

void KruskalSmallGraphTest(void);
void KruskalAEGraphTest(void);
void KruskalMatchesPrimTest(void);
void KruskalDisconnectedTest(void);

#endif //C_LEARNING_TESTKRUSKAL_H
