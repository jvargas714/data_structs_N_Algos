project(dataStructs_N_Algos)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/cpp/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/cpp/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/cpp/bin)

# build it all out
add_subdirectory(./utility)
add_subdirectory(./Algos)
add_subdirectory(./data_structs)
add_subdirectory(./driver)
add_subdirectory(./testing)
