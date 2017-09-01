#ifndef CRACKING_PROBLEMS_H
#define CRACKING_PROBLEMS_H
#include <iostream>
#include "node.h"
#include "linked_list.h"

#define ASCII_Z 90
#define ASCII_A 65
#define ASCII_a 97
#define ASCII_z 122

/*
    Questions from cracking the coding interview 
*/

/* CHAPTER 1 QUESTIONS*/
namespace arrays_n_strings_CH1 
{
    /*1.1 Is_Unique*/
    bool is_unique( const std::string& );

    /*1.2: Check Permutation*/
    bool check_permutation( std::string, std::string );

    /*1.3: Urlify*/
    void urlify( std::string& );

    /*1.4: Palindrome Permutation*/
    bool palindrome_permutation( const std::string& );

    /*1.5: One Away*/
    bool one_away(const std::string&, const std::string&);

    /*1.6: String Compression*/
    std::string string_compression(const std::string&);

    /*1.7: Rotate Matrix*/
    std::string rotate_matrix(std::string&);

    /*1.9: String Rotation*/
    bool is_rotation(const std::string&, const std::string&);
    bool is_rotation_optimized(const std::string&, const std::string&);

    // HELPER Functions
    unsigned int* _build_frequency_table( const std::string& str );
    bool _is_palindrome( const std::string );
    bool _check_max_one_odd(unsigned int* freq_table);
    unsigned int _get_char_index( const char& chr );
};

namespace linked_list_CH2
{
    /*2.1: Remove Duplicates from LinkedList, without temop buffer*/
    void removeDupsWbuff(llnode*);
    void removeDups(llnode*);

    /*2.2: find kth to end of the linkedlist (size known)*/
    int findKthFromEnd(llnode* nd, size_t kth, size_t len);
    int findKthFromEndNoLen(llnode* nd, size_t kth);

    /*2.3: Delete Middle Node*/
    bool deleteNodeInMiddle(llnode*);

    /*2.4: partition*/
    llnode* partition(llnode* root, int partPt);


    // HELPERs 
    void populateLL(linked_list& ll, size_t amt, size_t num_range);
    llnode* _findKthFromEndNoLen(llnode* nd, size_t kth, size_t& i);
    void display_ll(const llnode*);
}

#endif //CRACKING_PROBLEMS_H
