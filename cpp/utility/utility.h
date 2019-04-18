#ifndef CPP_UTILITY_H
#define CPP_UTILITY_H
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include "types.h"

#define LOG std::cout << __FUNCTION__ << "(): "
#define END std::endl
#define  FUNCT_HEADER std::cout << "\n\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << __FUNCTION__ << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << std::endl
#define FUNCT_END std::cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << __FUNCTION__ << " END " << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << std::endl
#define END_PROBLEM std::cout << "\n\n\n\n" << std::endl
#define SEPARATOR std::cout <<"----------------------------------------------------------------------" << std::endl;

// fill vector from file
bool fillVectorFromFile(const std::string& fileName, std::vector<int>& vect);

std::vector<int> fill_vector( uint32_t n, bool isRand=true);
int* fill_array( uint32_t );

// display vector
// display contents of std::vector
template <class T>
void display( const std::vector<T>& vect, uint32_t line_limit=LINE_LIMIT ) {
    int cnt = 0;
    std::cout << "size: " << vect.size() << std::endl;
    for( auto& el : vect ) {
        cnt++;
        if(cnt == line_limit) {
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

template<typename T1, typename T2>
void display(const std::vector<std::pair<T1, T2>>& pairs, uint32_t line_limit=LINE_LIMIT) {
    int cnt = 0;
//    std::cout << "size: " << pairs.size() << std::endl;
    for (const auto& el : pairs) {
        cnt++;
        if (cnt == line_limit) {
            std::cout << "(" << el.first << "," << el.second << ")" << std::endl;
            cnt = 0;
            continue;
        }
        std::cout << "(" << el.first << "," << el.second << ")" << " ";
    }
    std::cout << std::endl;
}

template<typename T>
int findLargestInMatrix(const T& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
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
    LOG << matrix.size() << "x" << matrix[0].size() << " matrix" << END;
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

// check for primality
bool isPrime(int n);
bool is_prime(const uint32_t& x);

// generate n prime numbers
std::vector<uint64_t> genPrimes(const uint64_t n);
std::vector<uint64_t> genPrimesV2(const uint64_t n);

// find max val in container using iterators [iter1, iter2] inclusive
// O(n)
template<typename RandomAccessIter, typename T>
T maxElement(RandomAccessIter iter1, RandomAccessIter iter2) {
    T maxVal = *iter1;
    iter1++;
    while (iter1 != iter2) {
        if (*iter1 > maxVal) maxVal = *iter1;
        iter1++;
    }
    return (*iter2 > maxVal) ? *iter2:maxVal;
}

template<class T>
void _permute(std::vector<T>& vals, std::vector<std::vector<T>>& result, int i, int len) {
    if (i == len-1) {
        result.push_back(vals);
        return;
    }
    for (int ii = i; ii < len; ii++) {
        swap(vals[ii], vals[i]);
        _permute(vals, result, i+1, len);
        swap(vals[ii], vals[i]);
    }
}

template<class T>
void _permute(std::vector<T>& vals, int permLen) {

}

template<class T>
std::vector<T> findPermutations(std::vector<T>& vals, int permLen) {
    return {};
}

template<class T>
std::vector<std::vector<T>> findPermutations(std::vector<T>& vals) {
    std::vector<std::vector<T>> result;
    _permute(vals, result, 0, vals.size());
    return result;
}

template<typename T>
int binarySearchLowerBound(const std::vector<T>& vals, const int& target) {
    int l = 0, r = (int)vals.size()-1;
    while (l <= r) {
        int mid = l + (r-l)/2;
        const T& val = vals[mid];
        if (val >= target) {  // greater than
//            r = mid - 1;
            return mid;
        } else { // less than
            l = mid + 1;
        }
    }
    return -1;
}

template<class T>
int binarySearch(const std::vector<T>& vals, const int target) {
    int l =0, r = (int)vals.size()-1;
    while (l <= r) {
        int mid = l + (r-l)/2;
        if (vals[mid] == target) return mid;
        else if (vals[mid] > target) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ERROR;
}

// returns vector indicating which bit positions have a 1 bit flipped, first bit is mapped to 0
std::vector<int> findBitPositions(uint64_t val);


#endif //CPP_UTILITY_H


















