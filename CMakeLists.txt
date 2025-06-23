cmake_minimum_required(VERSION 3.10)

project(HW1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 14) # -std=c++14

add_compile_options(-Wall) # -Wall
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(HW2
        UnionFind.h
        HashTable.h
        wet2util.h
#       main25b2.cpp    # RELEASE MODE
        unit_tests.cpp  # UNIT TEST MODE
)
