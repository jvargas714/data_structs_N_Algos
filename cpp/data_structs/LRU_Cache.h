#ifndef DATA_STRUCTS_LRU_CACHE_H
#define DATA_STRUCTS_LRU_CACHE_H
#include <cstdio>
#include <cstdlib>

/*
 * Uses two data structures
 *  1. Queue: implemented using a doubly linked list. Max size of queue will be equal
 *      to the total number of frames available (cache size). The most recently used
 *      pages will be near the front end and least recently pages will be near the
 *      rear end.
 *  2. A hash with page number as key and address of the corresponding queue node as
 *     a value.
 *
 *  Description:
 *      When a page is referenced, the required page may be in the memory. If it isn't
 *      in the memory, we need ot detach the node of the list and bring it to the front
 *      of the queue. If the required page is not in the memory, we bring that in memory.
 *      In simple words we add a new node to the front of the queue and update the
 *      corresponding node address in the hash. If the queue is full, i.e. all the frames
 *      are full, we remove a node from the rear of the queue, and add the new node to
 *      the front of the queue.
 *
 */
template<typename T>
class lru_cache
{
private:

};


#endif //DATA_STRUCTS_LRU_CACHE_H
