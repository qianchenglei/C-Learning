cmake_minimum_required(VERSION 4.2)
project(StringMatch CXX)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_BUFFER)
endif()
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
add_executable(StringMatch main.cpp
        h/Array1D.h
        h/BaseArray.h
        h/BaseArray.h
        h/Array2D.h
        h/Array3D.h
)
