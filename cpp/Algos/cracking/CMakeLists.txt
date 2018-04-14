project(cracking)
include_directories(../../utility
        ../../data_structs)
add_library(cracking STATIC
        problems.cpp
        problems.h)
target_link_libraries(cracking datastructs)
