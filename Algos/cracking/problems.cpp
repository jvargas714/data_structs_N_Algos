#include "problems.h"
#include <vector>
#include <string>

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

    sort( str1.begin(), str1.end() );
    sort( str2.begin(), str2.end() );
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
 * input: Tact Coa
 * */
bool arrays_n_strings::palindrome_permutation( const std::string& str )
{
    size_t len = str.size();
    if( len == 0 ) return false;
    if( len == 2 && str[0] == str[1] ) return false;
    if( (len % 2) == 0 )    // even case
    {
        // here is where eveny character must appear an even number of times
    }
    else                    // odd case
    {
        // here every character must appear an even amount of time but one char must appear once.
    }
}

bool arrays_n_strings::is_palindrome( const std::string str )
{
    size_t len = str.size();
    for( int i = 0; i < len; ++i )
    {
        if( str[i] != str[len - i - 1])
            return false;
    }
    return true;
}