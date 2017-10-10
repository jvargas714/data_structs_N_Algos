#include <iostream>
#include <string>
#include <cstdint> 
#include <sstream>
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
std::string find_next_palindrome(const std::string&);
void insert_int_pair(std::string&, uint32_t, uint32_t);
std::string increment_by_one(const std::string&);

int main() {
	uint32_t n;
	std::string val, result;
	std::cin >> n;
	for (uint32_t i = 0; i < n; ++i) {
		std::cin >> val;
		result = find_next_palindrome(val);
		std::cout << result << std::endl;
	}
	std::cout << is_palindrome("818") << std::endl;
	std::cin >> n;
	return 0;
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

/*function that puts char representations of each number to the front and back of the number*/
void insert_int_pair(std::string& str, uint32_t i, uint32_t a) {
	char tmp = static_cast<char>(a + ASCII_ZERO);
	str[i] = tmp;
	str[str.size() - i - 1] = tmp;
}

std::string increment_by_one(const std::string& val)
{	
	int tmp = std::stoi(val);
	return std::to_string(++tmp);
}

/*calculate the next palindrome that is greater than the provided string*/
std::string find_next_palindrome(const std::string& str_val) {
	uint32_t tmp, tmp2;
	if ( (str_val.size()==3) && (str_val != "999") ) {
		tmp = str_val[0]-ASCII_ZERO;
		tmp2 = str_val[2]-ASCII_ZERO;
		uint32_t tmp3 = 0;
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
		}
		return std::to_string(tmp * 100 + tmp3 * 10 + tmp2);
	}

	std::string result = increment_by_one(str_val);
	std::cout << "after incr by 1 " << result << std::endl;
	size_t len = result.size();
	bool carry = false;
	bool odd = false;

	for (size_t i = 0; i < len / 2; ++i) {
		tmp = result[i]-ASCII_ZERO;
		tmp2 = result[len-i-1]-ASCII_ZERO;
		if (carry) {
			tmp2++;
			tmp = tmp2;
			carry = false;
			insert_int_pair(result, i, tmp);
			std::cout << "after insert_int_pair: " << result << std::endl; 
			continue;
		}
		if (tmp < tmp2)
			carry = true;
		tmp2 = tmp;
		insert_int_pair(result, i, tmp);
		std::cout << "after insert_int_pair (carry set true): " << result << std::endl;
	}
	return result; 
}
