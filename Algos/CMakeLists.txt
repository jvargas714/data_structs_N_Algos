cmake_minimum_required(VERSION 3.6)
project(Algos)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    main.cpp
    Solution_Class.cpp
    Solution_Class.h
    hackerrank/markup_parser.h
    hackerrank/markup_parser.cpp
#    scrap.cpp
    )

add_executable(Algos ${SOURCE_FILES})