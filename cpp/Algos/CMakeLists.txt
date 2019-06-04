project(myAlgos)
include_directories(./ ../utility)

# look to divide algo types and have them move over to jstdlib (templated as well)
add_library(myAlgos STATIC
        algos.cpp
        algos.h
        intzip.cpp
        intzip.h
        ../utility/types.h 
        generalAlgos/kmp.cpp)

target_link_libraries(myAlgos utility)

# build the rest of the sub projects
add_subdirectory(./bitBanger)
add_subdirectory(./spoj)
add_subdirectory(./cracking)
add_subdirectory(./LeetCode)
add_subdirectory(./generalAlgos)
