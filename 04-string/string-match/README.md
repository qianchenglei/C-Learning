# StringMatch —— 动态多维数组模块（C 版 + C++ OOP 重写）

## 是什么

这个工程讲的是一个"动态多维数组模块"的演进史：先用 **C** 写了一个能在逻辑上模拟一维 / 二维 / 三维、底层却是**一段连续一维内存**的数组模块（`ArrayHard`，配套 `Tool_GetAndEffectiveIndex` 之类的索引映射工具函数）；然后把它用 **C++ 的面向对象思想**（封装 + 继承 + 多态）+ **模板**重新写了一遍，不再绑死 `int`，并抽象出可扩展的类体系。

**当前源码的实际完成度（对照文件核实过）：**

- **C 版（Array.c / publicData.h / ArrayHard）：源码已不在工程里。** `c\` 目录存在但为空，`h\` 下也没有 `publicData.h`、`Array.h`。C 版的痕迹只剩两处：`h\Array1D.h` 文件末尾一大段被注释掉的 C 版 API 声明（`InitArray`、`Tool_GetAndEffectiveIndex`、`SearchDataInArray`、`DestroyArray` 等），以及博客中对应的一篇总结文章。也就是说，C 版目前只能"考古"，无法在此工程内编译运行。
- **C++ 版：`BaseArray`（纯虚基类）+ `Array1D`（模板一维数组，实现完整）已可用；`Array2D` / `Array3D` 只有构造 + 析构的骨架。**
- **当前测试入口是 `main.cpp`（不是 main.c）**，`CMakeLists.txt` 也只编译 `main.cpp`，里面只演示了 `Array1D<int>` 通过 `BaseArray*` 多态调用的用法；没有用到 `Array2D` / `Array3D`——这也和它们目前无法实例化（见"已知问题"）相吻合。

## 文件结构

| 文件 | 一句话说明 |
| --- | --- |
| `CMakeLists.txt` | 构建脚本：只编译 `main.cpp`，C++20，`BaseArray.h` 被重复列了一次（无害），没有引用 `c\` 下的任何文件 |
| `main.cpp` | 当前测试入口：构造 `Array1D<int>`，演示入栈、多态取长度 / 判空 / 打印 / 清空，以及按索引插入 |
| `h\BaseArray.h` | C++ 版抽象基类：一个空实现的虚析构 + 4 个纯虚函数（`GetLength` / `IsEmpty` / `Clear` / `PrintArray`），定义了"数组"的统一接口 |
| `h\Array1D.h` | 模板一维数组 `Array1D<T>`：成员函数最全的一份（入栈出栈、按索引增删改查），实现了深拷贝与 Rule of Three；末尾残留一大段被注释的 C 版 API 声明 |
| `h\Array2D.h` | 模板二维数组 `Array2D<T>`：**只写了构造函数和析构函数**，未实现基类纯虚函数 |
| `h\Array3D.h` | 模板三维数组 `Array3D<T>`：**只写了构造函数和析构函数**，未实现基类纯虚函数，且构造里 `new T(...)` 的写法有 bug（见下） |
| `c\`（空目录） | C 版源码原先所在的位置，现在没有任何文件 |

## 核心设计

### C 版的关键点（据 `Array1D.h` 末尾残留注释与博客文章，源码本身已不在仓库）

- **一维底层**：不管逻辑上是几维，内存都是一段连续空间（博客记载为连续 `int` 内存），由 `ArrayHard` 结构体管理。
- **dims / 多维抽象**：用"维数 + 各维尺寸"描述逻辑形状（残留注释里的 `InitArray(int Dimension, int SingDimensionalSize, int i, int j, int k)` 可看出三维下标 i/j/k 的传参约定）。
- **`Tool_GetAndEffectiveIndex`**：把逻辑多维下标换算成底层一维偏移的核心工具函数，是"真正索引映射"的关键（博客文章标题即以此命名）。
- 配套生命周期管理（`InitArray` / `DestroyArray`）与增删改查、查找等 API（`InsertDataInArray` / `DeleteDataInArray` / `GetDataInArray` / `SetDataInArray` / `SearchDataInArray`）。

### C++ 版的关键点

- **`BaseArray` 纯虚接口**：把"数组"应提供的能力（长度、判空、清空、打印）固化成 4 个纯虚函数 + 虚析构，派生类各自实现——这是多态的根基。`main.cpp` 里 `BaseArray *base = &arr;` 正是通过基类指针调用派生类实现的演示。
- **`Array1D` 模板泛化**：`template <typename T>` 把原来绑死 `int` 的 C 模块泛型化；内部仍是裸指针 `T*` 指向的连续堆内存 + 容量 `TotalSize` + 已用单元数 `CurDataUnitNumber`，满则拒绝入栈并打印 `Array Overflow`（**固定容量，不自动扩容**）。
- **深拷贝**：拷贝构造函数与拷贝赋值运算符都做了"新建 `new T[TotalSize]` + 逐元素拷贝"的深拷贝，拷贝赋值还带 `this != &other` 自赋值保护。
- **Rule of Three**：`Array1D` 显式提供了析构、拷贝构造、拷贝赋值三者（类里有裸指针成员，必须如此）；`Array2D` / `Array3D` 则**没有**这套拷贝控制。
- 文件头部注释掉了一堆 `#define OneDimensional 1` 之类的 C 风格宏与函数声明，是 C 版向 C++ 版改造时留下的历史痕迹。

## 当前状态与已知问题

以下问题全部是在读源码时亲眼看到的：

1. **`Array3D` 用 `new T(R*C*H)` 而非 `new T[R*C*H]`（最严重）**。`h\Array3D.h` 第 17 行圆括号表示**只分配一个 T 对象**并以 `R*C*H` 作为它的初值，而不是分配 `R*C*H` 个元素；随后第 18–20 行循环却对这块"只有 1 个元素"的堆块写入 `Totals` 个单元——直接越界写、堆破坏；析构里 `delete []` 与标量 `new` 也不匹配（未定义行为）。这个类现在根本无法安全使用。
2. **`Array2D` / `Array3D` 没实现基类纯虚函数 → 抽象类，无法实例化**。两个类都只写了构造 + 析构，`BaseArray` 的 `GetLength` / `IsEmpty` / `Clear` / `PrintArray` 一个都没 override，所以 `Array2D<int> a(2,3)` 这类代码编译都过不了；`main.cpp` 也刻意没碰它们。
3. **成员名拼写不一致**：`Array1D` 的数据成员叫 `DataArae`（拼写错误，应为 `DataArea`），而 `Array2D` / `Array3D` 用的是 `DataArea`；`Array2D` 里还有 `TotelData`（应为 `TotalData`）。
4. **`Array1D.h` 的头文件守卫是 `STRINGMATCH_ARRAY_H`**（沿用旧文件名 `Array.h`），与文件名 `Array1D.h` 不符，存在同名守卫冲突的隐患。
5. **`GetLength()` 是带打印副作用的"查询"函数**：它内部先 `cout << "Length:..."` 再返回值；而 `main.cpp` 里又在外层再 `std::cout << "Length: " << base->GetLength()`，于是每调一次控制台会输出两行 Length，属于多态演示代码里的小瑕疵。
6. **`Array1D` 拷贝构造只复制了 `CurDataUnitNumber` 个元素**：堆上 `TotalSize` 个槽位里，剩下的没有初始化成 `T()`（默认构造时是全部初始化过的），目前由于多余槽位不可被读到所以不致命，但拷贝后"活动区之外的槽位状态"与源对象不一致，是规范性问题。
7. **容量 / 尺寸参数无校验**：`Array1D(To)`、`Array2D(R, C)`、`Array3D(R, C, H)` 都不检查参数是否为 0 / 负数，也拒绝自动扩容，满员时只能打印并返回 `false`。
8. **`Array2D` / `Array3D` 缺少 Rule of Three**：类里有裸指针成员却没有拷贝构造 / 拷贝赋值，一旦将来补全纯虚函数、可以被实例化，默认浅拷贝会带来双重 delete。
9. **`main.cpp` 用反斜杠包含头文件**：`#include "h\Array1D.h"` 在 Windows 编译器下能用，但移植到 Linux/GCC 这类环境就可能找不到头文件（`CMakeLists.txt` 里写的是正斜杠 `h/Array1D.h`，风格不一致）。
10. **`CMakeLists.txt` 把 `h/BaseArray.h` 列了两次**（第 12、13 行重复），无害但属冗余。
11. **C 版源码整体缺失**：`c\` 为空，README 无法对照 C 版真实代码，只能依据残留注释和博客还原其设计（见"核心设计"）。

## 延伸阅读

本工程在博客（`D:\zikao\blog\`）里有两篇配套总结文章，与两个版本一一对应：

- `blog\posts\ds-stringmatch-array.md`——《多维数组模块（StringMatch）：真正的索引映射与完整增删改查》，记录 **C 版**（`ArrayHard` + `Tool_GetAndEffectiveIndex`）的重写设计；
- `blog\posts\Ds _mdArraytoCpp.md`——《C 语言多维数组拓展——Cpp 的封装继承多态》，记录 **C++ 版**重写后的现状与遗留问题。

（本文档只读源码写成，未改动这两篇文章。）

---

**总结**：这个工程目前是"C++ 版半成品 + C 版空壳"的状态——`main.cpp` 能跑通 `Array1D` 的完整增删改查与多态调用，说明 OOP 改造的核心思路已经落地；但 `Array2D`/`Array3D` 只是两具无法实例化的骨架，且 C 版源码已不在仓库里，只能靠残留注释和博客考古。最该修的问题有两个：一是 `Array3D` 构造函数里 `new T(...)` 圆括号写成方括号 `new T[...]` 的堆越界 bug，二是给 `Array2D`/`Array3D` 补上基类纯虚函数与 Rule of Three，让它们真正能用、可安全拷贝。
