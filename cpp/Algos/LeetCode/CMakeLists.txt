project(leetCode)
include_directories(../)

add_library(leetCode STATIC
        string_problems.h
        string_problems.cpp
        binary_tree_problems.h
        binary_tree_problems.cpp
        array_problems.h
        array_problems.cpp
        )

add_executable(string_testing
        string_testing.cpp)
add_executable(binary_tree_testing binary_tree_testing.cpp)

target_link_libraries(string_testing leetCode utility)
target_link_libraries(binary_tree_testing leetCode utility)

