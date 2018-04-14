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

// display vector 
void display( const std::vector<int>& );

// print array of specified size 
void display( const int*, int );

// partition vector 
int partition_vect( std::vector<int>&, int, int );

// partition vector 
int partition( std::vector<int>&, int, int );

// swap two integers by pointers 
void swap_el( int*, int* );

// swap two integers by reference 
void swap( int&, int&);

// prints partition of vector to stdout 
void show_partition( std::vector<int>&, int );

// take a string and create a vector of tokens separated by delim 
void split(const std::string&, char delim, std::vector<std::string>&);

// same as python's sum() function 
int accum(std::vector<int>::iterator a, std::vector<int>::iterator b);

// put a linked list on the heap, takes values from vector 
ListNode* fillListNode(std::vector<int>&&);

// if linked list is fully allocated on the heap this function deallocates those nodes 
size_t deallocateLList(ListNode*);

// with an integer represented by an array this function performs carry operation when adding to this integer
void _carry(std::vector<int>& digits, int digit_pos);

// handle input args from terminal
template<typename T>
T handle_input(int argc, char* argv[]);

// return provided integer in the string form with commas 123456 --> 123,456
std::string format_number(const int& num);

// eliminate whitespace in a string
std::string elim_whitespace( std::string& str );

#endif //CPP_UTILITY_H
