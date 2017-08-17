#ifndef CRACKING_PROBLEMS_H
#define CRACKING_PROBLEMS_H
#include <iostream>

#define ASCII_Z 90
#define ASCII_A 65
#define ASCII_a 97
#define ASCII_z 122

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

private:    
    static unsigned int* _build_frequency_table( const std::string& str );
    static bool _is_palindrome( const std::string );
    static bool _check_max_one_odd(unsigned int* freq_table);
    static unsigned int get_char_index( const char& chr );

};

#endif //CRACKING_PROBLEMS_H
