#include <iostream>
#include <chrono>
#include "time.h"           // time(NULL)
#include <cstdlib>          // rand()
#include <vector>

using namespace std::chrono;
using namespace std;
typedef unsigned int uint;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;

t_point t1_bub = hrc::now();
    // bubble_sort( vect_1 );
    // t2_bub = hrc::now();
    // milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    // micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();

int64_t fib( int n )
{
	if( n <= 1 ) return n;

	return fib(n-1) + fib(n-2);
}

// fib calc with memoization
int64_t fib_mem( int n, vector<int64_t>& f )
{
	if( n <= 1 ) return n;

	if( f[n] == -1 ) // result of this is not cached
		f[n] = fib_mem(n-1, f) + fib_mem(n-2, f);

	return f[n];
}

int main()
{
	int n;
	std::cout << "Enter number n for fibonacci calculation.[0...92]" << endl;
	cin >> n;

	vector<int64_t> f(100, -1);
	t_point t1_bub;
	t_point t2_bub;

	/*
	t1_bub = hrc::now();
	std::cout << "fib(" << n << "): " << fib(n) << std::endl;
	t2_bub = hrc::now();
	

	auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
	auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();


	std::cout << "fib(" << n << "): took " << milli_sec << "ms" << std::endl;
	std::cout << "fib(" << n << "): took " << micro_sec << "us\n\n" << std::endl;
	*/

	// with memoization
	t1_bub = hrc::now();
	std::cout << "fib_mem(" << n << "): " << fib_mem(n, f) << std::endl;
	t2_bub = hrc::now();

	auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
	auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();

	std::cout << "fib_mem(" << n << "): took " << milli_sec << "ms" << std::endl;
	std::cout << "fib_mem(" << n << "): took " << micro_sec << "us\n\n" << std::endl;

	return 0;
}