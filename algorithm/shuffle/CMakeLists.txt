cmake_minimum_required(VERSION 3.26)
project(shuffle)

set(CMAKE_CXX_STANDARD 11)

add_executable(shuffle main.cpp
        Shuffle.cpp
        Shuffle.h)
