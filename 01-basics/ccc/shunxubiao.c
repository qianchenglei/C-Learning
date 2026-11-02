#include <stdio.h>
#include <string.h>
#include "shunxubiao.h"

int LoadListForDisk(SQList *L, const char *tableName)
{
    char FilePath[MaxFileInPutName];
    snprintf(FilePath, sizeof(FilePath), "%s%s", tableName, EXT);
    FILE *fp = fopen(FilePath, "rb");
    if (fp == NULL)
    {
        printf("read file error\n");
        return Erorr_Code;
    }
    L->TableLength = 0;
    fread(&L->TableLength, sizeof(int), 1, fp);
    if (L->TableLength > Maxsize)
    {
        L->TableLength = Maxsize;
    }
    fread(&L->data, sizeof(SQListData), L->TableLength, fp);
    fclose(fp);
    return S_Code;
}
void SaveListToDisk(SQList *L, const char *tableName)
{

    char FilePath[MaxFileInPutName];
    snprintf(FilePath, sizeof(FilePath), "%s%s", tableName, EXT);
    FILE *fp = fopen(FilePath, "wb");
    if (fp == NULL)
    {
        printf("save file error");
        return;
    }
    fwrite(&L->TableLength, sizeof(int), 1, fp);
    fwrite(&L->data, sizeof(SQListData), L->TableLength, fp);
    fclose(fp);
}

void InitList(SQList *L)
{
    L->TableLength = 0;
}
bool IsEmpty(SQList *L)
{
    if (L == NULL)
    {
        printf("The currently passed-in value is not a valid list\n");
        return true;
    }
    if (L->TableLength == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Length(SQList *L)
{
    if (L == NULL)
    {
        printf("The currently passed-in value is not a valid list\n");
    }
    else if (IsEmpty(L) == true)
    {
        printf("The currently passed-in list was empty\n");
    }
    else
    {
        printf("The currently passed-in list has %d datas\n", L->TableLength);
    }
}
SQListData GetInput(SQList *L)
{
    SQListData Cache = {0};
    int maxid = 0;
    for (int i = 0; i < L->TableLength; i++)
    {
        if (L->data[i].userid > maxid)
        {
            maxid = L->data[i].userid;
        }
    }
    printf("Please input you username\n");
    fgets(Cache.username, Maxnamesize - 1, stdin);
    int len = strlen(Cache.username);
    if (len > 0 && Cache.username[len - 1] == '\n')
        Cache.username[len - 1] = '\0';
    Cache.userid = maxid + 1;
    return Cache;
}
int ListInsert(SQList *L, int index, SQListData data)
{
    if (index >= 1 && index <= L->TableLength + 1 && L->TableLength < Maxsize)
    {
        for (int j = L->TableLength; j >= index; j--)
        {
            L->data[j] = L->data[j - 1];
        }
        L->data[index - 1] = data;
        L->TableLength += 1;
        return S_Code;
    }
    else
    {
        return Erorr_Code;
    }
}
int ListDelete(SQList *L, int index, SQListData *DeleteData)
{
    if (index <= L->TableLength && index >= 1)
    {
        *DeleteData = L->data[index - 1];
        for (int cut = index; cut < L->TableLength; cut++)
        {
            L->data[cut - 1] = L->data[cut];
        }
        L->TableLength--;
        return S_Code;
    }
    else
        return Erorr_Code;
}
int PrintList(SQList *L)
{
    if (L == NULL)
    {
        return Erorr_Code;
    }
    else if (IsEmpty(L) == true)
    {
        return Erorr_Code;
    }
    else
    {
        printf("This is Data of current List\n");
        for (int Count = 0; Count < L->TableLength; Count++)
        {
            printf("UserName:%s ", L->data[Count].username);
            printf("UserID:%d\n", L->data[Count].userid);
        }
        return S_Code;
    }
}
int DestroyList(SQList *L, const char *tableName)
{
    if (L == NULL)
    {
        return Erorr_Code;
    }
    else if (IsEmpty(L) == true)
    {
        return Erorr_Code;
    }
    else
    {
        L->TableLength = 0;
        char FilePath[MaxFileInPutName];
        snprintf(FilePath, sizeof(FilePath), "%s%s", tableName, EXT);
        remove(FilePath);
        return S_Code;
    }
}
void LocateElembyUserName(SQList *L, char UserName[])
{
    for (int c = 0; c < L->TableLength; c++)
    {
        if (strcmp(L->data[c].username, UserName) == 0)
        {
            printf("Found %s in %d\n", UserName, c);
            printf("UserName:%s ", L->data[c].username);
            printf("UserID:%d\n", L->data[c].userid);
            return;
        }
    }
    printf("Not Found\n");
}

void LocateElembyID(SQList *L,int Id){
    for (int c = 0; c < L->TableLength; c++)
    {
        if (L->data[c].userid == Id)
        {
            printf("Found %d in %d\n", Id, c);
            printf("UserName:%s ", L->data[c].username);
            printf("UserID:%d\n", L->data[c].userid);
            return;
        }
    }
    printf("Not Found\n");
}

void GetElem(SQList *L, int a)
{
    printf("UserName:%s ", L->data[a].username);
    printf("UserID:%d\n", L->data[a].userid);
}
void SubMamu(){
        while (1)
        {
        printf("\n==== 当前表: %s(%d 条)====\n", ListName, L1.TableLength);
        printf("press 1 to see User Guide\n");
        printf("What do you want to do(1-9):\n");
        printf("Press 0 to back to Main Mamu\n");
        printf("You now in Sub Mamu\n");
        int Use_Input;
        scanf("%d", &Use_Input);
        switch (Use_Input)
        {
        case 0:
            return;
        case 1:{
            printf("2.Locate Elem by UserName\n");
            printf("3.Locate Elem by UserID\n");
            printf("4.Locate Elem by ListLength\n");
            break;

        }
        case 2:{
            char UserName[MaxFileInPutName];
            printf("Looking who?");
            scanf("%39s",UserName);
            LocateElembyUserName(&L1,UserName);
            break;
        }
        case 3:{
            int UserId;
            printf("Looking who?");
            scanf("%d",&UserId);
            LocateElembyID(&L1,UserId);
            break;
        }
        case 4:{
            int pos;
            printf("Which position?(1-%d)", L1.TableLength);
            scanf("%d", &pos);
            if (pos >= 1 && pos <= L1.TableLength)
            {
                GetElem(&L1, pos - 1);
            }
            else
            {
                printf("Not Found\n");
            }
            break;
        }
        case 9:{
            return;
        }
    default:
        break;
    }
        }
        
}
