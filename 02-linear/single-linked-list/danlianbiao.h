//
// 单链表（学生数据）
//   头节点兼作表头：NextDataNode 串链，EndDataNode 维护尾指针以便 O(1) 尾插
//
#ifndef DANLIANBIAO_H
#define DANLIANBIAO_H

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
} Students_Data;

typedef struct SingleLinkList_Data
{
    Students_Data Students_Data;              /* 学生数据（成员名与类型同名，C 允许，历史遗留） */
    struct SingleLinkList_Data *NextDataNode; /* 下一个节点 */
    struct SingleLinkList_Data *EndDataNode;  /* 尾指针：只在头节点上维护，供 O(1) 尾插 */
} SingleLinkList_Data;

extern SingleLinkList_Data *SingleLinkList;

void sub(void);
long long GenerateUID(void);

bool InitSingleLinkList(SingleLinkList_Data **List);
bool AddEumeForTheList(SingleLinkList_Data **List, Students_Data NewData, int Index);

int SingleLinkListLength(SingleLinkList_Data *List);

int LookingSingleLinkListByIndex(SingleLinkList_Data *List, int Index, SingleLinkList_Data *BackData);
int LookingSingleLinkListByMark(SingleLinkList_Data *List, int Mark, SingleLinkList_Data *BackData);
int LookingSingleLinkListByName(SingleLinkList_Data *List, char Name[MaxStudentNameSize], SingleLinkList_Data *BackData);
int LookingSingleLinkListByGender(SingleLinkList_Data *List, bool Gender, SingleLinkList_Data *BackData);
int LookingSingleLinkListByUUID(SingleLinkList_Data *List, int uuid, SingleLinkList_Data *BackData);

int LookingSingleInsertForTheListBeing(SingleLinkList_Data **List, Students_Data NewData);
int LookingSingleInsertForTheListEding(SingleLinkList_Data **List, Students_Data NewData);

Students_Data DeleteSingleInsertDataUnit(SingleLinkList_Data **List, int Index);

#endif // DANLIANBIAO_H
