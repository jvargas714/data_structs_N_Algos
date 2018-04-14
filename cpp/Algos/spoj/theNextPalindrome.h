#pragma once
#include <string>

bool is_palindrome(const std::string&);
void find_next_palindrome(std::string&);
void insert_int_pair(std::string&, uint32_t, uint32_t);
void process_1_digit_num(std::string&);
void process_2_digit_num(std::string&);
void process_3_digit_num(std::string&);
void remove_leading_zeros(std::string&);
bool all_zeros(const std::string&);
void increment_by_one(std::string&, uint32_t);
//void carry_operation(std::string&, uint32_t, uint32_t);
void carry_operation(std::string&, uint32_t);
