#include <cstdint>
#include <iomanip>
#include <sstream>

template<typename T>
bool jaystd::bit_banger::is_even(const T& t) { 
	if ((t&1) == 0) 
		return true; 
	else 
		return false; 
}

template<typename T>
bool jaystd::bit_banger::is_nth_bit_set(const T& t, size_t nth) { 
	if (nth > (sizeof(nth)*8-1)) 
		return false;

	if (t & (static_cast<size_t>(1)<<nth)) 
		return true; 
	else 
		return false; 
}

template<typename T>
bool jaystd::bit_banger::set_nth_bit(T& t, size_t nth) { 
	if (nth > (sizeof(nth)*8-1)) 
		return false; 
	t|=(static_cast<size_t>(1)<<nth); 
	return true; 
}

template<typename T>
bool jaystd::bit_banger::unset_nth_bit(T& t, size_t nth) {
	if (nth > (sizeof(nth)*8-1)) 
		return false;
	t&=~(static_cast<size_t>(1)<<nth);
	return true;
}


template<typename T>
bool jaystd::bit_banger::toggle_nth_bit(T& t, size_t nth) {
	unsigned char* t_ptr = reinterpret_cast<unsigned char*>(&t);
	size_t byte_index = (nth/8);
	uint32_t bit_loc = nth%8;
	if (byte_index > sizeof(t))
		return false;
	t_ptr[byte_index]^=(1<<bit_loc);
	return true;
}

template<typename T>
std::string jaystd::bit_banger::bits_to_string(T& t, size_t nbits, bool spaces) {
	std::stringstream ss;
	ss <<"\t";
	size_t cnt = 0;
	const uint8_t* t_ptr = reinterpret_cast<unsigned char*>(&t);
	uint32_t tmp, ncols=(spaces)?0:1;
	uint8_t mask = 0x80;
	size_t nbytes = (nbits/8);
	if (nbits%8)
		nbytes++;
	for (uint32_t i = 0; i < nbytes; ++i) {
		for ( uint32_t j = 0; j < sizeof(uint8_t)*8; j++) {
			(is_little_endian()) ? tmp = t_ptr[(nbytes-1)-i]&mask : tmp = t_ptr[i]&mask;
			ss << std::setw(1) << ((tmp>0)?"1":"0");
			if (++cnt == nbits)
				break;
			mask>>=1;
		}
		if (spaces) {
			ss << " ";
			ncols++;
		}
		if (!(ncols%8))
			ss << "\n\t";
		mask=0x80;
	}
	return ss.str();
}

// LSB located in the first memory location 
bool jaystd::bit_banger::is_little_endian() {
	uint32_t tmp = 1;
	return (((unsigned char*)&tmp)[0])?true:false;
}

// sets the rightmost 1 bit to 0
template<typename T>
void jaystd::bit_banger::turn_off_rht_most_1bit(T& t) {
	t&=(x-1);
}

// finds the rightmost 1 bit and sets all other bits to zero
template<typename T>
void jaystd::bit_banger::isolate_rht_most_1bit(T& t) {
	t&=-t;
}

