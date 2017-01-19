cmake_minimum_required(VERSION 3.6)
project(cracking)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp problems.cpp problems.h)
add_executable(cracking ${SOURCE_FILES})