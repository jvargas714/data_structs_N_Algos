//
// Created by JAY VARGAS on 4/9/18.
//

#ifndef CPP_UTILITY_H
#define CPP_UTILITY_H
#include <vector>
#include <string>
#include <cstdint>
#include "types.h"

#define LOG std::cout << __FUNCTION__ << "(): "
#define END std::endl

std::vector<int> fill_vector( uint32_t );
int* fill_array( uint32_t );

// display vector
// display contents of std::vector
template <class T>
void display( const T& vect, uint32_t line_limit=LINE_LIMIT )
{
    int cnt = 0;
    std::cout << "size: " << vect.size() << std::endl;
    for( auto& el : vect )
    {
        cnt++;
        if(cnt == line_limit)
        {
            std::cout << el << std::endl;
            cnt = 0;
            continue;
        }
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

// print array of specified size 
void display( const int*, size_t );

template<class T>
int findLargestInMatrix(const T& matrix) {
    int largestVal = matrix[0][0];
    for(const auto& row: matrix) {
        for(const auto& el : row) {
            if (el > largestVal)
                largestVal = el;
        }
    }
    return largestVal;
}

template <class T>
int getMatrixSpacing(const T& matrix) {
    int largestVal = findLargestInMatrix(matrix);
    uint32_t cnt = 0;
    while(largestVal > 0) {
        largestVal /= 10;
        cnt++;
    }
    return cnt;
}

template<typename T>
std::string addSpaces(int numSpaces, const T& el) {
    std::string result;
    auto tmp = static_cast<int>(el);
    uint32_t cnt = 0;
    while(tmp > 0) {
        tmp /= 10;
        cnt++;
    }
    return std::string((numSpaces-cnt+1), ' ');
}

template<class T>
void displayMatrix(const T& matrix) {
    int numSpaces = getMatrixSpacing(matrix);
    for (const auto& row : matrix) {
        for (const auto& el: row) {
            std::cout << el << addSpaces(numSpaces, el);
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> generateNxNMatrix(size_t n);

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

void displayListNodes(ListNode* root);

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
std::string elim_whitespace(std::string& str);

// shift vector to the right one space
void logicalShiftR(std::vector<int>&);

// inplace shift vector to the left one space
void logicalShiftL(std::vector<int>& nums);

// builds an integer binary tree from a vector
TreeNode* allocateBinTreeFromVect(const std::vector<int>&);

// helper function to allocate the bin tree
void _fill(const std::vector<int>& data, TreeNode* node, int i);

// bin tree traversal
std::vector<int> inOrderTraversal(const TreeNode* root);
std::vector<int> preOrderTraversal(const TreeNode* root);
std::vector<int> postOrderTraversal(const TreeNode* root);
#endif //CPP_UTILITY_H
