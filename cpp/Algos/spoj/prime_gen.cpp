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


int __main() {
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

/*
Optimized School Method 
We can do following optimizations:

Instead of checking till n, we can check till √n because a larger factor of n must be a 
multiple of smaller factor that has been already checked.
The algorithm can be improved further by observing that all 
primes are of the form 6k ± 1, with the exception of 2 and 3. 
This is because all integers can be expressed as (6k + i) 
for some integer k and for i = -1, 0, 1, 2, 3, or 4; 2 divides (6k + 0), (6k + 2), (6k + 4); 
and 3 divides (6k + 3). So a more efficient method is to test if n is divisible by 2 or 3, 
then to check through all the numbers of form 6k ± 1. (Source: wikipedia)
 https://en.wikipedia.org/wiki/Primality_test
*/
bool is_prime(const uint32_t& x) {
	// check for fact or 3 
	if (x <= 3) return x > 1;

	// check if a factor of 2 or 3
	if (!(x & 1) || !(x % 3)) return false;
	
	// incrementing by 6 skips over multiples of 2 and 3
	// all primes fall in the form n = 6k ± 1 for
	// we start i at 5 because it cant be a factor of 2 or 3, 4 is even, so start at 5
	// we go to sqrt of x hence i*i <= x which is the same as i <= sqrt(x)
	// here we go from
	// i = 6k - 1
	// 5 = 6k - 1 ==> 11 = 6k - 1 ==> 17 = 6k - 1
	for (uint32_t i = 5; i*i <= x; i += 6) {
		// here check if x is divisible by 6k-1 or 6k+1
		if ( !(x%i) || !(x%(i+2)) )  // i = 6k - 1, so i+2 = 6k + 1
			return false;
	}
	return true;
}
