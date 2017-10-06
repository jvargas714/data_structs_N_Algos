#include <iostream> // std::cout std::cin 
#include <cstdint>	// typedefs 
#include <chrono>	// std::chrono::high_resolution_clock
#include <cmath>	// std::sqrt
using namespace std;
using namespace std::chrono;
typedef unsigned int uint;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;
/*
	SPOJ problem: PRIME1 - Prime Generator
	Descr: 
		Input:
			The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines 
			there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

		Output:
			For every test case print all prime numbers p such that m <= p <= n, one number per line, 
			test cases separated by an empty line.
*/

void gen_primes(const uint32_t&, const uint32_t&);
bool is_prime(const uint32_t&);

int main() {
	uint32_t n_tests;
	uint32_t m, n;
	cin >> n_tests;

	t_point t1_bub, t2_bub;
	auto milli_sec = duration_cast<milliseconds>(t2_bub - t1_bub).count();
	auto micro_sec = duration_cast<microseconds>(t2_bub - t1_bub).count();
	
	for (uint32_t i = 0; i < n_tests; i++) {
		cin >> m >> n;

		t1_bub = hrc::now();
		gen_primes(m, n);
		t2_bub = hrc::now();
		
		milli_sec = duration_cast<milliseconds>(t2_bub - t1_bub).count();
		micro_sec = duration_cast<microseconds>(t2_bub - t1_bub).count();
		
		cout << "time of execution-->\n" << milli_sec << " msec\n" << micro_sec << " usec\n" << endl;
		cout << endl;
	}
	cin >> n;
	return 0;
}

// gen primes between m and n
void gen_primes(const uint32_t& m, const uint32_t& n) {
	for (uint32_t i = m; i <= n; ++i) {
		if (is_prime(i))
			cout << i << "\n";
	}
}

// check if prime or not 
bool is_prime(const uint32_t& x) {
	if (x <= 3)
		return x > 1;
	if (!(x & 1) || !(x % 3))
		return false;
	// incrementing by 6 skips over multiples of 2 and 3
	for (uint32_t i = 5; i*i <= x; i += 6) {
		if ( !(x%i) || !(x%(i+2)) )
			return false;
	}
	return true;
}
