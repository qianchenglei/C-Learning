/* file: view.h */
#pragma once
#ifndef VIEW_H
#define VIEW_H

#include "linklist.h"
/* 原来包含 <conio.h>，但 view.c 只用了 getchar（标准 C），跨平台不需要它 */

// ��ͼ״̬����
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

// ��ҳ��ӡÿҳ����
#define PAGE_SIZE 7

// ��������
bool MainMenu(void);
void ClearInputBuffer(void);
void PrintAllListPaged(LinkList* list);
void WaitForEnter(void);

#endif // VIEW_H