project(data_structs)
include_directories(../utility)

#add_compile_definitions(TESTING_HASHTABLE)

add_library(datastructs STATIC
        binary_tree.h
        heap.cpp
        heap.h
        linked_list.cpp
        linked_list.h
        logger.cpp
        logger.h
        LRU_Cache.cpp
        LRU_Cache.h
        node.h
        queue.h
        stack.h
        trie.cpp
        trie.h
        hash_table.cpp hash_table.h test_hashtable.cpp)
target_link_libraries(datastructs utility)
add_executable(test_hash_table test_hashtable.cpp)
