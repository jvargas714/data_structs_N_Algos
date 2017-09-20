#include "bit_banger.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
using namespace jaystd;
using namespace std;

void test_bbanger_functions();
string display(const unsigned char* buff, size_t len);

int main(int argc, char* argv[]) {

	test_bbanger_functions();
	return 0;
}

void test_bbanger_functions() {
	int w = 0x00;
	int x = 76; 
	int y = 255;
	size_t z = 0x40000000;  // 30th bit set, decimal value: 1073741824
	string result="";

	(bit_banger::is_even(x)) ? result = "even\n" : result = "odd\n";
	cout << "\n" << x << " is " << result << endl;



	(bit_banger::is_even(y)) ? result = "even\n" : result = "odd\n";
	cout << y << " is " << result << endl;



	(bit_banger::is_nth_bit_set(z, 30)) ? result = "true\n" : result = "false\n";
	cout << std::hex << "is the 30th bit set on 0x" << z << " result: " << result << endl;



	cout << std::hex << "setting the 30th index bit on 0x" << w << " result: 0x";
	bit_banger::set_nth_bit(w, 30);



	cout << std::hex << w << "\n\nunsetting the 30th index bit on 0x" << w << " result: 0x";
	bit_banger::unset_nth_bit(w, 30);
	cout << w << "\n" << endl;



	unsigned char buff[16];
	memset(buff, 0, sizeof(buff));
	string buffstr = display(buff, 16);
	size_t nth = 7;
	cout << dec << "buffer:\n" << buffstr << "\ntoggling the " << nth << "th index bit" << endl;
	bit_banger::toggle_nth_bit(buff, nth);
	buffstr = display(buff, 16);
	cout << hex << "modified buff: \n" << buffstr << endl;



	cout << hex << "int zeroed out: 0x" << w << " ";
	cout << "toggling the 30th index bit, result: 0x";
	bit_banger::toggle_nth_bit(w, 30);
	cout << w << "\n" << endl;

	result = bit_banger::bits_to_string(x, sizeof(x)*8, true);
	cout << "Displaying 0x" << x << " in binary --->\n" << result << endl;

	cout << "Displaying buffer contents: \n" << bit_banger::bits_to_string(buff, sizeof(buff)*8, true) << endl;

	bool endianness = bit_banger::is_little_endian();
	if (endianness)
		cout << "system is is a little endian" << endl;
	else 
		cout << "system is a big endian" << endl; 
}


string display(const unsigned char* buff, size_t len) {
	stringstream ss;
	ss << hex << "\t";
	size_t cnt = 0;
	for( unsigned int i = 0; i < len; i++) {
		ss << "0x";
		ss << std::setfill('0') << setw(2) << static_cast<unsigned int>(buff[i]) << " ";
		if (!(++cnt%8)) {
			ss << "\n\t";
		}
	}
	return ss.str();
}
