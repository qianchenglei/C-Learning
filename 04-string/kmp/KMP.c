

#include "KMP.h"
#include <string.h>
#include <stdlib.h>

bool KMP_Next(char Main[],int** NextList,int *StringLength) {
    *StringLength = strlen(Main);
    if (*StringLength == 0) {
        *NextList = NULL;
        return false;
    }
    int MatchStringLength = 0 ;
    int*Next = (int*)malloc(*StringLength*sizeof(int));
    if (Next == NULL) {
        *NextList = NULL;
        return false;
    }
    else {
        memset(Next,0,*StringLength*sizeof(int));
        Next[0]=0;
        for(int P=1;P<*StringLength;P++) {
            while (MatchStringLength > 0 && Main[P] != Main[MatchStringLength]) {
                MatchStringLength = (Next)[MatchStringLength-1];
            }
            if (Main[P] == Main[MatchStringLength]) {
                MatchStringLength++;
            }
            Next[P] = MatchStringLength;
        }
        *NextList = Next;
        return true;
    }
}

bool KMP_Search(char Main[], int **Next, int *StringLength,char *SearchModeString,int *Matchmark) {
    int ModeLength = strlen(SearchModeString);
    if (*StringLength == 0) {
        return false;
    }else {
        if (Next == NULL||*Next == NULL) {
            return false;
        }
        if (ModeLength > *StringLength||ModeLength == 0 ) {
            return false;
        }
    }
    int Matched=0;
    for (int P=0;P<*StringLength;P++) {
        while (Matched > 0 && Main[P]!=SearchModeString[Matched] ) {
            Matched = (*Next)[Matched-1];
        }
        if (Main[P] == SearchModeString[Matched]) {
            Matched++;
        }
        if (Matched == ModeLength) {
            *Matchmark=P-Matched+1;
            return true;
        }
    }
    return false;
}
