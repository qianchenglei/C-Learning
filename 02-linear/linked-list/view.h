/* file: view.h */
#pragma once
#ifndef VIEW_H
#define VIEW_H

#include "linklist.h"
#include <conio.h>

// 视图状态常量
#define VIEW_MAIN            10
#define VIEW_INIT            11
#define VIEW_SYSMEMO         12
#define VIEW_INSERT_METHOD   13
#define VIEW_INSERT_AT_INPUT 14
#define VIEW_INSERT_H_INPUT  15
#define VIEW_INSERT_T_INPUT  16
#define VIEW_DELETE_INPUT    17
#define VIEW_SEARCH_METHOD   18
#define VIEW_SEARCH_INPUT    19
#define VIEW_PRINT_METHOD    20
#define VIEW_PRINT_PAGE      21

// 分页打印每页条数
#define PAGE_SIZE 7

// 函数声明
bool MainMenu(void);
void ClearInputBuffer(void);
void PrintAllListPaged(LinkList* list);
void WaitForEnter(void);

#endif // VIEW_H