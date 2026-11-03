#ifndef COMMON_QUEUE_H
#define COMMON_QUEUE_H

#include <stdbool.h>
#include <stddef.h>   /* NULL */

/* 循环队列，牺牲一个单元区分空/满。
   层序遍历、BFS 用它；判满条件是 (rear+1)%N == front。 */
#define QUEUE_MAX 100

typedef struct {
    void *data[QUEUE_MAX];
    int front;
    int rear;
} Queue;

void InitQueue(Queue *Q);
bool QueueEmpty(const Queue *Q);
bool QueueFull(const Queue *Q);
bool EnQueue(Queue *Q, void *x);
bool DeQueue(Queue *Q, void **x);
int  QueueLength(const Queue *Q);

#endif /* COMMON_QUEUE_H */
