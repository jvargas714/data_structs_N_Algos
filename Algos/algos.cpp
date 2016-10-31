#include <cstdlib>          // rand()
#include <iostream>         // cout, endl
#include <vector>           // vector, size_t
#include <chrono>
#include "time.h"           // time(NULL)
#include "../data_structs/master_structs.h"  // min:heap

// typedefs and namespaces 
using namespace std;
using namespace std::chrono;
typedef unsigned int uint;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;


// sorting algos
void bubble_sort( vector<int>& );
void bubble_sort( int*, size_t );
void insertion_sort( vector<int>& );
void insertion_sort( int* );
void heap_sort( vector<int>& );
void merge_sort( vector<int>& );
void quick_sort( vector<int>& );

// helper functions
vector<int> fill_vector( size_t );
int* fill_array( size_t );
void display( vector<int>& );
void display( int*, size_t );
void partition_vect( vector<int>&, int, int );

int main()
{
    const uint SIZE = 10000;
    vector<int> vect_1 = fill_vector( SIZE );       // used by bubble sort 
    vector<int> vect_2( vect_1 );                   // used by Insertion sort
    vector<int> vect_3( vect_1 );                   // used by heap sort 
    t_point t1_bub, t2_bub;
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    
    //--------------------------------------Bubble Sort---------------------------------------------
    t1_bub = hrc::now();
    bubble_sort( vect_1 );
    t2_bub = hrc::now();
    milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    cout << "Bubble Sort time of execution-->\n" << milli_sec << "msec\n" << micro_sec <<  
        "usec\n" << endl;
    // end bubble sort

    //-----------------------------------Insertion Sort---------------------------------------------
    t1_bub = hrc::now();
    insertion_sort( vect_2 );
    t2_bub = hrc::now();
    milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    cout << "Insertion Sort time of execution-->\n" << milli_sec << "msec\n" << micro_sec <<  
        "usec\n" << endl;
    // end insertion sort 

    //-----------------------------------Heap Sort--------------------------------------------------
    min_heap hp;
    for( auto& el : vect_3 )    // fill heap first before sort
    {
        hp.insert(el);
    }

    t1_bub = hrc::now();
    vector<int> sorted_vect = hp.sort();
    t2_bub = hrc::now();
    display(sorted_vect);
    milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    cout << "Heap Sort (from min_heap) time of execution-->\n" << milli_sec <<"msec\n" 
    << micro_sec << "usec" << endl;
    // end heap sort 

    return 0;
}

//-----------------------------------------implementations------------------------------------------

/* 
    bubble sort algo [* * * * * *]
    Worst case: 0(n^2)
    Best case: 0(n)
    Average case: 0(n^2)
*/
void bubble_sort( vector<int>& vect )
{
        bool changed    = true;
        while( changed )
        {
            changed = false;
            for( vector<int>::iterator it = vect.begin(); (it+1) != vect.end(); it++ )
            {
                if( *(it+1) < *(it) )
                {
                    int tmp   = *(it);
                    *(it)   = *(it+1);
                    *(it+1) = tmp;
                    changed = true;
                } 
            }
        }
}

/*
    Bubble Sort algo
    Worst case: 0(n^2)
    Best case: 0(n)
    Average case: o(n^2)
*/
void bubble_sort( int* ar, size_t len )
{
    bool changed    = true;
    while( changed )
    {
        changed = false;
        for( uint32_t i = 0; i < len; i++ )
        {
            if( ar[i] > ar[i+1] )
            { // swap values
                int tmp = ar[i];
                ar[i]   = ar[i+1];
                ar[i+1] = tmp;
                changed = true;
            }
        }
    }
}

/*
    Descr: Select one element and place it in the correct spot in the list 
*/
void insertion_sort( vector<int>& vect )
{
    uint j = 0;
    for( uint i = 1; i < vect.size(); i++ )
    {   
        j = i - 1;
        int val_to_insert = vect[i];
        while( i > 0 && val_to_insert < vect[j] )
        {
            // swap to make room for entry
            int tmp = vect[i];
            vect[i] = vect[j];
            vect[j] = tmp;
            --i;
            --j;
        }
        vect[i] = val_to_insert;
    }
}

/*
    Descr: uses a divide and conquer technique
    Worst case: 0(n^2)
    Best case: 0(nlog n) (simple partition) or 0(n) (3 way partition)
    Average case: 0(nlog n)

*/
void quick_sort( vector<int>& vect )
{

}

//______________________________________________Helpers_____________________________________________

// fill vector with random data from 0 to num_els 
vector<int> fill_vector( size_t num_els )
{
    vector<int> vect;
    srand( time( NULL ) );
    for( uint i = 0; i < num_els; i++ )
    {
        vect.push_back( rand() % num_els );
    }
    return vect;
}

// fills array with num_els random integers
// allocated on the heap
int* fill_array( size_t num_els )
{
    int* ar = new int[ num_els ];
    srand( time( NULL ) );
    for(uint i = 0; i < num_els; i++ )
    {
        ar[i] = rand() % num_els;
    }
    return ar;
}

// display contents of vector 
void display( vector<int>& vect )
{
    int cnt = 0;
    for( auto& el : vect )
    {
        if(cnt == LINE_LIMIT)
        {
            cout << el << endl;
            cnt = 1;
            continue;
        }
        cout << el << " ";
        cnt++;
    }
    cout << endl;
}

// displays an array 
void display( int* ar, size_t num_els )
{
    for( uint i = 0; i < num_els; i++ )
    {
        cout << ar[i] << " ";
    }
    cout << endl;
}

/*
    Descr: choose a pivot point and place it in the array so that all elements to the left are 
        smaller and all elements to the right are larger. 
        Big Oh: O(n)
        1. choose pivot index (typically rightmost index)
        2. compare every element with pivot if > group to the right group if <= group to left
            * if it is equal to the pivot val we can skip it 
        3. call this recursively 
*/
void partition_vect( vector<int>& vect, int left, int right )
{
    int i       = left;
    int j       = right;
    int tmp;
    int pivot   = vect[ (left+right) / 2 ]; 

    while( i <= j )
    {
        while( vect[i] < pivot )
            i++;

        while( vect[j] > pivot )
            j--;

        if( i <= j )
        {
            tmp = vect[i];
            vect[i] = vect[j];
            vect[j] = tmp;
            i++;
            j--;
        }
    }
    display( vect );
}
