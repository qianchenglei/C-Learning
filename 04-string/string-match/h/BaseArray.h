//
// Created by 14266 on 2026/9/2.
//

#ifndef STRINGMATCH_BASEARRAY_H
#define STRINGMATCH_BASEARRAY_H
#include <string>


class BaseArray {
    public:
    virtual ~BaseArray(){};
    virtual int GetLength()const = 0;
    virtual bool IsEmpty()const = 0;
    virtual void Clear()=0;
    virtual void PrintArray()const = 0;
};



#endif //STRINGMATCH_BASEARRAY_H
