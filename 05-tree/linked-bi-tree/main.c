#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "LinkedOfBinaryTree.h"

/* =====================================================
 * 链式二叉树 · 单元测试
 *   1) 表驱动：每个用例一行，包含先序串和全部期望值
 *   2) 自动断言：不符就打印 [FAIL]，最后汇总
 *   3) 遍历输出用 open_memstream 截获成字符串再比对
 *   退出码：全通过 0，有失败 1（方便接 CI）
 * ===================================================== */

static int gPass = 0;
static int gFail = 0;

static void report(const char *label, const char *want, const char *got) {
    gFail++;
    printf("    [FAIL] %-6s 期望 %s，实际 %s\n", label, want, got);
}

static void check_int(const char *label, int got, int want) {
    if (got == want) { gPass++; return; }
    char w[32], g[32];
    snprintf(w, sizeof w, "%d", want);
    snprintf(g, sizeof g, "%d", got);
    report(label, w, g);
}

static void check_bool(const char *label, bool got, bool want) {
    if (got == want) { gPass++; return; }
    report(label, want ? "true" : "false", got ? "true" : "false");
}

static void check_str(const char *label, const char *got, const char *want) {
    if (got != NULL && strcmp(got, want) == 0) { gPass++; return; }
    report(label, want, got ? got : "(null)");
}

/* 把遍历函数的输出重定向到内存，返回可 free 的字符串 */
static char *capture(void (*fn)(BinaryTree *), BinaryTree *root) {
    char *buf = NULL;
    size_t len = 0;
    FILE *mem = open_memstream(&buf, &len);
    if (mem == NULL) return NULL;

    fflush(stdout);
    FILE *saved = stdout;
    stdout = mem;
    fn(root);
    fflush(mem);
    stdout = saved;

    fclose(mem);          /* 关闭后 buf 才最终可用 */
    return buf;
}

/* ---------------- 用例表 ---------------- */
typedef struct {
    const char *name;
    const char *seq;      /* 先序建树串，# 表示空子树 */
    int  depth;
    int  nodes;
    int  leaves;
    const char *pre;
    const char *in;
    const char *post;
    bool complete;
} TestCase;

static const TestCase CASES[] = {
    /* 名称        先序串                深 结 叶  先序       中序       后序       完全 */
    { "空树",     "#",                 0, 0, 0, "",        "",        "",        true  },
    { "单结点",   "A##",               1, 1, 1, "A",       "A",       "A",       true  },
    { "三结点",   "AB##C##",           2, 3, 2, "ABC",     "BAC",     "BCA",     true  },
    { "满树",     "ABD##E##CF##G##",   3, 7, 4, "ABDECFG", "DBEAFCG", "DEBFGCA", true  },
    { "缺右叶",   "ABD##E##CF###",     3, 6, 3, "ABDECF",  "DBEAFC",  "DEBFCA",  true  },
    { "跳号4",    "AB#D##C##",         3, 4, 2, "ABDC",    "BDAC",    "DBCA",    false },
    { "跳号5",    "AB##C#D##",         3, 4, 2, "ABCD",    "BACD",    "BDCA",    false },
};

int main(void) {
    const size_t n = sizeof CASES / sizeof CASES[0];

    printf("==============================================\n");
    printf("  链式二叉树 · 单元测试（%zu 个用例）\n", n);
    printf("==============================================\n");

    for (size_t i = 0; i < n; i++) {
        const TestCase *c = &CASES[i];
        printf("\n[%zu/%zu] %s   建树串 \"%s\"\n", i + 1, n, c->name, c->seq);

        BinaryTree *root = NULL;
        const char *p = c->seq;
        BuildBiTree(&root, &p);

        check_bool("判空",   IsBiTreeEmpty(root), c->nodes == 0);
        check_int ("深度",   BiTreeDepth(root),   c->depth);
        check_int ("结点数", NodeCount(root),     c->nodes);
        check_int ("叶子数", LeafCount(root),     c->leaves);

        if (c->nodes > 0) {
            char *s;
            s = capture(PreOrder,  root); check_str("先序", s, c->pre);  free(s);
            s = capture(InOrder,   root); check_str("中序", s, c->in);   free(s);
            s = capture(PostOrder, root); check_str("后序", s, c->post); free(s);
        }

        check_bool("完全", IsComplete(root), c->complete);
    }

    int total = gPass + gFail;
    printf("\n----------------------------------------------\n");
    printf("共 %d 项断言：通过 %d，失败 %d\n", total, gPass, gFail);
    if (gFail == 0) {
        printf("✅ 全部通过\n");
    } else {
        printf("❌ %d 项不符，往上找 [FAIL] 行\n", gFail);
    }
    printf("----------------------------------------------\n");

    return gFail == 0 ? 0 : 1;
}
