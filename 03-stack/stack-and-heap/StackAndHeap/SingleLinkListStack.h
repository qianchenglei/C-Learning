#pragma once
#ifndef STACKANDHEAP_SINGLELINKLISTSTACK_H
#define STACKANDHEAP_SINGLELINKLISTSTACK_H
#include <stdio.h>
#include <string.h>
#include "DataType.h"

typedef struct LinkListDataUnit {
    BaseDataUnit Data;
    struct LinkListDataUnit *Next;
} LinkListDataUnit;

typedef struct LinkListStack {
    LinkListDataUnit *First;
    int StackSize;
} LinkListStack;

bool SLLS_InitStack(LinkListStack *Stack);

bool SLLS_StackEmpty(const LinkListStack *Stack);

bool SLLS_PushInToStack(LinkListStack *, BaseDataUnit);

bool SLLS_PopOfStack(LinkListStack *, BaseDataUnit *);

bool SLLS_GetTopDataUnit(LinkListStack *, BaseDataUnit *);

bool SLLS_CleanStack(LinkListStack *);
#endif //STACKANDHEAP_SINGLELINKLISTSTACK_H
