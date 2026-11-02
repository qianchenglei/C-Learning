#include <stdio.h>
#include <string.h>
#include "SingleLinkListStack.h"
#include "Queue.h"
#include "Stack.h"
#include "LinkListQueue.h"

void printData(const BaseDataUnit *data) {
    printf("Mark=%d, Gender=%s, Name=%s\n",
           data->Mark,
           data->Gender ? "Male" : "Female",
           data->Name);
}

// 测试顺序栈
void testSequentialStack() {
    printf("\n========== Sequential Stack Test ==========\n");
    Stack st;
    BaseDataUnit temp, out;
    bool ok;

    ok = InitStack(&st);
    printf("InitStack: %s\n", ok ? "success" : "fail");
    printf("StackEmpty (init): %s\n", StackEmpty(&st) ? "true" : "false");

    // 入栈 3 个元素
    temp.Mark = 1;
    temp.Gender = true;
    strcpy(temp.Name, "Alice");
    ok = PushInToStack(&st, temp);
    printf("Push Alice: %s\n", ok ? "success" : "fail");

    temp.Mark = 2;
    temp.Gender = false;
    strcpy(temp.Name, "Bob");
    ok = PushInToStack(&st, temp);
    printf("Push Bob: %s\n", ok ? "success" : "fail");

    temp.Mark = 3;
    temp.Gender = true;
    strcpy(temp.Name, "Charlie");
    ok = PushInToStack(&st, temp);
    printf("Push Charlie: %s\n", ok ? "success" : "fail");

    // 获取栈顶
    ok = GetTopDataUnit(&st, &out);
    if (ok) {
        printf("Top element: ");
        printData(&out);
    }

    // 出栈两个
    ok = PopOfStack(&st, &out);
    if (ok) {
        printf("Popped: ");
        printData(&out);
    }
    ok = PopOfStack(&st, &out);
    if (ok) {
        printf("Popped: ");
        printData(&out);
    }

    printf("StackEmpty after pops: %s\n", StackEmpty(&st) ? "true" : "false");

    // 销毁
    DestroyStack(&st);
    printf("DestroyStack done\n");
}

// 测试链式栈
void testLinkListStack() {
    printf("\n========== Link List Stack Test ==========\n");
    LinkListStack st;
    BaseDataUnit temp, out;
    bool ok;

    ok = SLLS_InitStack(&st);
    printf("InitStack: %s\n", ok ? "success" : "fail");
    printf("StackEmpty (init): %s\n", SLLS_StackEmpty(&st) ? "true" : "false");

    // 入栈 3 个元素
    temp.Mark = 101;
    temp.Gender = true;
    strcpy(temp.Name, "David");
    ok = SLLS_PushInToStack(&st, temp);
    printf("Push David: %s\n", ok ? "success" : "fail");

    temp.Mark = 102;
    temp.Gender = false;
    strcpy(temp.Name, "Eva");
    ok = SLLS_PushInToStack(&st, temp);
    printf("Push Eva: %s\n", ok ? "success" : "fail");

    temp.Mark = 103;
    temp.Gender = true;
    strcpy(temp.Name, "Frank");
    ok = SLLS_PushInToStack(&st, temp);
    printf("Push Frank: %s\n", ok ? "success" : "fail");

    // 获取栈顶
    ok = SLLS_GetTopDataUnit(&st, &out);
    if (ok) {
        printf("Top element: ");
        printData(&out);
    }

    // 出栈两个
    ok = SLLS_PopOfStack(&st, &out);
    if (ok) {
        printf("Popped: ");
        printData(&out);
    }
    ok = SLLS_PopOfStack(&st, &out);
    if (ok) {
        printf("Popped: ");
        printData(&out);
    }

    printf("StackEmpty after pops: %s\n", SLLS_StackEmpty(&st) ? "true" : "false");

    // 清空栈
    SLLS_CleanStack(&st);
    printf("CleanStack done\n");
    printf("StackEmpty after clean: %s\n", SLLS_StackEmpty(&st) ? "true" : "false");
}

// 测试链式队列（全部动态分配）
void testLinkListQueue() {
    printf("\n========== Link List Queue Test ==========\n");

    LLQueue *q = NULL; // 外部指针先置空
    BaseDataUnit temp, out;
    bool ok;

    // 1. 初始化（传入 &q）
    ok = InitLLQueue(&q);
    if (!ok || q == NULL) {
        printf("InitLLQueue failed (memory allocation error)\n");
        return;
    }
    printf("InitLLQueue: success\n");
    printf("QueueEmpty (init): %s\n", LLQueueEmpty(q) ? "true" : "false");

    // 2. 入队 3 个元素
    temp.Mark = 301;
    temp.Gender = true;
    strcpy(temp.Name, "Kate");
    ok = PushLLQueue(q, temp);
    printf("Push Kate: %s\n", ok ? "success" : "fail");

    temp.Mark = 302;
    temp.Gender = false;
    strcpy(temp.Name, "Leo");
    ok = PushLLQueue(q, temp);
    printf("Push Leo: %s\n", ok ? "success" : "fail");

    temp.Mark = 303;
    temp.Gender = true;
    strcpy(temp.Name, "Mia");
    ok = PushLLQueue(q, temp);
    printf("Push Mia: %s\n", ok ? "success" : "fail");

    // 3. 获取队头
    ok = GetFirstLLQueue(q, &out);
    if (ok) {
        printf("Front element: ");
        printData(&out);
    } else {
        printf("GetFirst failed\n");
    }

    // 4. 出队两个
    ok = PopLLQueue(q, &out);
    if (ok) {
        printf("Popped: ");
        printData(&out);
    }
    ok = PopLLQueue(q, &out);
    if (ok) {
        printf("Popped: ");
        printData(&out);
    }
    printf("QueueEmpty after pops: %s\n", LLQueueEmpty(q) ? "true" : "false");

    // 5. 再入队一个，验证队列继续工作
    temp.Mark = 304;
    temp.Gender = false;
    strcpy(temp.Name, "Noah");
    ok = PushLLQueue(q, temp);
    printf("Push Noah: %s\n", ok ? "success" : "fail");

    ok = GetFirstLLQueue(q, &out);
    if (ok) {
        printf("Front element now: ");
        printData(&out);
    }

    // 6. 清空所有数据节点（保留头结点） – 可选，用于测试 DeleteLLQueue
    ok = DeleteLLQueue(q);
    printf("DeleteLLQueue: %s\n", ok ? "success" : "fail");
    printf("QueueEmpty after delete: %s\n", LLQueueEmpty(q) ? "true" : "false");

    // 7. 销毁整个队列（释放头结点、外壳，并将外部指针置 NULL）
    ok = DestroyLLQueue(&q); // 传入 &q，二级指针
    printf("DestroyLLQueue: %s\n", ok ? "success" : "fail");
    // 此时 q 已经被 Destroy 内部置为 NULL，不能再使用
}

// 测试循环队列
void testQueue() {
    printf("\n========== Circular Queue Test ==========\n");
    ArrayQueue q;
    BaseDataUnit temp, out;
    bool ok;

    ok = InitQueue(&q);
    printf("InitQueue: %s\n", ok ? "success" : "fail");
    printf("QueueEmpty (init): %s\n", QueueEmpty(&q) ? "true" : "false");
    printf("QueueFull (init): %s\n", QueueFull(&q) ? "true" : "false");

    // 入队 3 个元素
    temp.Mark = 201;
    temp.Gender = true;
    strcpy(temp.Name, "Grace");
    ok = InQueue(&q, &temp);
    printf("Enqueue Grace: %s\n", ok ? "success" : "fail");

    temp.Mark = 202;
    temp.Gender = false;
    strcpy(temp.Name, "Henry");
    ok = InQueue(&q, &temp);
    printf("Enqueue Henry: %s\n", ok ? "success" : "fail");

    temp.Mark = 203;
    temp.Gender = true;
    strcpy(temp.Name, "Ivy");
    ok = InQueue(&q, &temp);
    printf("Enqueue Ivy: %s\n", ok ? "success" : "fail");

    // 获取队头
    ok = GetQueue(&q, &out);
    if (ok) {
        printf("Front element: ");
        printData(&out);
    }

    // 出队两个
    ok = PopQueue(&q, &out);
    if (ok) {
        printf("Dequeued: ");
        printData(&out);
    }
    ok = PopQueue(&q, &out);
    if (ok) {
        printf("Dequeued: ");
        printData(&out);
    }

    printf("QueueEmpty after dequeues: %s\n", QueueEmpty(&q) ? "true" : "false");

    // 再入队一个，测试循环
    temp.Mark = 204;
    temp.Gender = false;
    strcpy(temp.Name, "Jack");
    ok = InQueue(&q, &temp);
    printf("Enqueue Jack: %s\n", ok ? "success" : "fail");

    // 查看队头
    ok = GetQueue(&q, &out);
    if (ok) {
        printf("Front element now: ");
        printData(&out);
    }

    // 销毁队列
    DestroyQueue(&q);
    printf("DestroyQueue done\n");
}

int main() {
    testSequentialStack();
    testLinkListStack();
    testQueue();
    testLinkListQueue();
    return 0;
}
