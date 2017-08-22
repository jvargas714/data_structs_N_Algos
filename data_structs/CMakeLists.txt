cmake_minimum_required(VERSION 3.6)
project(data_structs)

set(CMAKE_CXX_STANDARD 11)
#add_definitions(-DDEBUG)
set(TRIE_FILES
        trie.h
        trie.cpp string_util.h string_util.cpp linked_list_main.cpp)
add_executable( trie_main ${TRIE_FILES})

set(LINKED_LIST_FILES
        linked_list.h
        linked_list.cpp
        linked_list_main.cpp)
add_executable(linked_list_main ${LINKED_LIST_FILES})

