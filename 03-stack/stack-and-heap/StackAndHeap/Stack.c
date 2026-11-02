#include "Stack.h"

#include <stdlib.h>

bool InitStack(Stack *Stack) {
    if (Stack == NULL) {
        return false;
    } else {
        Stack->TopPrint = -1;
        return true;
    }
}

bool StackEmpty(const Stack *Stack) {
    if (Stack == NULL) {
        printf("This Stark Was Uninitialized");
        return false;
    } else if (Stack->TopPrint == -1) {
        return true;
    } else {
        return false;
    }
}

bool PushInToStack(Stack *Stack, BaseDataUnit InputDataUnit) {
    if (Stack == NULL) {
        printf("This Stark Was Uninitialized");
        return false;
    } else if (Stack->TopPrint == MaxDataSize - 1) {
        printf("This Stark Was Fail");
        return false;
    } else {
        Stack->Data[++Stack->TopPrint] = InputDataUnit;
        return true;
    }
}

bool PopOfStack(Stack *Stack, BaseDataUnit *BackDataUnit) {
    if (Stack == NULL) {
        printf("This Stark Was Uninitialized");
        return false;
    } else if (StackEmpty(Stack) == true) {
        printf("This Stark Was Empty");
        return false;
    } else {
        *BackDataUnit = Stack->Data[(Stack->TopPrint)--];
        return true;
    }
}

bool GetTopDataUnit(Stack *Stack, BaseDataUnit *BackDataUnit) {
    if (Stack == NULL) {
        printf("This Stark Was Uninitialized");
        return false;
    } else if (StackEmpty(Stack) == true) {
        printf("This Stark Was Empty");
        return false;
    } else {
        *BackDataUnit = Stack->Data[Stack->TopPrint];
        return true;
    }
}

bool DestroyStack(Stack *Stack) {
    Stack->TopPrint = -1;
    return true;
}
