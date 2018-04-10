#include <iostream>
#include <sstream>
#include <random>
#include "types.h"
#include "utility.h"


// display contents of std::vector
void display( std::vector<int>& vect )
{
    int cnt = 0;
    std::cout << "size: " << vect.size() << std::endl;
    for( auto& el : vect )
    {
        if(cnt == LINE_LIMIT)
        {
            std::cout << el << std::endl;
            cnt = 1;
            continue;
        }
        std::cout << el << " ";
        cnt++;
    }
    std::cout << std::endl;
}

// displays an array
void display( int* ar, size_t num_els )
{
    for( uint i = 0; i < num_els; i++ )
    {
        std::cout << ar[i] << " ";
    }
    std::cout << std::endl;
}

/*
    Descr:
    As we traverse through, we know that when the if case is true (data[j] <= pivot) that all
    The idea behind this partitioning algorithm is to place all elements smallers than the pivot
    to the left and all the greater elements to the right. Returns index of division point.
    the elements that came before that are larger than the pivot. So we can increment i and swap
    with the element that is larger than the pivot. We continue from there doing the same till we
    run through all the elements of the std::vector.
    Data is split like this: 0....divPt ; divPt+1....n
    Worst Case: O(n)
*/
int partition( std::vector<int>& data, int low, int high )
{
    int pivot   = data[high];   // typically pivot point is at end of std::vector
    int i       = (low - 1);    // index where smaller element exists
    for( int j = low; j <= high-1; j++ )
    {
        if( data[j] <= pivot )
        {
            i++;
            swap_el( &data[i], &data[j] );
        }
    }
    swap( data[i+1], data[high] );
    return ( i + 1 );
}

// display std::vector in its respective partitioned sections according to the partition point
void show_partition( std::vector<int>& data, int part_pt )
{
    std::cout << "div_pt: " << part_pt << std::endl;
    std::cout << "\nThe low side: " << std::endl;
    for( int i = 0; i <= part_pt; i++ )
    {
        std::cout << data[i] << " ";
    }
    for( int64_t i = part_pt+1; i < data.size(); i++ )
    {
        std::cout << data[i] << " ";
    }
}

// simply swap function
void swap_el( int* a, int* b )
{
    int tmp = *a;
    *a      = *b;
    *b      = tmp;
}

// split a string by specified delim, if empty token between delims then do not collect it
void split( const std::string& s, char delim, std::vector<std::string>& elems )
{
    std::stringstream ss;
    ss.str(s);  // set contents of ss with s
    std::string item;
    while( getline(ss, item, delim) )
    {
        if( !item.empty() )
            elems.push_back(item);
    }
}

std::vector<int> fill_vector( uint32_t num_els )
{
    std::vector<int> vect;
    std::random_device rd;
    srand( static_cast<uint32_t>( time( nullptr ) ) );
    for( uint i = 0; i < num_els; i++ )
    {
        vect.push_back( rd() % num_els );
    }
    return vect;
}

// fills array with num_els random integers
// allocated on the heap
int* fill_array( uint32_t num_els ) {
    std::random_device rd;
    auto* ar = new int[ num_els ];
    srand( static_cast<unsigned int>( time(nullptr) ) );
    for(uint i = 0; i < num_els; i++ ) {
        ar[i] = static_cast<uint32_t>((rd() % num_els));
    }
    return ar;
}

void swap(int & a, int &b) {
    int tmp = a;
    b = a;
    a = tmp;
}

template<typename T>
void display(const T& t) {
    for (auto& el : t)
        std::cout << el << " ";
    std::cout << std::endl;
}

int accum(std::vector<int>::iterator a, std::vector<int>::iterator b) {
    int sum = 0;
    for (auto it = a; it!=b; it++) {
        sum += *it;
        // cout << "sum: " << sum << endl;
    }
    return sum;
}

ListNode* fillListNode(std::vector<int>&& vect) {
    size_t sz = vect.size();
    if(!sz)
        return nullptr;
    auto* head = new ListNode(vect[0]);
    ListNode* tmp = head;
    for(auto it = vect.begin()+1; it != vect.end(); ++it) {
        tmp->next = new ListNode(*it);
        tmp = tmp->next;
    }
    return head;
}

size_t deallocateLList(ListNode* head) {
    size_t cnt = 0;
    ListNode* tmp = head;
    while(tmp) {
        delete tmp;
        tmp = tmp->next;
        cnt +=1;
    }
    return cnt;
}
