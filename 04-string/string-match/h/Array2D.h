//
// Created by 14266 on 2026/9/2.
//

#ifndef STRINGMATCH_ARRAY2D_H
#define STRINGMATCH_ARRAY2D_H
#include <iostream>
#include "Array1D.h"
#include "BaseArray.h"
using namespace std;

template<typename T>
class Array2D : public BaseArray {
private:
    T *DataArea;
    int Rows;
    int Cols;
    int TotalData;
    int CurDataUnitNumber;

public:
    Array2D(int R, int C) : DataArea(new T[R * C]), Rows(R), Cols(C), TotalData(R * C), CurDataUnitNumber(0) {
        for (int i = 0; i < TotalData; i++) {
            DataArea[i] = T();
        }
    }

    ~Array2D() override {
        delete [] DataArea;
    }

    Array2D(const Array2D &Other) : Rows(Other.Rows), Cols(Other.Cols), TotalData(Other.TotalData),
                                    CurDataUnitNumber(Other.CurDataUnitNumber), DataArea(new T[Other.TotalData]) {
        for (int i = 0; i < CurDataUnitNumber; i++) {
            DataArea[i] = Other.DataArea[i];
        }
    }

    Array2D &operator=(const Array2D &Other) {
        if (this != &Other) {
            delete [] DataArea;
            TotalData = Other.TotalData;
            CurDataUnitNumber = Other.CurDataUnitNumber;
            DataArea = new T[TotalData];
            Rows = Other.Rows;
            Cols = Other.Cols;
            for (int i = 0; i < TotalData; i++) {
                DataArea[i] = Other.DataArea[i];
            }
        }
        return *this;
    }

    int GetLength() const override {
        return CurDataUnitNumber; // 查询函数只返回，不打印
    }

    bool IsEmpty() const override {
        if (CurDataUnitNumber == 0) {
            return true;
        } else {
            return false;
        }
    }

    void Clear() override {
        for (int i = 0; i < CurDataUnitNumber; i++) DataArea[i] = T();
        CurDataUnitNumber = 0;
    }

    void PrintArray() const override {
        if (CurDataUnitNumber == 0) {
            cout << "The Array is empty" << endl;
            return;
        }
        for (int i = 0; i < CurDataUnitNumber; i++) {
            cout << "[" << i << "]" << DataArea[i] << endl;
        }
    }

    int ParseCoordinatesToLabels(int R, int C) const {
        if (R >= 0 && R < Rows &&
            C >= 0 && C < Cols &&
            R * Cols + C < CurDataUnitNumber) {
            int Labels = 0;
            Labels = (R * Cols + C);
            return Labels;
        } else {
            cout << "Index out of range" << endl;
            return -1;
        }
    }

    void ParseCoordinatesToCoordinatesLabels(int index, int rows, int cols, int &R, int &C) const {
        C = index % cols;
        R = index / cols;
    }

    bool PushDataInArray(const T &Data) {
        if (CurDataUnitNumber >= TotalData) {
            cout << "Array Overflow" << endl;
            return false;
        }
        DataArea[CurDataUnitNumber++] = Data;
        return true;
    }

    bool PopDataInArray(T &Data) {
        if (CurDataUnitNumber == 0) {
            cout << "Array Was Empty" << endl;
            return false;
        }
        Data = DataArea[--CurDataUnitNumber];
        DataArea[CurDataUnitNumber] = T();
        return true;
    }

    bool InsertDataInArray(int Index, const T &Data) {
        if (Index < 0 || Index > CurDataUnitNumber) {
            cout << "Index illegal" << endl;
            return false;
        }
        if (CurDataUnitNumber >= TotalData) {
            cout << "Array Overflow" << endl;
            return false;
        }
        for (int i = CurDataUnitNumber; i > Index; --i) {
            DataArea[i] = DataArea[i - 1];
        }
        DataArea[Index] = Data;
        CurDataUnitNumber++;
        return true;
    }

    bool DeleteDataInArray(int Index, T &DeleteData) {
        if (Index >= 0 && Index <= CurDataUnitNumber - 1) {
            DeleteData = DataArea[Index];
            for (int i = Index; i < CurDataUnitNumber - 1; i++) {
                DataArea[i] = DataArea[i + 1];
            }
            CurDataUnitNumber--;
            return true;
        } else {
            cout << "Index out of range" << endl;
            return false;
        }
    }

    bool GetDataInArray(int Index, T &Data) {
        if (Index >= 0 && Index <= CurDataUnitNumber - 1) {
            Data = DataArea[Index];
            return true;
        } else {
            cout << "Index out of range" << endl;
            return false;
        }
    }

    bool SetDataInArray(int Index, const T &Data) {
        if (Index >= 0 && Index < TotalData) {
            DataArea[Index] = Data;
            return true;
        } else {
            cout << "Index out of range" << endl;
            return false;
        }
    }

    bool IsSymmetricTriangularMatrix() {
        if (Rows == Cols) {
            if (CurDataUnitNumber == TotalData) {
                for (int i = 0; i < Rows; i++) {
                    for (int j = 0; j < Cols; j++) {
                        if (DataArea[i * Cols + j] != DataArea[j * Cols + i]) {
                            cout << "Matrix not Symmetric" << endl;
                            return false;
                        }
                    }
                }
                return true;
            } else {
                cout << "Matrix Not fail " << endl;
                return false;
            }
        } else {
            cout << "Matrix Not square " << endl;
            return false;
        }
    }

    Array1D<T> ZipSymmetricTriangularMatrix() {
        if (!IsSymmetricTriangularMatrix()) {
            return Array1D<T>(0);
        }
        int ZipSize = Rows * (Rows + 1) / 2;
        Array1D<T> Zip(ZipSize);
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j <= i; ++j) {
                Zip.PushDataInArray(DataArea[i * Cols + j]);
            }
        }
        return Zip;
    }

    Array2D<T> UnZipSymmetricTriangularMatrix(const Array1D<T> &Zipped) {
        int ZR = Rows; // 矩阵维度
        int expectedSize = ZR * (ZR + 1) / 2;

        // 检查压缩数组长度是否匹配
        if (Zipped.GetLength() != expectedSize) {
            cout << "Compressed data size mismatch" << endl;
            return Array2D<T>(0, 0);
        }

        Array2D<T> UnZip(ZR, ZR); // 创建结果矩阵

        int k = 0; // 压缩数组索引
        for (int i = 0; i < ZR; ++i) {
            for (int j = 0; j <= i; ++j) {
                T value;
                // 从压缩数组中取出第 k 个元素
                if (!Zipped.GetDataInArray(k, value)) {
                    cout << "Failed to read compressed data" << endl;
                    return Array2D<T>(0, 0);
                }
                // 设置对称位置（使用一维索引）
                int idx1 = i * ZR + j;
                int idx2 = j * ZR + i;
                // 注意：SetDataInArray 不是 const 函数，且边界检查需要修改
                if (!UnZip.SetDataInArray(idx1, value) || !UnZip.SetDataInArray(idx2, value)) {
                    cout << "Failed to set data in matrix" << endl;
                    return Array2D<T>(0, 0);
                }
                ++k;
            }
        }
        UnZip.CurDataUnitNumber = ZR * ZR; // 补：解压把整矩阵写满，计数要同步，否则还原结果看起来是空的
        return UnZip;
    }

    bool UnderTriangularMatrix(T &UselessData, bool DetectMode) {
        if (Rows == Cols && CurDataUnitNumber == TotalData && Rows != 0) {
            if (Rows == 1) { UselessData = DataArea[0]; return true; }   // ① 退化先处理

            switch (DetectMode) {
                case false: {                            // 右上区(i<j)整片同值 → 下三角矩阵
                    T Mark = DataArea[0 * Cols + 1];     // ② n>=2 了才安全取 (0,1)
                    for (int i = 0; i < Rows; i++)
                        for (int j = i + 1; j < Cols; j++)
                            if (DataArea[i * Cols + j] != Mark) return false;
                    UselessData = Mark;
                    return true;
                }
                case true: {                             // 左下区(i>j)整片同值 → 上三角矩阵
                    T Mark = DataArea[1 * Cols + 0];     // ② n>=2 了才安全取 (1,0)
                    for (int i = 1; i < Rows; i++)
                        for (int j = 0; j < i; j++)
                            if (DataArea[i * Cols + j] != Mark) return false;
                    UselessData = Mark;
                    return true;
                }
            }
        }
        return false;
    }

    Array1D<T> ZipTriangularMatrix(bool DetectMode) {
        T Constant{};                                  // T 可能是任意类型，不能 = 0，用值初始化
        if (!UnderTriangularMatrix(Constant, DetectMode)) {
            return Array1D<T>(0);
        }else {
            Array1D<T> Ziped(Rows * (Rows + 1) / 2 + 1);
            switch (DetectMode) {
                case false: {
                    for (int i = 0; i < Rows; ++i) {
                        for (int j = 0; j <= i; ++j) {
                            Ziped.PushDataInArray(DataArea[i * Cols + j]);   // 直接下标即可
                        }
                    }
                    Ziped.PushDataInArray(Constant);
                    return Ziped;
                }
                case true: {
                    for (int i = 0; i < Rows; ++i) {
                        for (int j = i; j < Rows; ++j) {
                            Ziped.PushDataInArray(DataArea[i * Cols + j]);
                        }
                    }
                    Ziped.PushDataInArray(Constant);
                    return Ziped;
                }
                default: {
                    return Array1D<T>(0);
                }
            }
        }
    }
    Array2D<T> UnZipTriangularMatrix(const Array1D<T> &Zipped, bool DetectMode) {
        int n = Rows;
        int expect = n * (n + 1) / 2 + 1;              // 三角区 + 常量格

        if (Zipped.GetLength() != expect) {            // ① 长度不对就拒绝，别掉出函数
            cout << "压缩数据长度不匹配(期望 " << expect << ")。" << endl;
            return Array2D<T>(0, 0);
        }

        T c{};
        if (!Zipped.GetDataInArray(expect - 1, c)) {   // ② 只读末格 = 常量，不 Pop
            cout << "读取常量 c 失败。" << endl;
            return Array2D<T>(0, 0);
        }

        Array2D<T> UnZip(n, n);
        int k = 0;                                     // ③ 真数据游标：指向 Zipped 前半段
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                bool isReal = (DetectMode == false) ? (j <= i) : (j >= i);   // ④ 按 mode 分
                if (isReal) {
                    T v;
                    if (!Zipped.GetDataInArray(k++, v)) {   // ⑤ 从 Zipped 取，不是 DataArea！
                        cout << "压缩数据不足。" << endl;
                        return Array2D<T>(0, 0);
                    }
                    UnZip.PushDataInArray(v);
                } else {
                    UnZip.PushDataInArray(c);              // 常量区整片填 c
                }
            }
        }
        return UnZip;   // Push 了恰好 n² 次 → 计数自动=n²，无需手动同步 ✔
    }
};

#endif //STRINGMATCH_ARRAY2D_H
