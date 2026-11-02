#ifndef STACKANDHEAP_QUEUE_H
#define STACKANDHEAP_QUEUE_H
#define MaxArraySize 50
#include "DataType.h"

typedef struct Queue {
    BaseDataUnit Data[MaxArraySize];
    int Front, Rear;
} ArrayQueue;

bool InitQueue(ArrayQueue *Q);

bool QueueEmpty(ArrayQueue *Q);

bool QueueFull(ArrayQueue *Q);

bool InQueue(ArrayQueue *Q, BaseDataUnit *Data);

bool PopQueue(ArrayQueue *Q, BaseDataUnit *Data);

bool GetQueue(ArrayQueue *Q, BaseDataUnit *Data);

bool DestroyQueue(ArrayQueue *Q);

#endif //STACKANDHEAP_QUEUE_H
