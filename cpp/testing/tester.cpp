#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cfloat>
#include <string>
#include <cstdint>
#include <vector>
#include <sstream>
#include <iomanip>
#include "../utility/utility.h"

using namespace std;

// A utility funtion to find maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }

// A utility funtion to find maximum of three integers
int max(int a, int b, int c) { return max(max(a, b), c); }

// Find the maximum possible sum in arr[] auch that arr[m] is part of it
int maxCrossingSum(int arr[], int l, int m, int h) {
	LOG << "l: " << l << " mid: " << m << " r: " << h << endl;
	// Include elements on left of mid.
	int sum = 0;
	int left_sum = INT32_MIN;
	for (int i = m; i >= l; i--)
	{
		sum = sum + arr[i];
		if (sum > left_sum)
			left_sum = sum;
	}

	// Include elements on right of mid
	sum = 0;
	int right_sum = INT32_MIN;
	for (int i = m+1; i <= h; i++)
	{
		sum = sum + arr[i];
		if (sum > right_sum)
			right_sum = sum;
	}
	LOG << "left sum: " << left_sum << " right sum: " << right_sum << endl;
	LOG << "cross sum: " << (left_sum+right_sum) << endl;
	// Return sum of elements on left and right of mid
	return left_sum + right_sum;
}

// Returns sum of maxium sum subarray in aa[l..h]
int maxSubArraySum(int arr[], int l, int h) {
	LOG << "l: " << l << " r: " << h << endl;
	// Base Case: Only one element
	if (l == h)
		return arr[l];

	// Find middle point
	int m = (l + h)/2;

	/* Return maximum of following three possible cases
       a) Maximum subarray sum in left half
       b) Maximum subarray sum in right half
       c) Maximum subarray sum such that the subarray crosses the midpoint */
	return max(maxSubArraySum(arr, l, m),
			   maxSubArraySum(arr, m+1, h),
			   maxCrossingSum(arr, l, m, h));
}

/*Driver program to test maxSubArraySum*/
int main() {
	uint32_t n = 12345;
	std::stringstream ss;
	ss << std::hex << n << END;
	std::cout << ss.str() << END;
	return 0;
}

