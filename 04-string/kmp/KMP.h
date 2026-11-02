//
// Created by 14266 on 2026/9/8.
//

#ifndef KMP_KMP_H
#define KMP_KMP_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool KMP_Next(char Main[],int** Next,int *StringLength);
bool KMP_Search(char Main[],int** Next,int *StringLength,char *SearchModeString,int *Matchmark);





#endif //KMP_KMP_H
