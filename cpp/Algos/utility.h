//
// Created by JAY VARGAS on 4/9/18.
//

#ifndef CPP_UTILITY_H
#define CPP_UTILITY_H
#include <vector>
#include <string>
#include <cstdint>
struct ListNode;

std::vector<int> fill_vector( uint32_t );
int* fill_array( uint32_t );
void display( std::vector<int>& );
void display( int*, int );
int partition_vect( std::vector<int>&, int, int );
int partition( std::vector<int>&, int, int );
void swap_el( int*, int* );
void swap( int&, int&);
void show_partition( std::vector<int>&, int );
void split(const std::string&, char delim, std::vector<std::string>&);
int accum(std::vector<int>::iterator a, std::vector<int>::iterator b);
ListNode* fillListNode(std::vector<int>&&);
size_t deallocateLList(ListNode*);
// display contents of an iterable
template<typename T>
void display(const T& t);

// handle input args from terminal
template<typename T>
T handle_input(int argc, char* argv[]);


#endif //CPP_UTILITY_H
