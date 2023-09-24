cmake_minimum_required(VERSION 3.26)
project(RTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(RTree main.cpp
        RTree.cpp
        RTree.h)
