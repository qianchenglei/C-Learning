cmake_minimum_required(VERSION 3.20)

project(C_Learning LANGUAGES C CXX)

# ============================================================
# 全局设置
# ============================================================
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 可执行文件集中输出到 build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 给 clangd / LSP 用：生成 compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 统一开警告，但不开 -Werror。
# 理由：学习项目要看得见警告，但不能因为一个未用参数就构建失败。
if (MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra)
endif()

# ============================================================
# common：基础设施库
#   栈、队列等"容器层"代码只写一份，谁需要谁链接。
#   用法：target_link_libraries(目标名 PRIVATE common)
#   include 路径已设为 PUBLIC，链接后直接 #include "stack.h" 即可。
# ============================================================
add_library(common STATIC
    common/stack.c
    common/queue.c
)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)

enable_testing()

# ============ 01 C 语言基础 ============
add_executable(01_ccc
    01-basics/ccc/main.c
    01-basics/ccc/shunxubiao.c
)

# ============ 02 线性表 ============
add_executable(02_single_linked_list
    02-linear/single-linked-list/main.c
    02-linear/single-linked-list/danlianbiao.c
)

add_executable(02_linked_list
    02-linear/linked-list/main.c
    02-linear/linked-list/linklist.c
    02-linear/linked-list/view.c
)

# ============ 03 栈、队列 ============
add_executable(03_stack_and_heap
    03-stack/stack-and-heap/StackAndHeap/StackAndHeap.c
    03-stack/stack-and-heap/StackAndHeap/Stack.c
    03-stack/stack-and-heap/StackAndHeap/Queue.c
    03-stack/stack-and-heap/StackAndHeap/LinkListQueue.c
    03-stack/stack-and-heap/StackAndHeap/SingleLinkListStack.c
)

# ============ 04 串 ============
add_executable(04_kmp
    04-string/kmp/main.c
    04-string/kmp/KMP.c
)

add_executable(04_string_match
    04-string/string-match/main.cpp
)
target_include_directories(04_string_match PRIVATE 04-string/string-match)

# ============ 05 树 ============
add_executable(05_sq_bi_tree
    05-tree/sq-bi-tree/main.c
    05-tree/sq-bi-tree/SqBinaryTree.c
)

add_executable(05_linked_bi_tree
    05-tree/linked-bi-tree/main.c
    05-tree/linked-bi-tree/LinkedOfBinaryTree.c
    05-tree/linked-bi-tree/Stack.c
    common/queue.c              # 层序遍历用：void* 通用循环队列
)
# 只引 common 的头路径，不链接 common 静态库：
# 本目标自带 Stack.c，链接 common 会与 stack.c 的符号冲突。
target_include_directories(05_linked_bi_tree PRIVATE common)

# 05_tree_and_forest 暂时不参与构建：
# 05-tree/TreeAndForest/main.c 目前是空文件（0 字节），没有 main()，链接必定失败。
# 写完入口函数后，把下面三行取消注释即可。
# add_executable(05_tree_and_forest
#     05-tree/TreeAndForest/main.c
#     05-tree/TreeAndForest/TreeAndForest.c
# )

# ============ 06 图 ============
# 源文件（.c 参与编译）
set(GRAPH_SOURCES
    06-Graph/ALGraph.c
    06-Graph/MGraph.c
    06-Graph/UnionFindDisjointSet.c
    06-Graph/Main.c
    06-Graph/ai-tests/TestThing.c
    06-Graph/ai-tests/TestDfs.c
    06-Graph/ai-tests/TestBfs.c
    06-Graph/ai-tests/TestDirected.c
    06-Graph/ai-tests/TestTopo.c
    06-Graph/ai-tests/TestMGraph.c
    06-Graph/ai-tests/TestPrim.c
    06-Graph/ai-tests/TestUnionFind.c
    06-Graph/ai-tests/TestHelper.c
        06-Graph/UnionFindDisjointSet.c
)

# 头文件：不参与编译，只为了让 IDE 把它们收进工程视图
set(GRAPH_HEADERS
    06-Graph/GraphTypes.h
    06-Graph/ALGraph.h
    06-Graph/MGraph.h
    06-Graph/UnionFindDisjointSet.h
    06-Graph/ai-tests/TestThing.h
    06-Graph/ai-tests/TestDfs.h
    06-Graph/ai-tests/TestBfs.h
    06-Graph/ai-tests/TestDirected.h
    06-Graph/ai-tests/TestTopo.h
    06-Graph/ai-tests/TestMGraph.h
    06-Graph/ai-tests/TestPrim.h
    06-Graph/ai-tests/TestUnionFind.h
    06-Graph/ai-tests/TestHelper.h
        06-Graph/UnionFindDisjointSet.h
)

add_executable(06_Graph ${GRAPH_SOURCES} ${GRAPH_HEADERS})

# Main.c 要 include "TestThing.h"；ai-tests 里要 include "ALGraph.h" / "GraphTypes.h"
target_include_directories(06_Graph PRIVATE
    06-Graph
    06-Graph/ai-tests
)

# queue.c 的 EnQueue / DeQueue / QueueEmpty 来自 common
target_link_libraries(06_Graph PRIVATE common)

# 06_Graph 是 assert 驱动，main() 跑完全部验收即代表通过
add_test(NAME 06_Graph COMMAND 06_Graph)
