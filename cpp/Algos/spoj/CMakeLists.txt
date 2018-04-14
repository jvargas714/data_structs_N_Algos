project(spoj)
include_directories(../../utility)

add_library(spoj STATIC
        theNextPalindrome.cpp
        theNextPalindrome.h
        prime_gen.cpp)

target_link_libraries(spoj utility)