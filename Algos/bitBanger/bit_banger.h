#include <cstddef>
#include <iostream>

namespace jaystd {
	/* methods in this namespace are based on the following convention
		- functions cound bit positions from right to left 
		- bit position 0 in the following example is set high
			00000001   <<< bit position 0 set high
			10000000   <<< bit position 7 set high 
	*/
	namespace bit_banger {
		// checks to see if value is even or not 
		template<typename T>
		bool is_even(const T& t);
		
		// checks to see if the nth bit is set, bits are counted from the right to left
		// bit 0 is the first bit on the right
		template<typename T>
		bool is_nth_bit_set(const T& t, size_t nth);
		
		// set nth bit
		template<typename T>
		bool set_nth_bit(T& t, size_t nth);

		// unset the nth bit
		template<typename T>
		bool unset_nth_bit(T& t, size_t nth);
		
		// toggle bit 
		template<typename T>
		bool toggle_nth_bit(T& t, size_t nth);
		// bool toggle_nth_bit(const char*, size_t);

		// to string method, with array types the first indexed byte will be shown
		// on the right for little endian systems, imagine concatting all bytes in array 
		// to one large literal type
		template<typename T>
		std::string bits_to_string(T& t, size_t nbits, bool spaces=false);

		// determine if system is little or big endian
		bool is_little_endian();
	}
}

// link to implementations 
#include "bit_banger.imp.h"
