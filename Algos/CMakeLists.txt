cmake_minimum_required(VERSION 3.6)
project(Algos)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    LeetCode/short_algos.cpp
    LeetCode/short_algos.h
    LeetCode/main.cpp)

add_executable(Algos ${SOURCE_FILES})
