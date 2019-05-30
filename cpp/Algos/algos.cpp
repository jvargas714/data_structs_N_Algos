#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "algos.h"
#include "utility.h"


/*
    bubble sort algo [* * * * * *]
    Worst case: 0(n^2)
    Best case: 0(n)
    Average case: 0(n^2)
*/
void bubble_sort( std::vector<int>& vect )
{
    bool changed    = true;
    while( changed )
    {
        changed = false;
        for(auto it = vect.begin(); (it+1) != vect.end(); it++ )
        {
            if( *(it+1) < *(it) )
            {
                int tmp = *(it);
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
    Visualization: 
        https://visualgo.net/en/sorting
    
    Descr: 
        - Select one element at index i (value to insert) (j will start one spot before i) (outer loop)
        - inner loop: we keep swapping until val_to_insert is greater than or equal to j element (one to right)

    Example:
        say vect = 3 5 38 44 47 15 ......... i = 5 val_insert(15), and j = 4 (47) 
        iterations:
            1. val_insert < 47 so swap   i = 5, j = 4
                3 5 38 44 15 47 
            2. val_insert < 44 so swap   i = 4, j = 3
                3 5 38 15 44 47 
            3. val_insert < 38 so swap   i = 3, j = 2
                3 5 15 38 44 47
            4. now val_insert > 5 breaks out of loop i = 2 j = 1
    
    Complexity: 
        space: O(1)
        runtime: O(n^2)  <<-- worst case 
*/
void insertion_sort( std::vector<int>& vect ) {
    int j = 0;
    for( int i = 1; i < vect.size(); i++ ) {
        j = i - 1;
        int val_to_insert = vect[i];
        while( i > 0 && val_to_insert < vect[j] )
            std::swap(vect[i--], vect[j--]);
        vect[i] = val_to_insert;  // #jdebug: may not need this write op 
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
void quick_sort( std::vector<int>& data, int left_ind, int right_ind )
{   
    if( right_ind > left_ind )
    {
        int div_pt = partition( data, left_ind, right_ind );
        quick_sort( data, left_ind, div_pt-1 );         // low side sub vect
        quick_sort( data, div_pt+1, right_ind );        // high side sub vect 
    }
}

int64_t fib( int n )
{
    if( n <= 1 ) return n;

    return fib(n-1) + fib(n-2);
}

// fib calc with memoization
int64_t fib_mem( int n, std::vector<int64_t>& f )
{
    if( n <= 1 ) return n;

    if( f[n] == -1 ) // result of this is not cached
        f[n] = fib_mem(n-1, f) + fib_mem(n-2, f);

    return f[n];
}
