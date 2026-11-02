#include <stdio.h>
#include "shunxubiao.h"
char ListName[MaxFileName] = "default";
SQList L1;

int main()
{

    LoadListForDisk(&L1, ListName);

    while (1)
    {
        printf("\n==== 当前表: %s(%d 条)====\n", ListName, L1.TableLength);
        printf("press 1 to see User Guide\n");
        printf("What do you want to do(1-9):\n");
        printf("Press 0 to exit the exe\n");
        int Use_Input;
        scanf("%d", &Use_Input);
        switch (Use_Input)
        {
        case 0:
            return 0;
        case 1:
            /* code */
            getchar();
            printf("User Guide\n");
            printf("2.Load list for disk\n");
            printf("3.Get the current table length\n");
            printf("4.Insert data unit\n");
            printf("5.Delete data unit\n");
            printf("6.Print current List\n");
            printf("7.Destroy current List\n");
            printf("9.Save list to disk\n");
            break;
        case 2:
        {
            char WantToReadListName[MaxFileInPutName] = {0};
            printf("What list name do you want to read?\n");
            scanf("%39s", WantToReadListName);
            SaveListToDisk(&L1, ListName);
            if (LoadListForDisk(&L1, WantToReadListName) == S_Code)
            {
                strcpy(ListName, WantToReadListName);
            }
            else
            {
                printf("Load failed, keep using current list\n");
            }
            break;
        }
        case 3:
        {
            getchar();
            Length(&L1);
            break;
        }
        case 4:
        {
            getchar();
            SQListData DataCache;
            DataCache = GetInput(&L1);
            int DataIndex = 0;
            printf("Index?\n");
            scanf("%d", &DataIndex);
            getchar();
            if (ListInsert(&L1, DataIndex, DataCache) == S_Code)
            {
                printf("Insert Compelt\n");
            }
            else
            {
                printf("Insert Faile\n");
            }

            break;
        }
        case 5:
        {
            getchar();
            SQListData DeleteDataCache;
            int DeleteIndex;
            printf("Index?\n");
            scanf("%d", &DeleteIndex);
            getchar();
            if (ListDelete(&L1, DeleteIndex, &DeleteDataCache) == S_Code)
            {
                printf("Data delete compelt,UserName:%s,UserId=%d is you delete date\n", DeleteDataCache.username, DeleteDataCache.userid);
            }
            else
            {
                printf("Delete Faile");
            }
            break;
        }
        case 6:
        {
            if (PrintList(&L1) == Erorr_Code)
            {
                printf("The currently passed-in value is not a valid list or Is was Empty list\n");
            }
            else
            {
                printf("compelt");
            }
            break;
        }
        case 7:
        {
            printf("Do you really want to delete this file?!!\n");
            printf("If You say yes press 1 ,else press0\n");
            int cache;
            scanf("%d", &cache);
            if (cache == 1)
            {
                if (DestroyList(&L1, ListName) == Erorr_Code)
                {
                    printf("Destroy ERROR");
                }
                else
                {
                    printf("compelt");
                }
            }
            break;
        }
        case 8:
        {
            SubMamu();
            break;
        }

        case 9:
        {
            getchar();
            SaveListToDisk(&L1, ListName);
            printf("Save compelt\n");
            break;
        }
        default:
            break;
        }
    }

    // printf("The current length of the sequential list%d \n", L1.TableLength);
}
