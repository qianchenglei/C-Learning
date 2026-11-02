#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "KMP.h"

/* 运行一次测试:算 next + 匹配,打印结果 */
static void runTest(const char *name, const char *text, const char *pattern) {
    int *next = NULL;
    int modeLen = 0;
    int mark = -1;
    int textLen = (int)strlen(text);

    printf("==== %s ====\n", name);
    printf("文本: %s\n", text);
    printf("模式: %s\n", pattern);

    if (!KMP_Next((char *)pattern, &next, &modeLen)) {
        printf("  -> next 计算失败(空模式?)\n\n");
        return;
    }

    printf("next: ");
    for (int i = 0; i < modeLen; i++)
        printf("%d ", next[i]);
    printf("\n");

    if (KMP_Search((char *)text, &next, &textLen, (char *)pattern, &mark))
        printf("  -> 找到!起始下标 %d,内容: %s\n\n", mark, text + mark);
    else
        printf("  -> 未找到\n\n");

    free(next);
}

int main(void) {
    /* 基本 + 边界 */
    runTest("匹配在中间", "abababacab", "ababaca");
    runTest("模式在开头", "hello world", "hello");
    runTest("模式在结尾", "hello world", "world");
    runTest("重复字符", "aaaaaaaa", "aaa");
    runTest("模式=整个文本", "kmp", "kmp");
    runTest("重叠型", "ababab", "abab");
    runTest("经典 mississippi", "mississippi", "issip");
    runTest("单字符命中", "aaaa", "a");

    /* 失败路径 */
    runTest("模式不存在", "hello", "xyz");
    runTest("模式比文本长", "ab", "abc");
    runTest("空文本", "", "a");
    runTest("空模式串", "abc", "");
    runTest("单字符不命中", "aaaa", "b");

    return 0;
}