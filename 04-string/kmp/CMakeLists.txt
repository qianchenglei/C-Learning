cmake_minimum_required(VERSION 4.3)
project(KMP C)

set(CMAKE_C_STANDARD 11)

add_executable(KMP main.c
        KMP.c
        KMP.h)
