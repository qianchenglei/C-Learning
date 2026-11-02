#pragma once
#ifndef STACKANDHEAP_DATATYPE_H
#define STACKANDHEAP_DATATYPE_H
#define MaxNameSize 50
#include <stdio.h>
#include <stdbool.h>

typedef struct BaseDataUnit {
    int Mark;
    bool Gender;
    char Name[MaxNameSize];
} BaseDataUnit;


#endif //STACKANDHEAP_DATATYPE_H
