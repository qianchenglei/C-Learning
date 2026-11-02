#ifndef DANLIANBIAO_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define MaxStudentNameSize 50
typedef struct Students_Data
{
    int  StudentsMark;
    char StudentName[MaxStudentNameSize];
    bool StudentGender;
    int  StudentUUID;
}Students_Data;

typedef struct SingleLinkList_Data
{
    Students_Data Students_Data;
    SingleLinkList_Data *NextDataNode;
}SingleLinkList_Data;
extern SingleLinkList_Data* SingleLinkList;

bool InitSingleLinkList(SingleLinkList_Data *List);
#endif