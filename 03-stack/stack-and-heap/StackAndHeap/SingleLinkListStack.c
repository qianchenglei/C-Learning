#include "SingleLinkListStack.h"

#include <stdlib.h>

#include "Stack.h"

bool SLLS_InitStack(LinkListStack *Stack) {
    if (Stack == NULL) {
        printf("The Single Link List Stack was uninitialized");
        return false;
    }
    Stack->StackSize = 0;
    Stack->First = NULL;
    return true;
}

bool SLLS_StackEmpty(const LinkListStack *Stack) {
    if (Stack == NULL) {
        printf("The Single Link List Stack was uninitialized");
        return false;
    } else if (Stack->First == NULL && Stack->StackSize == 0) {
        printf("The Single Link List Stack is empty");
        return true;
    } else {
        printf("The Single Link List Stack is not empty");
        return false;
    }
}

bool SLLS_PushInToStack(LinkListStack *Stack, BaseDataUnit TempData) {
    if (Stack == NULL) {
        printf("The Single Link List Stack was uninitialized");
        return false;
    }
    LinkListDataUnit *NextPrint = (LinkListDataUnit *) malloc(sizeof(LinkListDataUnit));
    if (NextPrint == NULL) {
        printf("The Memory was failed");
        return false;
    }
    NextPrint->Next = Stack->First;
    NextPrint->Data = TempData;
    Stack->First = NextPrint;
    Stack->StackSize++;
    return true;
}

bool SLLS_PopOfStack(LinkListStack *Stack, BaseDataUnit *BackData) {
    if (Stack == NULL || Stack->First == NULL) {
        printf("The Single Link List Stack was uninitialized or was Empty");
        return false;
    }
    LinkListDataUnit *ToFreeNude = Stack->First;
    *BackData = ToFreeNude->Data;
    Stack->First = ToFreeNude->Next;
    Stack->StackSize--;
    free(ToFreeNude);
    return true;
}

bool SLLS_GetTopDataUnit(LinkListStack *Stack, BaseDataUnit *BackData) {
    if (Stack == NULL || Stack->First == NULL) {
        printf("The Single Link List Stack was uninitialized or was Empty");
        return false;
    }
    *BackData = Stack->First->Data;
    return true;
}

bool SLLS_CleanStack(LinkListStack *Stack) {
    if (Stack == NULL || Stack->First == NULL) {
        printf("The Single Link List Stack was uninitialized or was Empty");
        return false;
    }
    BaseDataUnit Dummy;
    while (Stack->First != NULL) {
        SLLS_PopOfStack(Stack, &Dummy);
    }
    return true;
}
