#include "queue.h"

void InitQueue(Queue *Q) {
    if (Q == NULL) return;
    Q->front = 0;
    Q->rear = 0;
}

bool QueueEmpty(const Queue *Q) { return Q->front == Q->rear; }
bool QueueFull(const Queue *Q)  { return (Q->rear + 1) % QUEUE_MAX == Q->front; }

bool EnQueue(Queue *Q, void *x) {
    if (QueueFull(Q)) return false;
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % QUEUE_MAX;
    return true;
}

bool DeQueue(Queue *Q, void **x) {
    if (QueueEmpty(Q)) return false;
    *x = Q->data[Q->front];
    Q->data[Q->front] = NULL;
    Q->front = (Q->front + 1) % QUEUE_MAX;
    return true;
}

/* 牺牲一格，所以最多存 QUEUE_MAX - 1 个 */
int QueueLength(const Queue *Q) {
    return (Q->rear - Q->front + QUEUE_MAX) % QUEUE_MAX;
}
