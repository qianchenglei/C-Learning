// =====================================================
// StringMatch —— 动态多维数组模板（C++ OOP 版）交互测试主程序
//
// 泛型演示：启动时选择元素类型 T ∈ {int, double, std::string, char}
// 之后 Array1D<T> / Array2D<T> / Array3D<T> 都用该类型实例化：
//   1) Array1D<T>   一维数组（Push/Pop/Insert/Delete/Get/Set/拷贝…）
//   2) Array2D<T>   二维对称矩阵（压缩 Zip / 解压 UnZip，仅数值型）
//   3) Array3D<T>   三维（Push/Pop + 坐标 <-> 线性偏移 双向解析）
//   4) Array2D<T>   二维三角矩阵（判定下/上三角 + 压缩/解压闭环，仅数值型）
//
// 编译（MinGW）： g++ -std=c++17 -o StringMatch main.cpp
// Windows 自动 chcp 65001，中文不乱码。
// 注：不要 include <windows.h>（与 <iostream> 的 std::byte 在 MinGW 下歧义）。
// =====================================================
#include "h/Array1D.h"
#include "h/Array2D.h"
#include "h/Array3D.h"

#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <cstdlib>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

/* 可读的类型显示名（typeid(...).name() 是编译器的内部名，不直观） */
template <typename T> inline const char *typeName() { return "?"; }
template <> inline const char *typeName<int>()         { return "int"; }
template <> inline const char *typeName<double>()      { return "double"; }
template <> inline const char *typeName<string>()      { return "std::string"; }
template <> inline const char *typeName<char>()        { return "char"; }

/* ---------- 菜单/下标用整数读取 ---------- */
static int readInt(const char *prompt, int defaultVal = INT_MIN, bool allowEmpty = true) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        if (allowEmpty && line.empty() && defaultVal != INT_MIN) return defaultVal;
        if (line.empty()) { cout << "输入无效，请重新输入。" << endl; continue; }
        char *end = nullptr;
        long v = strtol(line.c_str(), &end, 10);
        if (end != line.c_str() && *end == '\0' && v >= INT_MIN && v <= INT_MAX) return static_cast<int>(v);
        cout << "输入无效，请重新输入一个整数。" << endl;
    }
}

/* ---------- 按类型读取一个元素值（泛型） ---------- */
template <typename T>
T readData(const char *prompt) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        std::istringstream is(line);
        T v;
        if (!(is >> v)) { cout << "输入无效，请重新输入。" << endl; continue; }
        string rest;
        if (is >> rest) { cout << "输入无效（多了多余内容），请重新输入。" << endl; continue; }
        return v;
    }
}

template <>
string readData<string>(const char *prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    // 去掉首尾空白
    size_t a = s.find_first_not_of(" \t");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

/* ================= 一维数组（泛型） ================= */
template <typename T>
static void menuArray1D() {
    int cap = readInt("容量（回车默认 10）: ", 10);
    if (cap <= 0) cap = 10;
    Array1D<T> arr(cap);
    cout << "已创建 Array1D<" << typeName<T>() << ">，容量 " << cap << "。\n";

    while (true) {
        cout << "\n[Array1D] 1 Push  2 Pop  3 Insert  4 Delete  5 Get  6 Set\n"
             << "          7 Print  8 长度  9 判空  10 清空  11 拷贝/赋值  0 返回上级\n请选择: ";
        switch (readInt("", 0, false)) {
            case 0: return;
            case 1: {
                T d = readData<T>("要插入的值: ");
                cout << (arr.PushDataInArray(d) ? "Push 成功。" : "Push 失败（已满）。") << endl;
                break;
            }
            case 2: {
                T d{};
                if (arr.PopDataInArray(d)) cout << "Pop 成功，弹出的值: " << d << endl;
                else cout << "Pop 失败（为空）。" << endl;
                break;
            }
            case 3: {
                int idx = readInt("插入位置（0..个数，可末尾）: ", 0, false);
                T d = readData<T>("要插入的值: ");
                cout << (arr.InsertDataInArray(idx, d) ? "Insert 成功。" : "Insert 失败（位置非法或已满）。") << endl;
                break;
            }
            case 4: {
                int idx = readInt("删除位置（0 基）: ", 0, false);
                T out{};
                if (arr.DeleteDataInArray(idx, out)) cout << "Delete 成功，被删值: " << out << endl;
                else cout << "Delete 失败（位置非法）。" << endl;
                break;
            }
            case 5: {
                int idx = readInt("位置（0 基）: ", 0, false);
                T out{};
                if (arr.GetDataInArray(idx, out)) cout << "arr[" << idx << "] = " << out << endl;
                else cout << "Get 失败（位置非法）。" << endl;
                break;
            }
            case 6: {
                int idx = readInt("位置（0 基）: ", 0, false);
                T d = readData<T>("新值: ");
                cout << (arr.SetDataInArray(idx, d) ? "Set 成功。" : "Set 失败（位置非法）。") << endl;
                break;
            }
            case 7: arr.PrintArray(); break;
            case 8: cout << "元素个数: " << arr.GetLength() << endl; break;
            case 9: cout << (arr.IsEmpty() ? "数组为空。" : "数组不为空。") << endl; break;
            case 10: arr.Clear(); cout << "已清空。" << endl; break;
            case 11: {
                T d = readData<T>("先压入一个值用于拷贝演示: ");
                arr.PushDataInArray(d);
                Array1D<T> copy(arr);
                Array1D<T> assign;
                assign = arr;
                cout << "--- 拷贝副本 ---\n"; copy.PrintArray();
                cout << "--- 赋值副本 ---\n"; assign.PrintArray();
                break;
            }
            default: cout << "无效选择。" << endl;
        }
    }
}

/* ================= 二维对称矩阵压缩演示（仅数值型） ================= */
template <typename T>
static void demoMatrix2D() {
    int n = readInt("矩阵阶数 n（回车默认 3）: ", 3);
    if (n <= 0 || n > 20) n = 3;

    Array2D<T> m(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            m.PushDataInArray(static_cast<T>((i + 1) * (j + 1)));   // 对称 v[i][j]==v[j][i]

    cout << "--- 原始矩阵（行优先线性打印）---\n";
    m.PrintArray();

    if (!m.IsSymmetricTriangularMatrix()) { cout << "不是对称矩阵，演示终止。" << endl; return; }

    Array1D<T> zip = m.ZipSymmetricTriangularMatrix();
    cout << "--- 压缩为下三角一维（长度 " << zip.GetLength() << " = n(n+1)/2）---\n";
    zip.PrintArray();

    Array2D<T> un = m.UnZipSymmetricTriangularMatrix(zip);
    cout << "--- 解压还原（长度 " << un.GetLength() << "）---\n";
    un.PrintArray();

    bool ok = true;
    T a{}, b{};
    for (int i = 0; i < n * n && ok; ++i)
        if (!m.GetDataInArray(i, a) || !un.GetDataInArray(i, b) || !(a == b)) ok = false;
    cout << "还原校验: " << (ok ? "与原矩阵完全一致 ✔" : "不一致 ✘") << endl;
}

/* ---------- 把 n×n 矩阵按二维网格打印（好看一点） ---------- */
template <typename T>
static void printMatrix2D(Array2D<T> &m, int n) {
    T v{};
    for (int i = 0; i < n; ++i) {
        cout << "  ";
        for (int j = 0; j < n; ++j) {
            if (!m.GetDataInArray(i * n + j, v)) { cout << "?"; }
            else { cout << v; }
            if (j != n - 1) cout << "\t";
        }
        cout << "\n";
    }
}

/* ================= 二维三角矩阵压缩演示（仅数值型） ================= */
template <typename T>
static void demoTriangularMatrix() {
    int n = readInt("矩阵阶数 n（回车默认 3）: ", 3);
    if (n <= 0 || n > 8) n = 3;   // 限制小阶数，手动输入别输到手软

    cout << "\n生成哪种矩阵？\n"
         << "  1) 下三角矩阵（右上区 i<j 全为常量 0）\n"
         << "  2) 上三角矩阵（左下区 i>j 全为常量 0）\n"
         << "  3) 全常量矩阵（退化：下/上三角两种判定都会成立）\n"
         << "  4) 手动逐格输入任意矩阵（测试判定是否稳健）\n请选择: ";
    int kind = readInt("", 1, false);
    if (kind < 1 || kind > 4) kind = 1;

    Array2D<T> m(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            T v{};
            if (kind == 1)      v = static_cast<T>((i >= j) ? ((i + 1) * (j + 1)) : 0);   // 下三角: 真数据在 i>=j
            else if (kind == 2) v = static_cast<T>((i <= j) ? ((i + 1) * (j + 1)) : 0);   // 上三角: 真数据在 i<=j
            else if (kind == 3) v = static_cast<T>(7);                                    // 全常量（退化矩阵）
            else { cout << "[" << i << "][" << j << "] = "; v = readData<T>(""); }        // 手动输入
            m.PushDataInArray(v);
        }
    }

    cout << "\n--- 原始矩阵 ---\n";
    printMatrix2D(m, n);

    // 双向判定：mode=false → 右上区(i<j)整片同值 = 下三角矩阵；mode=true → 左下区(i>j)整片同值 = 上三角矩阵
    T cLow{}, cUp{};
    bool isLow = m.UnderTriangularMatrix(cLow, false);
    bool isUp  = m.UnderTriangularMatrix(cUp, true);

    if (isLow) cout << "判定[下三角模式]: 是 ✔，常量 c = " << cLow << endl;
    else       cout << "判定[下三角模式]: 否（右上区不是整片同值）" << endl;
    if (isUp)  cout << "判定[上三角模式]: 是 ✔，常量 c = " << cUp << endl;
    else       cout << "判定[上三角模式]: 否（左下区不是整片同值）" << endl;

    // 挑一个成立的模式做压缩演示（约定：两个都成立时先用下三角）
    bool mode = false;
    if (isLow)      { mode = false; }
    else if (isUp)  { mode = true; }
    else {
        cout << "两种三角判定都不成立 → 不是（可压缩的）三角矩阵，跳过压缩演示。\n"
             << "（说明：它既不是对称/三角这类特殊矩阵，也可能只是普通矩阵）" << endl;
        return;
    }
    cout << "命中[" << (mode ? "上三角矩阵" : "下三角矩阵") << "]，开始 压缩→解压 闭环：\n";

    Array1D<T> zip = m.ZipTriangularMatrix(mode);
    cout << "--- 压缩为一维（长度 " << zip.GetLength() << " = n(n+1)/2 + 1，末格为常量 c）---\n";
    zip.PrintArray();

    Array2D<T> un = m.UnZipTriangularMatrix(zip, mode);
    cout << "--- 解压还原 ---\n";
    printMatrix2D(un, n);

    bool ok = true;
    T a{}, b{};
    for (int i = 0; i < n * n && ok; ++i)
        if (!m.GetDataInArray(i, a) || !un.GetDataInArray(i, b) || !(a == b)) ok = false;
    cout << "还原校验: " << (ok ? "与原矩阵完全一致 ✔" : "不一致 ✘") << endl;
}

/* ================= 三维（坐标解析，泛型） ================= */
template <typename T>
static void menuArray3D() {
    int R = readInt("层数 rows: ", 2, false), C = readInt("行数 cols: ", 2, false), H = readInt("列数 height: ", 2, false);
    if (R <= 0) R = 1; if (C <= 0) C = 1; if (H <= 0) H = 1;
    Array3D<T> a(R, C, H);
    cout << "已创建 Array3D<" << typeName<T>() << ">(" << R << "," << C << "," << H << ")，容量 " << R * C * H << "。\n";

    while (true) {
        cout << "\n[Array3D] 1 Push  2 Pop  3 Print  4 长度  5 判空\n"
             << "          6 清空  7 坐标→偏移  8 偏移→坐标  0 返回上级\n请选择: ";
        switch (readInt("", 0, false)) {
            case 0: return;
            case 1: {
                T d = readData<T>("要压入的值: ");
                cout << (a.PushDataInArray(d) ? "Push 成功。" : "Push 失败（已满）。") << endl;
                break;
            }
            case 2: {
                T d{};
                if (a.PopDataInArray(d)) cout << "Pop 成功，值: " << d << endl;
                else cout << "Pop 失败（为空）。" << endl;
                break;
            }
            case 3: a.PrintArray(); break;
            case 4: cout << "元素个数: " << a.GetLength() << endl; break;
            case 5: cout << (a.IsEmpty() ? "为空。" : "不为空。") << endl; break;
            case 6: a.Clear(); cout << "已清空。" << endl; break;
            case 7: {
                int r = readInt("层 r: ", 0, false), c = readInt("行 c: ", 0, false), h = readInt("列 h: ", 0, false);
                int off = a.ParseCoordinatesToLabels(r, c, h);
                cout << "(" << r << "," << c << "," << h << ") -> 偏移 " << off << endl;
                break;
            }
            case 8: {
                int idx = readInt("线性偏移 index: ", 0, false);
                int r = -1, c = -1, h = -1;
                if (a.ParseCoordinatesToCoordinatesLabels(idx, r, c, h))
                    cout << "偏移 " << idx << " -> (" << r << "," << c << "," << h << ")" << endl;
                break;
            }
            default: cout << "无效选择。" << endl;
        }
    }
}

/* ---------- 类型分发 ---------- */
enum ElemType { T_INT = 1, T_DOUBLE = 2, T_STRING = 3, T_CHAR = 4 };

template <typename T>
static void runAll() {
    constexpr bool numeric = std::is_arithmetic_v<T>;   // 二维压缩演示仅数值型可用
    while (true) {
        cout << "\n选择容器:\n"
             << "  1) Array1D<" << typeName<T>() << ">   一维数组（完整增删改查）\n"
             << "  2) Array2D<" << typeName<T>() << ">   二维对称矩阵（压缩/解压演示" << (numeric ? "" : "，仅数值型") << "）\n"
             << "  3) Array3D<" << typeName<T>() << ">   三维（坐标 <-> 偏移 解析）\n"
             << "  4) Array2D<" << typeName<T>() << ">   二维三角矩阵（判定+压缩/解压演示" << (numeric ? "" : "，仅数值型") << "）\n"
             << "  0) 返回/退出\n请选择: ";
        switch (readInt("", 0, false)) {
            case 0: return;
            case 1: menuArray1D<T>(); break;
            case 2:
                if constexpr (numeric) demoMatrix2D<T>();
                else cout << "二维对称阵演示需要数值类型，当前类型不适用，请选 1D/3D。" << endl;
                break;
            case 3: menuArray3D<T>(); break;
            case 4:
                if constexpr (numeric) demoTriangularMatrix<T>();
                else cout << "二维三角阵演示需要数值类型，当前类型不适用，请选 1D/3D。" << endl;
                break;
            default: cout << "无效选择。" << endl;
        }
    }
}

int main() {
#ifdef _WIN32
    std::system("chcp 65001 > nul");
#endif
    cout << "===== StringMatch · 动态数组（C++ 模板 OOP）交互测试 =====" << endl;
    while (true) {
        cout << "\n选择元素类型 T:\n"
             << "  1) int\n  2) double\n  3) std::string\n  4) char\n  0) 退出\n请选择: ";
        switch (readInt("", 0, false)) {
            case 0: cout << "再见。" << endl; return 0;
            case T_INT:    runAll<int>(); break;
            case T_DOUBLE: runAll<double>(); break;
            case T_STRING: runAll<string>(); break;
            case T_CHAR:   runAll<char>(); break;
            default: cout << "无效选择。" << endl;
        }
    }
}
