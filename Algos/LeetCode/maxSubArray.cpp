#include <iostream>
#include <algorithm>
#include <cstdint>
#include <stack> 
#include <map>
#include <vector>
#include <iomanip>
#include <string>
#include <climits>
#include <chrono>

// typedefs & namespace
using namespace std;
using namespace chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;


template<typename T>
void display(const T& t);
void tester();
int accum(vector<int>::iterator, vector<int>::iterator);

// brute force O(n^2)
int maxSubArray(vector<int>& nums) {
    if (nums.size()==0)
        return 0;
    if (nums.size()==1)
        return nums[0];
    int sum = *max_element(nums.begin(), nums.end());
    cout << "init sum: " << sum << endl; 
    int tmp = INT_MIN;
    int cnt = 0;
    for(unsigned int i = 0; i < nums.size(); ++i) {
    	for ( unsigned int j = i+1; j <= nums.size(); ++j) {
	        tmp = accum(nums.begin()+i, nums.begin()+j);
	        if (tmp > sum) {
	            sum = tmp;
	        }
    		cnt++;
    	}
    }
    cout << "iterations " << cnt << endl;
    return sum;
}

void tester() {
	vector<int> v = {-2, -1, 5, 4};
	cout << *max_element(v.begin(), v.end()) << endl;
	cout << accum(v.begin(), v.end()) << endl; 
}

// 0(n) solution
int maxSubArray2(vector<int>& nums) {
	if (nums.size() == 0)
		return 0;
	if (nums.size() == 1)
		return nums[0];
	
	int result = nums[0];
	int sum = 0;

	for (size_t i = 0; i < nums.size(); i++) {
		sum += nums[i];
		result = max(sum, result);
		sum = max(sum, 0);	 // if sum drops below zero then reset sum
	}
	return result;
}

/* 
	dynamic programming version 0(n) solution 
*/

int maxSubArray3(vector<int>& nums) {
	int n = nums.size();
	vector<int> dp(n, 0);
	dp[0] = nums[0];
	int sum = dp[0];

	for (int i = 1; i < n; i++) {
		dp[i] = nums[i] + (dp[i-1] > 0) > dp[i-1]:0;
		sum = max(sum, dp[i]);
	}
	return sum;
}

/*
	Divide and conquer solution 0(n)
	Recursive
*/
int maxSubArray4() {
	
}


int main(int argc, char* argv[]) {
	vector<int> vect;
	t_point t1_bub, t2_bub;
	auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	cout << "size of vector " << (argc-1) << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	for ( int i = 1; i < argc; ++i)
		vect.push_back(stoi(argv[i]));

	cout << "\ninput: ";
	display(vect); 

    t1_bub = hrc::now();
	int sum = maxSubArray2(vect);
	t2_bub = hrc::now();

	cout << "result: " << sum << endl; 

	milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    
    cout << "time of execution: " << milli_sec << "msec\t" << micro_sec << "usec" << endl;
	// tester();
	return 0;
}



int accum(vector<int>::iterator a, vector<int>::iterator b) {
	int sum = 0;
	for (auto it = a; it!=b; it++) {
		sum += *it;
		// cout << "sum: " << sum << endl; 
	}
	return sum;
}

template<typename T>
void display(const T& t) {
	for (auto& el : t)
		cout << el << " ";
	cout << endl;
}



