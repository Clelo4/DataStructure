cmake_minimum_required(VERSION 3.26)
project(demo)

set(CMAKE_CXX_STANDARD 11)

add_executable(demo main.cpp
        RedBlackTree.cpp
        RedBlackTree.h)
