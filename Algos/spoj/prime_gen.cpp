#include <iostream>
#include <cstdint>
using namespace std;

void gen_primes(const unsigned int&, const unsigned int&);
bool is_prime(const unsigned int&);

int main() {
	unsigned int n_tests;
	unsigned int m, n;
	cin >> n_tests;
	
	for (unsigned int i = 0; i < n_tests; i++) {
		cin >> m >> n;
		gen_primes(m, n);
	}
	return 0;
}

// gen primes between m and n
void gen_primes(const unsigned int& m, const unsigned int& n) {
	for (int i = m; i <= n; ++i) {
		if (is_prime(i))
			cout << i << "\n";
	} cout << endl; 
}

// check if prime or not 
bool is_prime(const unsigned int& x) {
	if (x==1 || x==0)
		return false;
	for (unsigned int i = 2; i < x; ++i) {
		if (!(x%i))
			return false;
	}
	return true;
}
