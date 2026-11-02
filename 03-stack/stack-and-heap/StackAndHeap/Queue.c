//
// Created by 14266 on 2026/8/28.
//

#include "Queue.h"


bool InitQueue(ArrayQueue *Q) {
    if (Q == NULL) {
        return false;
    }
    Q->Front = 0;
    Q->Rear = 0;
    return true;
}

bool QueueEmpty(ArrayQueue *Q) {
    if (Q == NULL) {
        return false;
    }
    if (Q->Rear == Q->Front) {
        return true;
    } else {
        return false;
    }
}

bool QueueFull(ArrayQueue *Q) {
    if (Q == NULL) {
        return false;
    }
    if ((Q->Rear + 1) % MaxArraySize == Q->Front) {
        return true;
    } else {
        return false;
    }
}

bool InQueue(ArrayQueue *Q, BaseDataUnit *Data) {
    if (Q == NULL) {
        return false;
    }
    if (QueueFull(Q) != true) {
        Q->Data[Q->Rear] = *Data;
        Q->Rear = (Q->Rear + 1) % MaxArraySize;
        return true;
    } else {
        return false;
    }
}

bool PopQueue(ArrayQueue *Q, BaseDataUnit *Data) {
    if (Q == NULL) {
        return false;
    }
    if (QueueEmpty(Q) != true) {
        *Data = Q->Data[Q->Front];
        Q->Front = (Q->Front + 1) % MaxArraySize;
        return true;
    } else {
        return false;
    }
}

bool GetQueue(ArrayQueue *Q, BaseDataUnit *Data) {
    if (Q == NULL) {
        return false;
    }
    if (QueueEmpty(Q) != true) {
        *Data = Q->Data[Q->Front];
        return true;
    } else {
        return false;
    }
}

bool DestroyQueue(ArrayQueue *Q) {
    if (Q == NULL) {
        return false;
    }
    Q->Front = 0;
    Q->Rear = 0;
    return true;
}
