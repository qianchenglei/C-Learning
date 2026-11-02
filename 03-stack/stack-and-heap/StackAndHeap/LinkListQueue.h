//
// Created by 14266 on 2026/8/28.
//

#ifndef STACKANDHEAP_LINKLISTQUEUE_H
#define STACKANDHEAP_LINKLISTQUEUE_H
#include "DataType.h"

typedef struct LLQueueData {
    BaseDataUnit DataUnit;
    struct LLQueueData *Next;
} LLQueueData;

typedef struct LLQueue {
    LLQueueData *Front;
    LLQueueData *Rear;
} LLQueue;

bool InitLLQueue(LLQueue **Queue);

bool LLQueueEmpty(const LLQueue *Queue);

bool PushLLQueue(LLQueue *Queue, BaseDataUnit DataUnit);

bool PopLLQueue(LLQueue *Queue, BaseDataUnit *DataUnit);

bool GetFirstLLQueue(LLQueue *Queue, BaseDataUnit *DataUnit);

bool DeleteLLQueue(LLQueue *Queue);

bool DestroyLLQueue(LLQueue **Queue);
#endif //STACKANDHEAP_LINKLISTQUEUE_H
