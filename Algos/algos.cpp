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

int main()
{
    // const uint SIZE = 10000;
    // vector<int> vect_1 = fill_vector( SIZE );       // used by bubble sort 
    // vector<int> vect_2( vect_1 );                   // used by Insertion sort
    // vector<int> vect_3( vect_1 );                   // used by heap sort 
    // t_point t1_bub, t2_bub;
    // auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    // auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    
    // cout << "Sorting an vector of length: " << vect_1.size()  << "\n" << endl;
    // //--------------------------------------Bubble Sort---------------------------------------------
    // t1_bub = hrc::now();
    // bubble_sort( vect_1 );
    // t2_bub = hrc::now();
    // milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    // micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    // cout << "Bubble Sort time of execution-->\n" << milli_sec << "msec\n" << micro_sec <<  
    //     "usec\n" << endl;
    // // end bubble sort

    // //-----------------------------------Insertion Sort---------------------------------------------
    // t1_bub = hrc::now();
    // insertion_sort( vect_2 );
    // t2_bub = hrc::now();
    // milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    // micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    // cout << "Insertion Sort time of execution-->\n" << milli_sec << "msec\n" << micro_sec <<  
    //     "usec\n" << endl;
    // // end insertion sort 

    // //-----------------------------------Heap Sort--------------------------------------------------
    // min_heap hp;
    // t1_bub = hrc::now();
    // // O(n)
    // for( auto& el : vect_3 )    // fill heap first before sort
    // {
    //     hp.insert(el);
    // }
    // // O(log n)
    // vector<int> sorted_vect = hp.sort();
    // t2_bub = hrc::now();
    // //display(sorted_vect);
    // milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    // micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    // cout << "Heap Sort (from min_heap) time of execution-->\n" << milli_sec <<"msec\n" 
    // << micro_sec << "usec" << endl;
    // // end heap sort 

    //-----------------------------------Quick Sort-------------------------------------------------
    // vector<int> data = { 3, 5, 8, 1, 2, 9, 4, 7, 6, 77, 1, 2, 5, 6, 7, 8, 00, 9, 8, 6 };
    vector<int> data = { 3, 5, 8, 1, 2, 9, 4, 7, 6, 77 };
    // vector<int> data = { 3, 5, 8, 1, 2, 9, 4, 7, 6 };
    // vector<int> data = { 1, 5, 4, 3, 2, 9, 8, 7, 6 };
    display( data );
    quick_sort( data, 0, data.size()-1 );
    cout << "at end of sort: " << endl; 
    // cout << " div: " << partition_vect(data, 0, data.size()-1) << "\n";
    display( data );
    // partition_vect(data, 0, 4);

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
    static int cnt = 0;   
    cnt++;
    cout << "cnt: " << cnt << endl; 
    if( cnt > 20)
        return;

    // recurs calls on the subsections of the vector
    if( (right_ind-1) > 0 && right_ind > left_ind )
    {
        // divPt is index at which the section of the vector that is higher than the pivot val begins
        int divPt = partition_vect( data, left_ind, right_ind );
        quick_sort( data, left_ind, divPt-1 );      // low side of sub vect 
        quick_sort( data, divPt, right_ind );       // high side 
    }
    cout << "GOT OUT" << endl; 
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
int partition_vect( vector<int>& vect, int left, int right )
{
    int tmp;
    int i               = left;     // left marker
    int j               = right;    // right marker
    const int pivot     = vect[ right ];       // pivot value 
    display( vect );
    cout << "left: " << left << " right: " << right << endl;
    cout <<"pivot: " << pivot << endl; 

    while( i <= j )
    {
        while( vect[i] < pivot )
            i++;

        while( vect[j] >= pivot )
            j--;

        if( i < j )
        {
            cout << "swapping: " << vect[i] << " with " << vect[j] << endl; 
            tmp = vect[i];
            vect[i] = vect[j];
            vect[j] = tmp;
            i++;
            j--;
        }
        else if( i == j )
        {
            cout << "swapping " << vect[i] << " with pivot " << pivot << endl;
            vect[right] = vect[i];
            vect[i] = pivot;
            break;
        }
    }
    display( vect );
    cout << "divpt: " << i << endl; 
    cout << "\n" << endl; 
    return i;
}
