#include <iostream>
#include <cstdint>
using namespace std;
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

void gen_primes(const unsigned int&, const unsigned int&);
bool is_prime(const unsigned int&);

int main() {
	unsigned int n_tests;
	unsigned int m, n;
	cin >> n_tests;
	
	for (unsigned int i = 0; i < n_tests; i++) {
		cin >> m >> n;
		gen_primes(m, n);
		cout << endl;
	}
	return 0;
}

// gen primes between m and n
void gen_primes(const unsigned int& m, const unsigned int& n) {
	for (unsigned int i = m; i <= n; ++i) {
		if (is_prime(i))
			cout << i << "\n";
	}
}

// check if prime or not 
bool is_prime(const unsigned int& x) {
	if (x==2)
	    return true;
	if (x==1 || x==0 || !(x%2))
		return false;
	for (unsigned int i = 3; i < x; ++i) {
		if (!(x%i))
			return false;
	}
	return true;
}
