project(driver)
include_directories(../Algos
        ../Algos/LeetCode
        ../Algos/cracking
        ../Algos/hackerrank
        ../Algos/spoj
        ../data_structs
        ../utility)

add_executable(driver
        main.cpp)

target_link_libraries(driver
        datastructs
        utility
        cracking
        leetCode
        spoj)
