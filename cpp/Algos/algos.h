#ifndef CPP_ALGOS_H
#define CPP_ALGOS_H
#include <vector>
#include <cstdint>

// sorting algos
void bubble_sort( std::vector<int>& );
void bubble_sort( int*, size_t );
void insertion_sort( std::vector<int>& );
void insertion_sort( int* );
void heap_sort( std::vector<int>& );
void merge_sort( std::vector<int>& );
void quick_sort( std::vector<int>&, int, int );

int64_t fib_mem( int n, std::vector<int64_t>& f );
int64_t fib(int);

#endif //CPP_ALGOS_H
