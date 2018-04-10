project(leetCode)
include_directories(../)

add_library(leetCode STATIC
        leet_algos.cpp
        leet_algos.h
        ../utility.cpp
        ../utility.h)

add_executable(leetTest
        main.cpp)

target_link_libraries(leetTest leetCode)

