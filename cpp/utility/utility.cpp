#include <iostream>
#include <sstream>
#include <random>
#include "time.h"
#include "types.h"
#include "utility.h"



// displays an array
void display( const int* ar, size_t num_els )
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

void _carry(std::vector<int>& digits, int digit_pos) {
	// terminating condition
	if (digits[digit_pos] <= 9) {
		return;
	}
	digits[digit_pos] = 0;
	digit_pos--;
	if (digit_pos < 0)
		digits.insert(digits.begin(), 1);
	else
		digits[digit_pos]++;
	_carry(digits, digit_pos);
}

/*
  take integer input and return string representation of that integer ie 123456 --> 123,456
*/
std::string format_number(const int& num) {
    std::string result("");
    std::string sign = "";
    const char SEP = ',';
    bool neg = (num<0);
    unsigned int tmp, charCnt=0;
    int rem = num;

    if(neg) {
        sign = "-";
        rem*=-1;
    }
    if (num == 0) {
        return std::string("0");
    }
    else if (rem < 10) {
        result = std::string(1, static_cast<char>(rem+ASCII_ZERO));
        std::cout << "result: " << result << std::endl;
        return (sign + result);
    }
    while(rem > 0) {
        result.insert(0, 1, static_cast<char>((ASCII_ZERO+(rem%10))));   // string::insert(pos, size, char)
        charCnt++;
        if( !(charCnt%3) ) {
            result.insert(0, 1, SEP);
        }
        rem /= 10;
    }
    // remove comma if at front of number
    if(result[0] == ',')
        result.erase(0, 1);   // std::string::erase(pos, npos); position and number of positions to erase
    return (sign + result);
}

std::string elim_whitespace( std::string& str )
{
    // find char index of first none white space
    uint32_t ind = 0;
    for( auto& ch : str )
    {
        if( ch == 32 ) // 32 ASCII for Space 
            ind++;
        else
            break;
    }
    return str.substr( ind, str.size() );
}

std::vector<std::vector<int>> generateNxNMatrix(size_t n) {
    int val = 1;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matrix[i][j] = val;
            val++;
        }
    }
    return matrix;
}

// shifts in a zero at the beginning of the vector
void logicalShiftR(std::vector<int>& nums) {
    for(size_t i = nums.size()-1; i > 0; i--)
        nums[i] = nums[i-1];
    nums[0] = 0;
}

void logicalShiftL(std::vector<int>& nums) {
    for(size_t i = 0; i < nums.size(); i++) {
        nums[i] = nums[i+1];
    }
    nums[nums.size()-1] = 0;
}
