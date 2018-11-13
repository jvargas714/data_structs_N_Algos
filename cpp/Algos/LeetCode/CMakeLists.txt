project(leetCode)
include_directories(../)

add_library(leetCode STATIC
        string_problems.h
        string_problems.cpp
        binary_tree_problems.h
        binary_tree_problems.cpp
        array_problems.h
        array_problems.cpp
        array_testing.cpp
        other_problems.cpp
        other_problems.h
        sort_search_problems.h
        sort_search_problems.cpp
        sort_search_testing.cpp
        dynamic_problems.cpp
        dynamic_problems.h
        linkedlist_problems.cpp
        linkedlist_problems.h
        math_problems.cpp
        math_problems.h
        design_problems.cpp
        design_problems.h)

add_library(facebook STATIC
        facebook.cpp
        facebook.h)

add_executable(string_testing string_testing.cpp)
add_executable(binary_tree_testing binary_tree_testing.cpp)
add_executable(array_testing array_testing.cpp)
add_executable(sort_search_testing sort_search_testing.cpp)
add_executable(facebook_test facebook_test.cpp)

target_link_libraries(string_testing leetCode utility)
target_link_libraries(binary_tree_testing leetCode utility)
target_link_libraries(array_testing leetCode utility)
target_link_libraries(sort_search_testing leetCode utility)
target_link_libraries(facebook_test facebook utility)

