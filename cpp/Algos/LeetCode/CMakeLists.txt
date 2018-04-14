project(leetCode)
include_directories(../)

add_library(leetCode STATIC
        leet_algos.cpp
        leet_algos.h
        )

add_executable(leetTest
        main.cpp)

target_link_libraries(leetTest leetCode utility)

