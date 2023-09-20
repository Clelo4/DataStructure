cmake_minimum_required(VERSION 3.26)
project(BTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(btree main.cpp
        BTree.cpp
        BTree.h)
