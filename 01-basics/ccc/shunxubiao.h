#ifndef SHUNXUBIAO_H
#define SHUNXUBIAO_H

#include <stdbool.h>
#include <string.h>
#define EXT      ".data"
#define MaxFileInPutName 40
#define MaxFileName 50
#define Maxsize 50
#define Maxnamesize 20
#define S_Code 300
#define Erorr_Code 402


typedef struct
{
    char username[Maxnamesize];
    int userid;
} SQListData;

typedef struct table
{
    SQListData data[Maxsize];
    int TableLength;
} SQList;
extern SQList L1 ;
extern char ListName[MaxFileName];
void SubMamu();
void InitList( SQList *L);
bool IsEmpty(SQList *L);
void Length(SQList *L);
SQListData GetInput(SQList *L);
void LocateElembyUserName(SQList *L,char UserName[]);
void LocateElembyID(SQList *L,int Id);
void GetElem(SQList *L,int a);
int ListInsert(SQList *L,int index, SQListData data);
int ListDelete(SQList *L,int index,SQListData *e);
int PrintList(SQList *L);
int DestroyList(SQList *L,const char *tableName);
int LoadListForDisk(SQList *L, const char *tableName);
void SaveListToDisk(SQList *L, const char *tableName);

#endif