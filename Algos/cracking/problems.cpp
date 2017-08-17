#include "problems.h"
#include <vector>
#include <cstring>
#include <algorithm>
typedef unsigned int uint;
/*
 * 1.1
 * Implement an algorithm to determine if a string has all unique characters.
 * What if you cannot use additional data structures?
 * Solution: O(n)
 */
bool arrays_n_strings::is_unique( const std::string& str )
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
bool arrays_n_strings::check_permutation( std::string str1, std::string str2 )
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
void arrays_n_strings::urlify( std::string& str )
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
bool arrays_n_strings::palindrome_permutation( const std::string& str )
{
    size_t len = str.size();
    if( len == 0 ) return false;
    if( len == 2 && str[0] == str[1] ) return false;
    unsigned int* freq_table = _build_frequency_table( str );
    return _check_max_one_odd(freq_table);    
}

bool arrays_n_strings::_is_palindrome( const std::string str )
{
    size_t len = str.size();
    for( unsigned int i = 0; i < len; ++i )
    {
        if( str[i] != str[len - i - 1] )
            return false;
    }
    return true;
}

/*Helper method to build a frequency table*/
unsigned int* arrays_n_strings::_build_frequency_table( const std::string& str ) 
{ 
    unsigned int* freq_table = new unsigned int[26];   // where index 0 is 'a' and index 25 is 'z'
    memset(freq_table, 0, 26);
    for( auto chr : str ) 
    {
        int tmp = get_char_index(chr);
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
unsigned int arrays_n_strings::get_char_index( const char& chr )
{
    if( chr >= 'a' && chr <= 'z' ) // lowercase 
    {
        return (chr-'a');
    }
    else if ( chr >= 'A' && chr <= 'Z' ) 
    {
        return (chr-'A');
    }
    else // non-letter char 
    {
        return -1;
    }   
}

/*
    This function will check the input array conforms to the criteria that is needed for a phrase 
    to be a palindrone permutation, and that is for a character 
*/
bool arrays_n_strings::_check_max_one_odd(unsigned int* freq_table)
{
    bool odd_found = false; 
    for(int i = 0; i < 26; ++i)
    {
        if ( freq_table[i]%2 == 1 )
        {
            if(odd_found)   // at this point we already found a char that has freq so no a permutation
                return false;
            odd_found = true; 
        }
    }
    delete [] freq_table;
    return true;
}
