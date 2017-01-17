#ifndef CRACKING_PROBLEMS_H
#define CRACKING_PROBLEMS_H
#include <iostream>

class arrays_n_strings
{
public:
    arrays_n_strings(){}
    /*1.1*/
    static bool is_unique( const std::string& );

    /*1.2*/
    static bool check_permutation( std::string, std::string );

    /*1.3*/
    static void urlify( std::string& );

    /*1.4*/
    static bool palindrome_permutation( const std::string& );

    bool arrays_n_strings::is_palindrome( const std::string );

};

#endif //CRACKING_PROBLEMS_H
