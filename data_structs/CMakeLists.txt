cmake_minimum_required(VERSION 3.6)
project(data_structs)

set(CMAKE_CXX_STANDARD 11)
#add_definitions(-DDEBUG)
set(SOURCE_FILES
    trie_complete/trie_main.cpp
        trie.h
        trie.cpp string_util.h string_util.cpp)

add_executable( trie_main ${SOURCE_FILES})
execute_process( COMMAND install_trie.sh )