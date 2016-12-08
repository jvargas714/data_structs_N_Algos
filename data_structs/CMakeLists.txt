cmake_minimum_required(VERSION 3.6)
project(data_structs)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    main.cpp
    node.h
    heap.cpp
    heap.h
    queue.h)

add_executable(data_structs ${SOURCE_FILES})