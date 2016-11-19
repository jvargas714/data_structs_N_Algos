#include <iostream>
#include <cstdio>
#include <vector>

/*
	This files contains misc problems outlined by various sources,
	implementations will be included in misc.cpp
*/

/*
 	1.1 Is unique: implement an algorithm to determine if a string has all unique characters. 
 	What if you could not use additional data structures?
*/
bool unique_chars( const std::string& );
// bool unique_chars( const char* );

/*
	1.2 Check permutation: Given two strings, write a function to decide if one is a permutation of
		the other.
*/
bool permutation( const std::string& );
bool permutation( const char* );

/*
	1.3 URLify: Write a method to replace all spaces in a string with '%20'. You may assume that the
	string has sufficient space at the end to hold the additional characters, and that you are given
	the true, length of the string
*/
std::string URLify( const std::string& );
char* URLify( const char* );

bool check_order(std::vector<int>& v);