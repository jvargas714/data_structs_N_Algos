project(data_structs)
include_directories(../utility)

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
        hash_table.cpp hash_table.h)
target_link_libraries(datastructs utility)
