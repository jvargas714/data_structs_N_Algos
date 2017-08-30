#include "problems.h"
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <random> 
#include <map> 

typedef unsigned int uint;
/*
 * 1.1
 * Implement an algorithm to determine if a string has all unique characters.
 * What if you cannot use additional data structures?
 * Solution: O(n)
 */
bool arrays_n_strings_CH1::is_unique( const std::string& str )
{
    // small strings
    if( str.size() > 128 ) return false;   // only 128 characters so anymore means a repeat

    std::vector<bool> char_set( 128, false );
    for( auto ch : str )
    {
        unsigned int pos = str.find( ch );
        if( char_set[pos] )
            return false;
        char_set[pos] = true;
    }
    return true;
}

/*
 * 1.2
 * Given two strings, write a method to decide if one is a permutation of the other
 */
bool arrays_n_strings_CH1::check_permutation( std::string str1, std::string str2 )
{
    if( str1.size() != str2.size() ) return false;

    std::sort( str1.begin(), str1.end() );
    std::sort( str2.begin(), str2.end() );
    if( !str1.compare( str2 ) )
        return true;
    return false;
}

/*
 * 1.3
 * Write a method that replaces all spaces with %20 you can assume the string has sufficient space
 * at the end to hold the additional characters, and that you are given the true length of the
 * string
 * Runtime: O(n)
 * */
void arrays_n_strings_CH1::urlify( std::string& str )
{
    std::cout << str << std::endl;
    size_t len = str.size();
    for( size_t i = 0; i < len; ++i )
    {
        if( str[i] == 0x20 )
        {
            str.erase( i, 1 );
            str.insert( i, "%20" );
            len+=3;
        }
    }
    std::cout << str << std::endl;
}

/*
 * 1.4
 * Given a string write a function to check if it is a permutation of a palindrome. A palindrome is a word
 * or phrase that is the same forwards and backwards. A permutation is a rearrangement of letters. Does not
 * need to be only dictionary words.
 * Notes:
 *  We know that for a string to be a palindrome that is must be able to be read the same forward and
 *  backwards. This tells us that all characters must appear an even number of times. If there are an
 *  odd number of characters in the input string then exactly one character must only appear once.
 *  Therefore we only have to check if a palindrome permutation a string can have no more than one 
 *  character that is odd in frequency.
 * input: Tact Coa
 * */
bool arrays_n_strings_CH1::palindrome_permutation( const std::string& str )
{
    size_t len = str.size();
    if( len == 0 ) return false;
    if( len == 2 && str[0] == str[1] ) return false;
    unsigned int* freq_table = _build_frequency_table( str );
    return _check_max_one_odd(freq_table);    
}

/*
    1.5: One Away 
        There are three types of edits that can be made on strings, insert a character, remove a character, or 
        replace a character. Given two strings, write a method to check if they are one edit (or zero edits) away 
*/
bool arrays_n_strings_CH1::one_away(const std::string& a, const std::string& b) 
{
    // check if same first 
    if (a==b)
        return true;
    
    int size_a = a.size();
    int size_b = b.size();
    size_t mod_cnt = 0;

    if(abs(size_a-size_b) >= 2) {  // check deletes and inserts here
        return false;
    }
    else { // case where we may have more than one replace, or can have a replace and delete, or replace and insert
        // O(n)
        int char_cnt = (size_a<size_b) ? size_a:size_b; // take shorter word length 
        for( int i = 0; i < char_cnt; ++i) {
            if(mod_cnt>1)
                return false;
            if(a[i] != b[i])
                mod_cnt++;
        }
    }
    // if we found a modification the strings can still different in length by 1 if so that would be the second mod 
        if( mod_cnt == 1 && (size_a != size_b))
            return false;
        else
            return true;
}

std::string arrays_n_strings_CH1::string_compression(const std::string& str) {
    char curr_char = str[0];
    int cnt = 0;
    std::stringstream result;
    for(auto it = str.begin(); it != str.end(); it++) {
        if (*it == curr_char) {
            cnt++;
        }
        else { // a new char
            result << curr_char << cnt;
            curr_char = *it;
            cnt=1;
        }
    }
    result << curr_char << cnt;
    return (str.size() > result.str().size()) ? result.str():str;
}

/*1.9: String Rotation (long way)
    Check if one word is a substring of another. Given two strings s1 and s2 write code to check 
    if s2 is a rotation of s1. I.e: waterbottle --> erbottlewat (returns true)
    Noted Functions: 
        string::compare(char* str)
        string::copy(char* str, size_t len, size_t pos=0)
*/
bool arrays_n_strings_CH1::is_rotation(const std::string& s1, const std::string& s2) {
    size_t len = s1.size(); 
    // must be same size
    if (len != s2.size())
        return false; 
    char s2cpy[len+1];
    // copy for string rotation 
    size_t cpylen = s2.copy(s2cpy, len);
    s2cpy[cpylen] = '\0';
    char new_end;

    // from here we just rotate the word a full lap and check if it matches the other string
    for(unsigned int i = 0; i < len; ++i) {
        if (s1.compare(s2cpy) == 0) 
                return true;
        for(unsigned int j = 0; j < len-1; ++j) {
            if (j == 0) 
                new_end = s2cpy[0];
            s2cpy[j] = s2cpy[j+1];
        }
        s2cpy[cpylen-1] = new_end;
        std::cout << s2cpy << std::endl;
    }
    return false;
}

/*1.9: Is Rotation Optimized Version
    Description:
        The idea here is if we concat s1+s1 to get s1s1 then we know if s2 is a rotation it will always 
        be a substring on s1s1.
    Key Functions: 
        std::string::npos --> represents an error case in different cases, means until end of string
        std::find(const string& str, size_t pos = 0) --> essentially a c++ way of finding a substring within the calling string 
*/
bool arrays_n_strings_CH1::is_rotation_optimized(const std::string& s1, const std::string& s2) {
    size_t len = s1.size();
    if (len != s2.size() || len == 0)
        return false;
    std::string s1s1 = s1 + s1; 

    // find function here merely searches for a substring and returns npos if not found
    if(s1s1.find(s2) != std::string::npos) {
        return true;
    } else {
        return true;
    }
}

/********************************************HELPER METHODS****************************************/
bool arrays_n_strings_CH1::_is_palindrome( const std::string str ) {
    size_t len = str.size();
    for( unsigned int i = 0; i < len; ++i ) {
        if( str[i] != str[len - i - 1] )
            return false;
    }
    return true;
}

/*Helper method to build a frequency table*/
unsigned int* arrays_n_strings_CH1::_build_frequency_table( const std::string& str ) { 
    unsigned int* freq_table = new unsigned int[26];   // where index 0 is 'a' and index 25 is 'z'
    memset(freq_table, 0, 26);
    for( auto chr : str ) {
        int tmp = _get_char_index(chr);
        if( tmp != -1 )
            freq_table[tmp]++;
    }
    return freq_table;
}

/*
    This method will return an integer for the position of the character, non-letter chars
    will return -1 
    numerical difference between 'A' and 'a' is 32 
*/
unsigned int arrays_n_strings_CH1::_get_char_index( const char& chr ) {
    if( chr >= 'a' && chr <= 'z' ) {
        return (chr-'a');
    }
    else if ( chr >= 'A' && chr <= 'Z' ) {
        return (chr-'A');
    } else {
        return -1;
    }   
}

/*
    This function will check the input array conforms to the criteria that is needed for a phrase 
    to be a palindrone permutation, and that is for a character 
*/
bool arrays_n_strings_CH1::_check_max_one_odd(unsigned int* freq_table) {
    bool odd_found = false; 
    for(int i = 0; i < 26; ++i) {
        if ( freq_table[i]%2 == 1 ) {
            if(odd_found)   // at this point we already found a char that has freq so no a permutation
                return false;
            odd_found = true; 
        }
    }
    delete [] freq_table;
    return true;
}

/*2.1: Remove Duplicates from LinkedList, with temp buffer 0(n) Solution*/
// [ * * * * * * * ]
void linked_list_CH2::removeDupsWbuff(llnode* nd) {
    if (!nd) 
        return;
    bool dupFound = false;
    std::map<int, bool> mp;
    llnode* tmp = nullptr;
    llnode* prev = nullptr;
    while (nd!=nullptr) {
        if (mp.find(nd->data) == mp.end()) {  // Not found 
            mp[nd->data] = true;
            prev = nd;
        } else {  // we found a duplicate, deallocate and remove from ll
            prev->next = nd->next;
        }
        if (dupFound) {
            tmp = nd;
            nd = nd->next;
            delete tmp;
            dupFound = false;
        }
        nd = nd->next;
    }
}

/*2.1: Remove duplicates from linkedList, without tmp buffer, O(n^2) Solution*/
// [* * * * * *]
void linked_list_CH2::removeDups(llnode* nd) {
    using namespace std;
    if (!nd)
        return;
    llnode* toBeDeleted = nullptr;
    llnode* current = nd;
    llnode* runner = nullptr;

    while (current != nullptr) {
        runner = current; 
        while (runner->next != nullptr) {
            if (runner->next->data == current->data) {
                toBeDeleted = runner->next;
                runner->next = runner->next->next;
                delete toBeDeleted;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

/*2.2: Find Kth from end element*/
int linked_list_CH2::findKthFromEnd(llnode* nd, size_t kth, size_t len) {
    int rc = -1;
    if (!nd || (kth>len))
        return rc;  // normally throw an exception here 
    // so if we want the 2nd to last index of a 10 element 10-2 = 8th element so 7th index 
    size_t targetIndex = len - kth - 1;
    for (size_t i = 0; i < targetIndex; ++i) {
        nd = nd->next;
    }
    return nd->data;
}

/*2.2: Find Kth from end element length is not provided
    Approach: 
        Recursive approach, traverse down to end and recursively come back while keeping count
*/
int linked_list_CH2::findKthFromEndNoLen(llnode* nd, size_t kth) {
    if (!nd)
        return kth;
    size_t i = 0;
    return _findKthFromEndNoLen(nd, kth, i)->data;
}

llnode* linked_list_CH2::_findKthFromEndNoLen(llnode* nd, size_t kth, size_t& index) {
    if (!nd)
        return nullptr;
    llnode* tmp = _findKthFromEndNoLen(nd->next, kth, index);
    index+=1;
    if(index==kth)
        return nd;
    return tmp;
}

void linked_list_CH2::populateLL(linked_list& ll, size_t amt, size_t num_range) {
    std::random_device rd; 
    for(size_t i = 0; i < amt; ++i)
        ll.push_back(rd()%num_range);
}





