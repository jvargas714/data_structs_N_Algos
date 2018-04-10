#include <iostream>
#include <string>
#include <vector>

/*
    Heap Data Structure
    Properties:
        - its a complete tree ( all levels are completely filled except possibly the last level and 
            the last level has all keys as left as possible)
        
        - suitable to be stored in a array
        
        - For min heap the key root must be minimum among all keys present in the binary heap. 
            * same must be recursively true for all nodes in Binary heap.
        
        - max heaps are similar, but instead the root is greater then all of its children 
            * same must be recursively true for all nodes in the Binary heap
        
        - Useful when using with a Priority Queue
        
        - delete, get_max, insert operations are O(logn)
        
        - can be used to solve the following problems 
            a. Dijkstra's shortest path 
            b. Prims Minimum spanning tree
            c. Kth largest element in an array 
            d. Sort an almost sorted array 
            e. Merge K sorted arrays
        
        - Operations
            1. getMin() : O(1) 
                * returns the root element of a Min Heap
            
            2. extract_min() : O(log n)
                * removes the minimum element from Min Heap. 
                * after removal will need to maintain heap properties stated above by calling
                    heapify()

            3. decreaseKey(): O(log n)
                * Decreases value of key. After the modification we may beed to re heapify to
                    restore heap properties 

            4. insert(): O(log n)
                * add a new key at the end of the tree. 
                * if new key is greater than its parent, then we dont need to do anything
                * otherwise we need to traverse up to fix the violated heap property

            delete(): O(log n)
                * sets key to infinite minimum ie. INT_MIN, by calling decreaseKey
                * after decreaseKey is calle the element will be at the root 
                * we can then extractMin()

        Array Based Implementation Notes:
            - Array Positioning
                * for any node in position i
                * its left child is in position 2i
                * its right child is in position 2i + 1 
                * its parent is in position i/2 (use integer division)

            - Inserting in to a min heap
                * place new element in to next available position in array
                * Compare the new element with its parent.
                    -- if new el is smaller then swap it with the parent 
                    -- continue this process until either 
                        1. the new elements parent is smaller than or equal to the new element
                        2. the element reaches the root (index zero of the array)

            - Removing a node
                * place the root element in a variable to return later
                * remove the last element in the deepest level and move it to the root
                * While the moved element has a value greater than at least one of its children, 
                    swap this value with the smaller valued child
                * return the original root that was saved 
*/

/* 
    TODO: convert this to a template class eventually
    TODO: need to deal with duplicate node somehow dahhh !! 
    Descr: 
        -- by default this heap class will be a Min Heap
        -- This is an array based implementation 
        -- root is smallest value 
*/

// used in the display function limit how many elements are displayed per line

class min_heap 
{
private:
    std::vector<int> data;

    // return index of left child of node @ index i
    inline int left( int i ) const { return 2*i + 1; }

    // return index of right child of node @ index i 
    inline int right( int i ) const{ return 2*i + 2; }

    // return index of parent node of node @ index i
    inline int parent( int i ) const{ return (i-1) / 2; }

    // get index of element in the heap
    int get_index( int ) const;

    // bubbles down node in root to correct location within the heap
    void bubble_down();

    // bubbles up node at the end of the heap to its correct location within the heap 
    void bubble_up();

public:
    min_heap(): data(){}
    min_heap( int el ): data(){ data.push_back( el ); }
    
    virtual void insert( int );                             // checks good 
    
    // returns min element without removing it
    int get_min() const;

    // returns max element without removing it
    inline int get_max() const { return 0; } /*TODO:: needs implementation*/
    
    // returns and removes the minimum element then restore min heap properties
    int extract_min();

    /* 
        if the node at index i is violating the min heap properties, 
        not smaller than both its children, if so we correct this
    */
    void display() const;

    inline size_t size() const { return data.size(); };

    /* 
        a heap sort! returns a sorted vector O(nlog n)
        - bool arg specifies if we want to retain original data vector when extracting elements
        - if so a copy is made and at end of sort the original heap is retained
    */
    std::vector<int> sort( bool cpy=false );
};