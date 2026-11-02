cmake_minimum_required(VERSION 4.2)
project(StackAndHeap C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(StackAndHeap
        Stack.c
        Stack.h
        StackAndHeap.c
        SingleLinkListStack.c
        Queue.c
        Queue.h
        LinkListQueue.c
        LinkListQueue.h)
