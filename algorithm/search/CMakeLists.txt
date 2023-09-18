cmake_minimum_required(VERSION 3.26)
project(binary_search)

set(CMAKE_CXX_STANDARD 11)

add_executable(search main.cpp
        search.cpp
        search.h
        UniformBinarySearch.cpp
        UniformBinarySearch.h
        ExponentialSearch.cpp
        ExponentialSearch.h)
