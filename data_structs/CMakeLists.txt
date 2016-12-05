cmake_minimum_required(VERSION 3.6)
project(data_structs)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    binary_tree.cpp
    binary_tree.h
    heap.cpp
    heap.h
    linked_list.cpp
    linked_list.h
    logger.cpp
    logger.h
    main.cpp
    master_structs.h
    node.h
    stack.h
    trie.cpp
    trie.h)

add_executable(data_structs ${SOURCE_FILES})