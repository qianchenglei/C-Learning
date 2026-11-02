/* file: view.c */
#include "view.h"

// 清空输入缓冲区
void ClearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 等待用户按回车键
void WaitForEnter(void) {
    printf("按回车键继续...");
    ClearInputBuffer();  // 清空可能残留的输入
    getchar();           // 等待回车
}

// 分页打印所有学生数据
void PrintAllListPaged(LinkList* list) {
    if (list == NULL) {
        printf("链表未初始化。\n");
        return;
    }

    LinkList* p = list->NextDataUnitAdd;
    LinkList* tailMarker = (list->NowListType == LIST_CIRC_SINGLE ||
        list->NowListType == LIST_CIRC_DOUBLE) ? list : NULL;
    int index = 1;
    int count = 0;

    if (p == tailMarker) {
        printf("列表为空，没有数据。\n");
        return;
    }

    ClearInputBuffer();  // 打印前清空输入缓冲区

    while (p != tailMarker) {
        PrintStudents_Date(p->StudentsData, index);
        count++;
        if (count % PAGE_SIZE == 0) {
            printf("----- 第 %d 页结束 -----\n", count / PAGE_SIZE);
            WaitForEnter();
            system("cls");  // 清屏后继续打印下一页
        }
        p = p->NextDataUnitAdd;
        index++;
    }
    // 如果最后一页不足 PAGE_SIZE，但已经打印完，不额外提示
    printf("----- 打印完成，共 %d 条记录 -----\n", count);
}

// 主菜单函数（状态机）
bool MainMenu(void) {
    static int currentView = VIEW_MAIN;
    int choice;
    Students_Data tempData;
    int index;
    int gender;
    uint64_t uuid;
    char name[MaxStudentNameSize];
    static int searchField = SEARCH_BY_UUID;  // 初始化为任意默认搜索字段

    system("cls");

    // 顶部状态栏
    printf("+------------------------------------------+\n");
    printf("| Welcome to Students Manager System       |\n");
    printf("+------------------------------------------+\n");
    if (DefaltLinkList == NULL) {
        printf("| Status: No List Initialized              |\n");
    }
    else {
        printf("| Status: ");
        switch (DefaltLinkList->NowListType) {
        case LIST_SINGLE:      printf("Single Link List           "); break;
        case LIST_DOUBLE:      printf("Double Link List           "); break;
        case LIST_CIRC_SINGLE: printf("Cycly Single Link List     "); break;
        case LIST_CIRC_DOUBLE: printf("Cycly Double Link List     "); break;
        default:               printf("Unknown Type (Error)       "); break;
        }
        printf("|\n");
    }
    printf("+------------------------------------------+\n");

    // 根据当前视图打印菜单（非数据输入视图才打印菜单选项）
    switch (currentView) {
    case VIEW_MAIN:
        printf("| 1. Initialize Link List                  |\n");
        printf("| 2. System Memo                           |\n");
        printf("| 0. Exit                                  |\n");
        break;
    case VIEW_INIT:
        printf("| [Initialize Link List]                   |\n");
        printf("| 1. Single link list                      |\n");
        printf("| 2. Double link list                      |\n");
        printf("| 3. Cycly Single link list                |\n");
        printf("| 4. Cycly Double link list                |\n");
        printf("| 0. Back                                  |\n");
        break;
    case VIEW_SYSMEMO:
        printf("| [System Memo]                            |\n");
        printf("| 1. Insert                                |\n");
        printf("| 2. Delete                                |\n");
        printf("| 3. Search                                |\n");
        printf("| 4. Print                                 |\n");
        printf("| 0. Back                                  |\n");
        break;
    case VIEW_INSERT_METHOD:
        printf("| [Insert Method]                          |\n");
        printf("| 1. Insert At Index                       |\n");
        printf("| 2. Insert At Head                        |\n");
        printf("| 3. Insert At End                         |\n");
        printf("| 0. Back                                  |\n");
        break;
    case VIEW_SEARCH_METHOD:
        printf("| [Search Field]                           |\n");
        printf("| 1. Search by UUID                        |\n");
        printf("| 2. Search by Name                        |\n");
        printf("| 3. Search by Gender                      |\n");
        printf("| 0. Back                                  |\n");
        break;
    case VIEW_PRINT_METHOD:
        printf("| [Print Method]                           |\n");
        printf("| 1. Print All (One Page)                  |\n");
        printf("| 2. Print All (Paged, %d per page)        |\n", PAGE_SIZE);
        printf("| 0. Back                                  |\n");
        break;
        // 数据输入视图不打印菜单，直接进入输入流程
    case VIEW_INSERT_AT_INPUT:
    case VIEW_INSERT_H_INPUT:
    case VIEW_INSERT_T_INPUT:
    case VIEW_DELETE_INPUT:
    case VIEW_SEARCH_INPUT:
    case VIEW_PRINT_PAGE:
        break;
    default:
        currentView = VIEW_MAIN;
        break;
    }

    // 如果不是数据输入视图，打印底部框线和读取选择
    if (currentView != VIEW_INSERT_AT_INPUT &&
        currentView != VIEW_INSERT_H_INPUT &&
        currentView != VIEW_INSERT_T_INPUT &&
        currentView != VIEW_DELETE_INPUT &&
        currentView != VIEW_SEARCH_INPUT &&
        currentView != VIEW_PRINT_PAGE) {
        printf("+------------------------------------------+\n");
        printf("> ");
        if (scanf("%d", &choice) != 1) {
            ClearInputBuffer();
            choice = -1;
        }
        else {
            ClearInputBuffer();  // 清空残留回车
        }
    }

    // 路由处理
    switch (currentView) {
    case VIEW_MAIN:
        if (choice == 1) currentView = VIEW_INIT;
        else if (choice == 2) currentView = VIEW_SYSMEMO;
        else if (choice == 0) return true;  // 退出程序
        break;

    case VIEW_INIT:
        if (choice >= 1 && choice <= 4) {
            int ret = InitLinkList(&DefaltLinkList, choice);
            if (ret == 0) {
                printf("初始化成功！\n");
            }
            else {
                printf("初始化失败！错误码 %d\n", ret);
            }
            WaitForEnter();
            currentView = VIEW_MAIN;
        }
        else if (choice == 0) {
            currentView = VIEW_MAIN;
        }
        break;

    case VIEW_SYSMEMO:
        if (choice == 1) {
            if (DefaltLinkList == NULL) {
                printf("错误：链表未初始化（错误码201）\n");
                WaitForEnter();
            }
            else {
                currentView = VIEW_INSERT_METHOD;
            }
        }
        else if (choice == 2) {
            if (DefaltLinkList == NULL) {
                printf("错误：链表未初始化（错误码201）\n");
                WaitForEnter();
            }
            else {
                currentView = VIEW_DELETE_INPUT;
            }
        }
        else if (choice == 3) {
            if (DefaltLinkList == NULL) {
                printf("错误：链表未初始化（错误码201）\n");
                WaitForEnter();
            }
            else {
                currentView = VIEW_SEARCH_METHOD;
            }
        }
        else if (choice == 4) {
            if (DefaltLinkList == NULL) {
                printf("错误：链表未初始化（错误码201）\n");
                WaitForEnter();
            }
            else {
                currentView = VIEW_PRINT_METHOD;
            }
        }
        else if (choice == 0) {
            currentView = VIEW_MAIN;
        }
        break;

    case VIEW_INSERT_METHOD:
        if (choice == 1) {
            if (DefaltLinkList == NULL) {
                printf("错误：链表未初始化（错误码201）\n");
                WaitForEnter();
            }
            else {
                currentView = VIEW_INSERT_AT_INPUT;
            }
        }
        else if (choice == 2) {
            if (DefaltLinkList == NULL) {
                printf("错误：链表未初始化（错误码201）\n");
                WaitForEnter();
            }
            else {
                currentView = VIEW_INSERT_H_INPUT;
            }
        }
        else if (choice == 3) {
            if (DefaltLinkList == NULL) {
                printf("错误：链表未初始化（错误码201）\n");
                WaitForEnter();
            }
            else {
                currentView = VIEW_INSERT_T_INPUT;
            }
        }
        else if (choice == 0) {
            currentView = VIEW_SYSMEMO;
        }
        break;

        // ========== 插入：按位 ==========
    case VIEW_INSERT_AT_INPUT:
        printf("请输入插入索引（从0开始）：");
        scanf("%d", &index); ClearInputBuffer();
        printf("请输入姓名：");
        scanf("%s", tempData.StudentName); ClearInputBuffer();
        printf("请输入 Mark：");
        scanf("%d", &tempData.StudentsMark); ClearInputBuffer();
        printf("请输入性别 (0=女, 1=男)：");
        scanf("%d", &gender); ClearInputBuffer();
        tempData.StudentGender = (bool)gender;
        tempData.StudentUUID = GenarateUUID();

        InsertAt(DefaltLinkList, index, tempData);
        WaitForEnter();
        currentView = VIEW_SYSMEMO;
        break;

        // ========== 插入：头插 ==========
    case VIEW_INSERT_H_INPUT:
        printf("请输入姓名：");
        scanf("%s", tempData.StudentName); ClearInputBuffer();
        printf("请输入 Mark：");
        scanf("%d", &tempData.StudentsMark); ClearInputBuffer();
        printf("请输入性别 (0=女, 1=男)：");
        scanf("%d", &gender); ClearInputBuffer();
        tempData.StudentGender = (bool)gender;
        tempData.StudentUUID = GenarateUUID();

        InsertEumeIntotheListByHand(DefaltLinkList, tempData);
        WaitForEnter();
        currentView = VIEW_SYSMEMO;
        break;

        // ========== 插入：尾插 ==========
    case VIEW_INSERT_T_INPUT:
        printf("请输入姓名：");
        scanf("%s", tempData.StudentName); ClearInputBuffer();
        printf("请输入 Mark：");
        scanf("%d", &tempData.StudentsMark); ClearInputBuffer();
        printf("请输入性别 (0=女, 1=男)：");
        scanf("%d", &gender); ClearInputBuffer();
        tempData.StudentGender = (bool)gender;
        tempData.StudentUUID = GenarateUUID();

        InsertEumeIntotheListByEnd(DefaltLinkList, tempData);
        WaitForEnter();
        currentView = VIEW_SYSMEMO;
        break;

        // ========== 删除 ==========
    case VIEW_DELETE_INPUT:
        printf("请输入要删除的索引（从0开始）：");
        scanf("%d", &index); ClearInputBuffer();
        {
            Students_Data deletedData;
            int ret = DeleteDataUnit(DefaltLinkList, &deletedData, index);
            if (ret == 0) {
                printf("删除成功！被删除的学生信息：\n");
                PrintStudents_Date(deletedData, index + 1);  // 打印时索引+1以符合人类习惯
            }
            else {
                printf("删除失败！错误码 %d\n", ret);
            }
            WaitForEnter();
            currentView = VIEW_SYSMEMO;
        }
        break;

        // ========== 查找字段选择 ==========
    case VIEW_SEARCH_METHOD:
        if (choice == 1) {
            searchField = SEARCH_BY_UUID;
            currentView = VIEW_SEARCH_INPUT;
        }
        else if (choice == 2) {
            searchField = SEARCH_BY_NAME;
            currentView = VIEW_SEARCH_INPUT;
        }
        else if (choice == 3) {
            searchField = SEARCH_BY_GENDER;
            currentView = VIEW_SEARCH_INPUT;
        }
        else if (choice == 0) {
            currentView = VIEW_SYSMEMO;
        }
        break;

        // ========== 查找输入 ==========
    case VIEW_SEARCH_INPUT:
        if (searchField == SEARCH_BY_UUID) {
            printf("请输入要查找的 UUID：");
            scanf("%" PRIu64, &uuid); ClearInputBuffer();
            SearchDataUnit(DefaltLinkList, SEARCH_BY_UUID, &uuid);
        }
        else if (searchField == SEARCH_BY_NAME) {
            printf("请输入要查找的姓名：");
            scanf("%s", name); ClearInputBuffer();
            SearchDataUnit(DefaltLinkList, SEARCH_BY_NAME, name);
        }
        else if (searchField == SEARCH_BY_GENDER) {
            printf("请输入要查找的性别 (0=女, 1=男)：");
            scanf("%d", &gender); ClearInputBuffer();
            bool genderBool = (bool)gender;
            SearchDataUnit(DefaltLinkList, SEARCH_BY_GENDER, &genderBool);
        }
        WaitForEnter();
        currentView = VIEW_SYSMEMO;
        break;

        // ========== 打印方式选择 ==========
    case VIEW_PRINT_METHOD:
        if (choice == 1) {
            // 一页打印全部
            PrintAllList(DefaltLinkList);
            WaitForEnter();
            currentView = VIEW_SYSMEMO;
        }
        else if (choice == 2) {
            // 分页打印
            PrintAllListPaged(DefaltLinkList);
            WaitForEnter();
            currentView = VIEW_SYSMEMO;
        }
        else if (choice == 0) {
            currentView = VIEW_SYSMEMO;
        }
        break;

        // ========== 分页打印视图（本设计中不单独使用，直接调用函数）==========
    case VIEW_PRINT_PAGE:
        // 此视图备用，当前实现直接在 VIEW_PRINT_METHOD 中处理
        currentView = VIEW_SYSMEMO;
        break;

    default:
        currentView = VIEW_MAIN;
        break;
    }

    return false;
}