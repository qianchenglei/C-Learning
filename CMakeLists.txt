cmake_minimum_required(VERSION 3.20)

project(C_Learning LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 所有可执行文件集中输出到 build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
    common/queue.c          # 层序遍历用：void* 通用循环队列
)
# 让本目标能 #include "queue.h"（只引队列实现，不引 common 的 stack.c，避免与自带 Stack.c 符号冲突）
target_include_directories(05_linked_bi_tree PRIVATE common)
