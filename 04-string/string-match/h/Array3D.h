//
// Created by 14266 on 2026/9/2.
//

#ifndef STRINGMATCH_ARRAY3D_H
#define STRINGMATCH_ARRAY3D_H
#include "BaseArray.h"
#include <iostream>
template<typename T>
class Array3D : public BaseArray {
private:
    T *DataArea;
    int Rows;
    int Cols;
    int Height;
    int TotalData;
    int CurDataUnitNumber;
    public:
    Array3D(int R, int C, int H)
        : Rows(R > 0 ? R : 1), Cols(C > 0 ? C : 1), Height(H > 0 ? H : 1),
          TotalData(0), CurDataUnitNumber(0) {
        // 成员初始化列表里不能用计算过的 Rows*Cols*Height，这里先算后分配
        TotalData = Rows * Cols * Height;
        DataArea = new T[TotalData];
        for (int i = 0; i < TotalData; i++) DataArea[i] = T();
    }
    ~Array3D() override {
        delete [] DataArea;
    }
    Array3D(const Array3D &Other):Rows(Other.Rows),Cols(Other.Cols),Height(Other.Height),TotalData(Other.TotalData),CurDataUnitNumber(Other.CurDataUnitNumber),DataArea(new T[Other.TotalData]){
        for (int i=0;i<CurDataUnitNumber;i++) {
            DataArea[i] = Other.DataArea[i];
        }
    }
    Array3D & operator=(const Array3D &Other) {
        if (this != &Other) {
            delete [] DataArea;
            TotalData = Other.TotalData;
            Rows = Other.Rows;
            Cols = Other.Cols;
            Height = Other.Height;
            CurDataUnitNumber = Other.CurDataUnitNumber;
            DataArea = new T[TotalData];
            for (int i=0;i<CurDataUnitNumber;i++) {
                DataArea[i] = Other.DataArea[i];
            }
        }
        return *this;
    }
    int GetLength() const override {
        return CurDataUnitNumber;   // 查询函数只返回，不打印
    }
    bool IsEmpty() const override {
        if (CurDataUnitNumber == 0) {
            return true;
        }else {
            return false;
        }
    }
    void Clear() override {
        // 逻辑清空：保留缓冲区，逐个重置并计数清零（与析构兼容，不再野指针/双重释放）
        for (int i = 0; i < CurDataUnitNumber; i++) DataArea[i] = T();
        CurDataUnitNumber = 0;
    }
    void PrintArray() const override {
        if (CurDataUnitNumber==0) {
            std::cout<<"The Array is empty"<<std::endl;
            return;
        }
        for (int i=0;i<CurDataUnitNumber;i++) {
            std::cout<<"["<<i<<"]"<<DataArea[i]<<std::endl;
        }
    }
    int ParseCoordinatesToLabels(int R,int C,int H)const {
        if (R >= 0 && R < Rows &&
        C >= 0 && C < Cols &&
        H >= 0 && H < Height &&
        (R*Cols+C)*Height+H<CurDataUnitNumber) {
            int Labels =0;
            Labels = (R*Cols+C)*Height+H;
            return Labels;
        }
        else {
            std::cout<<"Index out of range"<<std::endl;
            return -1;
        }
    }
    bool ParseCoordinatesToCoordinatesLabels(int index, int& R, int& C, int& H) const {
        if (index < 0 || index >= TotalData) {
            std::cout << "Index out of range" << std::endl;
            return false;
        }
        H = index % Height;
        C = index / Height % Cols;
        R = index / (Height * Cols);
        return true;
    }
    bool PushDataInArray(const T &Data) {
        if (CurDataUnitNumber>=TotalData) {
            std::cout<<"Array Overflow"<<std::endl;
            return false;
        }
        DataArea[CurDataUnitNumber++] = Data;
        return true;
    }
    bool PopDataInArray(T &Data) {
        if (CurDataUnitNumber == 0 ) {
            std::cout<<"Array Was Empty"<<std::endl;
            return false;
        }
        Data = DataArea[--CurDataUnitNumber];
        DataArea[CurDataUnitNumber]=T();
        return true;
    }
    bool InsertDataInArray(int Index, const T &Data) {
        if (Index<0 || Index>CurDataUnitNumber) {
            std::cout<<"Index illegal"<<std::endl;
            return false;
        }
        if (CurDataUnitNumber>=TotalData) {
            std::cout<<"Array Overflow"<<std::endl;
            return false;
        }
        for (int i=CurDataUnitNumber;i>Index;--i) {
            DataArea[i] = DataArea[i-1];
        }
        DataArea[Index] = Data;
        CurDataUnitNumber++;
        return true;
    }
    bool DeleteDataInArray(int Index,T&DeleteData)  {
        if (Index>=0 && Index<CurDataUnitNumber) {
            DeleteData = DataArea[Index];
            for (int i=Index;i<CurDataUnitNumber-1;i++) {
                DataArea[i] = DataArea[i+1];
            }
            DataArea[CurDataUnitNumber-1] = T();   // 清掉尾部残留
            CurDataUnitNumber--;
            return true;
        }else {
            std::cout << "Index out of range" << std::endl;
            return false;
        }
    }
    bool GetDataInArray(int Index, T &Data) {
        if (Index>=0 && Index<CurDataUnitNumber) {
            Data = DataArea[Index];
            return true;
        }else {
            std::cout << "Index out of range" << std::endl;
            return false;
        }
    }
    bool SetDataInArray(int Index, const T &Data) {
        if (Index>=0 && Index<CurDataUnitNumber) {
            DataArea[Index] = Data;
            return true;
        }else {
            std::cout << "Index out of range" << std::endl;
            return false;
        }
    }
};
#endif //STRINGMATCH_ARRAY3D_H
