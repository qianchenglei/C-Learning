#pragma once
#ifndef LINKLIST_H
#define LINKLIST_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#define MaxStudentNameSize 50
#define LIST_SINGLE       1   // 单链表
#define LIST_DOUBLE       2   // 双链表
#define LIST_CIRC_SINGLE  3   // 循环单链表
#define LIST_CIRC_DOUBLE  4   // 循环双链表
#define SEARCH_BY_UUID   101
#define SEARCH_BY_NAME   102
#define SEARCH_BY_GENDER 103
#define UUID_MAKER_CODE 0x425951ULL 
typedef unsigned long long uint64_t;

typedef struct Students_Data
{
    int  StudentsMark;
    char StudentName[MaxStudentNameSize];
    bool StudentGender;
    uint64_t  StudentUUID;
}Students_Data;

typedef struct LinkListData
{
    struct LinkListData* PrimaryDataUnitAdd;
    Students_Data StudentsData;
    struct LinkListData* NextDataUnitAdd;
    int NowListType;
}LinkList;
extern LinkList* DefaltLinkList;

void EnableANSI();
int InitLinkList(LinkList**,int);
uint64_t GenarateUUID();
int InsertAt(LinkList* List, int index, Students_Data);
int IEILASub_Single (LinkList*, Students_Data, int index);
int IEILASub_DOUBLE(LinkList*, Students_Data, int index);
int IEILASub_cyc_Single(LinkList*, Students_Data, int index);
int IEILASub_cyc_DOUBLE(LinkList*, Students_Data, int index);
int InsertEumeIntotheListByHand(LinkList*, Students_Data);
int IEITLBHSub_SingleLinkList(LinkList*, Students_Data);
int IEITLBHSub_DoubleLinkList(LinkList*, Students_Data);
int IEITLBHSub_Cyc_SingleLinkList(LinkList*, Students_Data);
int IEITLBHSub_Cyc_DoubleLinkList(LinkList*, Students_Data);
int InsertEumeIntotheListByEnd(LinkList*, Students_Data);
int IEITLBESub_SingleLinkList(LinkList*, Students_Data);
int IEITLBESub_DoubleLinkList(LinkList*, Students_Data);
int IEITLBESub_Cyc_SingleLinkList(LinkList*, Students_Data);
int IEITLBESub_Cyc_DoubleLinkList(LinkList*, Students_Data);
int DeleteDataUnit(LinkList* List, Students_Data* BackData, int index);
int DDUSub_BySingle(LinkList*, Students_Data*, int index);
int DDUSub_ByDouble(LinkList*, Students_Data*, int index);
int DDUSub_By_Cyc_Single(LinkList*, Students_Data*, int index);
int DDUSub_By_Cyc_Double(LinkList*, Students_Data*, int index);
int PrintAllList(LinkList*);
int PrintStudents_Date(Students_Data TempData, int index);
int SearchDataUnit(LinkList* List, int SearchField, const void* SearchValue);
int SearchSub_Single(LinkList* List, int SearchField, const void* SearchValue);
int SearchSub_Double(LinkList* List, int SearchField, const void* SearchValue);
int SearchSub_CycSingle(LinkList* List, int SearchField, const void* SearchValue);
int SearchSub_CycDouble(LinkList* List, int SearchField, const void* SearchValue);
#endif