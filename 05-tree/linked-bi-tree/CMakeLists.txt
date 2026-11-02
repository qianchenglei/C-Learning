cmake_minimum_required(VERSION 3.28)
project(linked_of_a_binary_tree C)

set(CMAKE_C_STANDARD 11)

add_executable(linked_of_a_binary_tree main.c
        LinkedOfBinaryTree.c
        LinkedOfBinaryTree.h
        Stack.h
        Stack.c)
