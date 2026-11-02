#pragma once

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "DataType.h"
#define MaxDataSize 50

typedef struct DataUnit {
    BaseDataUnit Data[MaxDataSize];
    int TopPrint;
} Stack;

bool InitStack(Stack *);

bool StackEmpty(const Stack *);

bool PushInToStack(Stack *, BaseDataUnit);

bool PopOfStack(Stack *, BaseDataUnit *);

bool GetTopDataUnit(Stack *, BaseDataUnit *);

bool DestroyStack(Stack *);
