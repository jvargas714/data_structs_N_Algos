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
void quick_sort( vector<int>&, int, int );

// helper functions
vector<int> fill_vector( size_t );
int* fill_array( size_t );
void display( vector<int>& );
void display( int*, size_t );
int partition_vect( vector<int>&, int, int );
int partition( vector<int>&, int, int );
void swap_el( int*, int* );
void show_partition( vector<int>&, int );


int main()
{
    const uint SIZE = 100000;
    vector<int> vect_1 = fill_vector( SIZE );       // sorted by bubble sort 
    vector<int> vect_2( vect_1 );                   // sorted by Insertion sort
    vector<int> vect_3( vect_1 );                   // sorted by heap sort
    vector<int> vect_4( vect_1 );                   // sorted by quicksort
    t_point t1_bub, t2_bub;
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    
    cout << "Sorting an vector of length: " << vect_1.size()  << "\n" << endl;
    // //--------------------------------------Bubble Sort------------------------------------------
    // t1_bub = hrc::now();
    // bubble_sort( vect_1 );
    // t2_bub = hrc::now();
    // milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    // micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    // cout << "Bubble Sort time of execution-->\n" << milli_sec << "msec\n" << micro_sec <<  
    //     "usec\n" << endl;
    // // end bubble sort

    // // //-----------------------------------Insertion Sort---------------------------------------
    // t1_bub = hrc::now();
    // insertion_sort( vect_2 );
    // t2_bub = hrc::now();
    // milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    // micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    // cout << "Insertion Sort time of execution-->\n" << milli_sec << "msec\n" << micro_sec <<  
    //     "usec\n" << endl;
    // end insertion sort 

    //-----------------------------------Heap Sort--------------------------------------------------
    min_heap hp;
    t1_bub = hrc::now();
    // O(n)
    for( auto& el : vect_3 )    // fill heap first before sort
    {
        hp.insert(el);
    }
    // O(log n)
    vector<int> sorted_vect = hp.sort();
    t2_bub = hrc::now();
    //display(sorted_vect);
    milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    cout << "Heap Sort (from min_heap) time of execution-->\n" << milli_sec <<"msec\n" 
    << micro_sec << "usec\n" << endl;
    // end heap sort 

    //-----------------------------------Quick Sort-------------------------------------------------
    t1_bub = hrc::now();
    quick_sort( vect_4, 0, vect_1.size()-1 );
    t2_bub = hrc::now();
    milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    cout << "QuickSort time of execution-->\n" << milli_sec << "msec\n" << micro_sec <<  
        "usec\n" << endl;
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
    Descr: uses a divide and conquer technique. By swapping the numbers, you can gather numbers that
        are less than the pivot on the left side of the sequence, and numbers that are greater than
        or equal to the pivot on the right side.
    Algo:
        1. randomly set a pivot value
        2. a left marker is placed on the most left value
        3. a right marker is placed on the most right value
        4. left marker will move to the right
        5. when the left marker reaches a value greater or equal to the pivot value it stops
        6. now the right marker moves to the left 
        7. when the right marker hits a value that is less than the pivot it stops
        8. swap both values of the left and right markers
        9. after the swap the left marker continues to moving to the right 
        10. left continues to move until it finds a value >= pivot it stops moving 
        11. Again move the right marke left until it finds a value < pivot
        12. movement of the right marker also stops when it hits the same value as the left marker
        13. when the left and right marker stops and they are on the same value the pivot is swapped
        14. the number occupied by both the left and right markers is considered fully sorted
        15. first round is finished, now another round of operations will be performed recursively
            on both sequences created by the division
        16. This is repeated unitl fully sorted 

        Notes on flow control: 
            - when moving with the left marker and it runs into the right marker, it doesnt stop
                * this is different from the right marker 
                * When the left marker reaches the rightmost edge of the target sequence, it stops
                    ** this means the pivot number is the largest number in the target sequence
            - When the rightmost marker is passed by the left marker it finishes without moving 
            - When the left marker has reached the rightmost edge of the target sequence, the pivot
                number is considered fully sorted, and the round of operations ends, the remaining 
                elements are considered to be another sequence
            - when the target sequence only has one number it is considered fully sorted
    
    Worst case: 0(n^2)
    Best case: 0(nlog n) (simple partition) or 0(n) (3 way partition)
    Average case: 0(nlog n)
*/
void quick_sort( vector<int>& data, int left_ind, int right_ind )
{   
    if( right_ind > left_ind )
    {
        int div_pt = partition( data, left_ind, right_ind );
        quick_sort( data, left_ind, div_pt-1 );         // low side sub vect
        quick_sort( data, div_pt+1, right_ind );        // high side sub vect 
    }
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
    cout << "size: " << vect.size() << endl; 
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
    Descr: 
    As we traverse through, we know that when the if case is true (data[j] <= pivot) that all
    The idea behind this partitioning algorithm is to place all elements smallers than the pivot 
    to the left and all the greater elements to the right. Returns index of division point. 
    the elements that came before that are larger than the pivot. So we can increment i and swap
    with the element that is larger than the pivot. We continue from there doing the same till we 
    run through all the elements of the vector. 
    Data is split like this: 0....divPt ; divPt+1....n
    Worst Case: O(n)
*/
int partition( vector<int>& data, int low, int high )
{
    int pivot   = data[high];   // typically pivot point is at end of vector
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

// display vector in its respective partitioned sections according to the partition point 
void show_partition( vector<int>& data, int part_pt )
{
    int cnt = 0;
    cout << "div_pt: " << part_pt << endl; 
    cout << "\nThe low side: " << endl;
    for( int i = 0; i <= part_pt; i++ )
    {
        cout << data[i] << " ";
        if( cnt == LINE_LIMIT )
        {
            cout << endl;
            cnt = 0;
        }
    }
    for( uint i = part_pt+1; i < data.size(); i++ )
    {
        cout << data[i] << " ";
        if( cnt == LINE_LIMIT )
        {
            cout << endl;
            cnt = 0;
        }   
    }
}

// simply swap function
void swap_el( int* a, int* b )
{
    int tmp = *a;
    *a      = *b;
    *b      = tmp;
}