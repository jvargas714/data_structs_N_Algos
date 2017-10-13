#include <iostream>		// std::cout, std::cin
#include <string>		// std::string 
#include <cstdint>		// uint32_t
#include <sstream>		// std::stringstream
#include <algorithm>	// std::remove_if(...)
const unsigned int ASCII_ZERO = 48;
/*
Description:
A positive integer is called a palindrome if its representation in the decimal system is the same when read from
left to right and from right to left. For a given positive integer K of not more than 1000000 digits, write the
value of the smallest palindrome larger than K to output. Numbers are always displayed without leading zeros.

Input:
The first line contains integer t, the number of test cases. Integers K are given in the next t lines.

Output:
For each K, output the smallest palindrome larger than K.
*/

bool is_palindrome(const std::string&);
void find_next_palindrome(std::string&);
void insert_int_pair(std::string&, uint32_t, uint32_t);
void process_1_digit_num(std::string&);
void process_2_digit_num(std::string&);
void process_3_digit_num(std::string&);
void remove_leading_zeros(std::string&);
bool all_zeros(const std::string&);
void increment_by_one(std::string&, uint32_t);
void carry_operation(std::string&, uint32_t, uint32_t);

int main() {
	uint32_t n;
	std::string val, result;
	std::cin >> n;
	for (uint32_t i = 0; i < n; ++i) {
		std::cin >> val;
		find_next_palindrome(val);
		std::cout << val << std::endl;
	}
	std::cin >> n;
	return 0;
}

bool all_zeros(const std::string& str) {
	for (auto& el : str) {
		if (el != '0')
			return false;
	}
	return true;
}

void remove_leading_zeros(std::string& numstr) {
	if (all_zeros(numstr)) {
		numstr = "0";
		return;
	}
	numstr.erase(
		std::remove_if(numstr.begin(), numstr.end(), [](auto& el) { 
			static bool leading = true;
			if (el == '0' && leading) return true;  
			else {
				leading = false;
				return false;
			}
		} ), numstr.end()
	);
}

/*checks if integer (represented as a string) is a palindrome or not*/
bool is_palindrome(const std::string& x) {
	size_t len = x.size();
	for (size_t i = 0; i < len; ++i) {
		if (x[i] != x[len - i - 1])
			return false;
	}
	return true;
}

/*function that puts char representations of a to the front and back of the number*/
void insert_int_pair(std::string& str, uint32_t i, uint32_t a) {
	char tmp = static_cast<char>(a + ASCII_ZERO);
	str[i] = tmp;
	str[str.size() - i - 1] = tmp;
}

void process_1_digit_num(std::string& numstr) {
	uint32_t val = std::stoi(numstr);
	if (val == 9) {
		numstr = "11";
	}
	else {
		numstr = std::to_string(++val);
	}
}

void process_2_digit_num(std::string& str_val) {
	if (str_val == "99") {
		str_val = "101";
		return;
	}
	int val = std::stoi(str_val);
	do {
		val++;
		if (!(val % 11)) {
			str_val = std::to_string(val);
			break;
		}
	} while (val <= 99);
}

void process_3_digit_num(std::string& str_val) {
	uint32_t tmp  = str_val[0] - ASCII_ZERO;
	uint32_t tmp2 = str_val[2] - ASCII_ZERO;
	uint32_t tmp3 = str_val[1] - ASCII_ZERO;
	if (tmp < tmp2) {
		tmp2 = tmp;
		tmp3 = str_val[1] - ASCII_ZERO;
		tmp3++;
	}
	else if (tmp > tmp2) {
		tmp2 = tmp;
	}
	else { // they are equal
		tmp3 = str_val[1] - ASCII_ZERO;
		tmp3++;
	}
	if (tmp3 == 10) {
		tmp++;
		tmp2++;
		tmp3 = 0;
	}
	str_val = std::to_string(tmp * 100 + tmp3 * 10 + tmp2);
}

// increment string representation of integer by one
// i starts at last index
void increment_by_one(std::string& strval, uint32_t i) {
	uint32_t x = strval[i] - ASCII_ZERO;
	x++;
	if (x < 10) {
		strval[i] = static_cast<char>(x + ASCII_ZERO);
		return;
	}
	strval[i] = '0';
	if (i == 0) {
		strval.insert(0, 1, '1');
		return;
	}
	increment_by_one(strval, --i);
}

// increment all pairs from curr_idx up to limit
// TODO :: needs fixing 
void carry_operation(std::string& numstr, uint32_t curr_idx, uint32_t limit) {
	if (curr_idx == limit)
		return;
	uint32_t tmp = numstr[curr_idx] - ASCII_ZERO;
	tmp++;
	if (tmp == 10) {
		insert_int_pair(numstr, curr_idx, 0);
		carry_operation(numstr, ++curr_idx, limit);
	}
	else {
		insert_int_pair(numstr, curr_idx, tmp);
	}
	std::cout << "carry op : " << numstr << std::endl;
}

/*calculate the next palindrome that is greater than the provided string*/
void find_next_palindrome(std::string& str_val) {
	remove_leading_zeros(str_val);	
	size_t len = str_val.size();
	if (len == 2) {
		process_2_digit_num(str_val);
		return;
	}
	increment_by_one(str_val, len-1);
	if (len == 1)
		return;
	uint32_t tmp, tmp2, midpt;
	bool carry = false;
	bool odd = false;

	for (uint32_t i = 0; i < len / 2; ++i) {
		tmp = str_val[i]-ASCII_ZERO;
		tmp2 = str_val[len-i-1]-ASCII_ZERO;
		
		if (tmp == tmp2)
			continue;
		
		if (tmp < tmp2) {
			midpt = (len % 2) ? (len/2):(len/2-1);
			carry_operation(str_val, midpt, i);
		}
		tmp2 = tmp;
		insert_int_pair(str_val, i, tmp);
	}
}
