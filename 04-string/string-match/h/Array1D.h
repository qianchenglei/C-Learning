// //
// // Created by 14266 on 2026/8/29.
// //
//
#ifndef STRINGMATCH_ARRAY_H
#define STRINGMATCH_ARRAY_H
#include <iostream>

#include "BaseArray.h"
using namespace std;
template <typename  T>
class Array1D :public BaseArray {
    private:
        T *DataArae;
        int TotalSize;
        int CurDataUnitNumber;
    public:
    Array1D(int To = 50):DataArae(new T[To]), TotalSize(To), CurDataUnitNumber(0) {
        for (int i=0;i<To;i++) {
            DataArae[i] = T();
        }
    };
    ~Array1D() override{
        delete [] DataArae;
    };
    Array1D(const Array1D &other) :DataArae(new T [other.TotalSize]), TotalSize(other.TotalSize), CurDataUnitNumber(other.CurDataUnitNumber) {
            for (int i=0;i<CurDataUnitNumber;i++) {
                DataArae[i]=other.DataArae[i];
            }
        }

    Array1D &operator=(const Array1D &other) {
        if (this!=&other) {
            delete [] DataArae;
            TotalSize=other.TotalSize;
            CurDataUnitNumber=other.CurDataUnitNumber;
            DataArae=new T [TotalSize];
            for (int i=0;i<CurDataUnitNumber;i++) {
                DataArae[i]=other.DataArae[i];
            }
        }
        return *this;
    };

    void PrintArray()const override {
        if (CurDataUnitNumber==0) {
            cout<<"Array Was Empty"<<endl;
            return;
        }
        for (int i=0;i<CurDataUnitNumber;i++) {
            cout<<"["<<i<<"]:"<<DataArae[i]<<endl;
        }

    };
    int GetLength()const override {
        return CurDataUnitNumber;   // 查询函数只返回，不打印
    }
    bool PushDataInArray(const T& Data){
        if (CurDataUnitNumber>=TotalSize) {
            cout<<"Array Overflow"<<endl;
            return false;
        }
        DataArae[CurDataUnitNumber++] = Data;
        return true;

    };
    bool PopDataInArray(T& BackData){
        if (CurDataUnitNumber==0) {
            cout<<"Array Was Empty"<<endl;
            return false;
        }
        BackData=DataArae[--CurDataUnitNumber];
        DataArae[CurDataUnitNumber]=T();

        return true;
    }
    void Clear() override {
        for (int i=0;i<CurDataUnitNumber;i++) {
            DataArae[i]=T();
        }
        CurDataUnitNumber=0;

    }
    bool IsEmpty()const override {
        if (CurDataUnitNumber==0) {
            return true;
        }else {
            return false;
        }
    }
    bool InsertDataInArray(int index, const T& Data) {
        // 1. 检查索引是否合法：允许在 [0, CurDataUnitNumber] 范围内插入
        if (index < 0 || index > CurDataUnitNumber) {
            cout << "Index out of range" << endl;
            return false;
        }
        // 2. 检查数组是否已满
        if (CurDataUnitNumber >= TotalSize) {
            cout << "Array Overflow" << endl;
            return false;
        }

        // 3. 从最后一个元素开始，逐个后移，直到 index 位置
        for (int i = CurDataUnitNumber; i > index; --i) {
            DataArae[i] = DataArae[i - 1];
        }

        // 4. 插入新元素
        DataArae[index] = Data;

        // 5. 更新元素个数
        CurDataUnitNumber++;

        return true;
    }
    bool DeleteDataInArray(int index, T& deletedData) {
        if (index >= 0 && index <= CurDataUnitNumber-1) {
            deletedData = DataArae[index];
            for (int i = index; i < CurDataUnitNumber-1; ++i) {
                DataArae[i] = DataArae[i + 1];
            }
            CurDataUnitNumber--;
            return true;
        }else {
            cout << "Index out of range" << endl;
            return false;
        }
    }
    bool GetDataInArray(int index, T & Data) const {
        if (index < 0 || index >= CurDataUnitNumber) {
            cout << "Index out of range" << endl;
            return false;
        }
        Data=DataArae[index];
        return true;
    }
    bool SetDataInArray(int index, const T& Data) {
        if (index < 0 || index >= CurDataUnitNumber) {
            cout << "Index out of range" << endl;
            return false;
        }
        DataArae[index]=Data;
        return true;
    }
};

// #define OneDimensional 1
// #define TwoDimensional 2
// #define ThreeDimensional 3
// #define DefaultMaxSingleRowArraysize 50
// ArrayHard* InitArray(int Dimension,int SingDimensionalSize,int i,int j,int k);
//
// bool Tool_GetAndEffectiveIndex(ArrayHard* Array,int i,int j,int k,int*Offsetdata);

// bool SearchDataInArray(ArrayHard* Array,int Data,int*ReturnData);
// bool DeleteDataInArray(ArrayHard *Array, int i,int j,int k, int *ReturnData);
// bool InsertDataInArray(ArrayHard *Array, int i,int j,int k, int Date);
// bool GetDataInArray(ArrayHard* Array,int i,int j,int k,int *ReturnData);
// bool SetDataInArray(ArrayHard* Array,int i,int j,int k,int SetData);
// bool DestroyArray(ArrayHard* Array,int i,int j,int k);
#endif //STRINGMATCH_ARRAY_H
