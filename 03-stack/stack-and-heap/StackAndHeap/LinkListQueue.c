//
// Created by 14266 on 2026/8/28.
//

#include "LinkListQueue.h"

#include <stdlib.h>
#include <string.h>

bool InitLLQueue(LLQueue **Queue) {
    if (Queue == NULL) {
        return false;
    }
    LLQueue *Q = (LLQueue *) malloc(sizeof(LLQueue));
    LLQueueData *Hard = (LLQueueData *) malloc(sizeof(LLQueueData));
    if (Hard == NULL) {
        return false;
    }
    Q->Front = Hard;
    Q->Rear = Hard;
    *Queue = Q;
    return true;
}

bool LLQueueEmpty(const LLQueue *Queue) {
    if (Queue == NULL) {
        return false;
    }
    if (Queue->Front == Queue->Rear) {
        return true;
    } else {
        return false;
    }
}

bool PushLLQueue(LLQueue *Queue, BaseDataUnit DataUnit) {
    if (Queue == NULL) {
        return false;
    }
    LLQueueData *InsetData = (LLQueueData *) malloc(sizeof(LLQueueData));
    if (InsetData == NULL) {
        return false;
    } else {
        memset(InsetData, 0, sizeof(LLQueueData));
        InsetData->DataUnit = DataUnit;
        InsetData->Next = NULL;
        Queue->Rear->Next = InsetData;
        Queue->Rear = InsetData;
        return true;
    }
}

bool PopLLQueue(LLQueue *Queue, BaseDataUnit *DataUnit) {
    if (Queue == NULL) {
        return false;
    }
    if (LLQueueEmpty(Queue) != true) {
        LLQueueData *Temp = Queue->Front->Next;
        *DataUnit = Temp->DataUnit;
        Queue->Front->Next = Temp->Next;
        if (Queue->Rear == Temp) {
            Queue->Rear = Queue->Front;
        }
        free(Temp);
        return true;
    } else {
        return false;
    }
}

bool GetFirstLLQueue(LLQueue *Queue, BaseDataUnit *DataUnit) {
    if (Queue == NULL) {
        return false;
    }
    if (LLQueueEmpty(Queue) != true) {
        *DataUnit = Queue->Front->Next->DataUnit;
        return true;
    } else {
        return false;
    }
}

bool DeleteLLQueue(LLQueue *Queue) {
    if (Queue == NULL) {
        return false;
    }
    LLQueueData *Temp = Queue->Front->Next;
    while (Temp != NULL) {
        LLQueueData *Next = Temp->Next;
        free(Temp);
        Temp = Next;
    }
    Queue->Front->Next = NULL;
    Queue->Rear = Queue->Front;
    return true;
}

bool DestroyLLQueue(LLQueue **Queue) {
    if (Queue == NULL || *Queue == NULL) {
        return false;
    }
    DeleteLLQueue(*Queue);
    free(*Queue);
    *Queue = NULL;
    return true;
}
