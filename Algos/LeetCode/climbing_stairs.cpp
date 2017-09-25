#include <iostream>
#include <algorithm>
#include <cstdint>
#include <stack> 
#include <map>
#include <vector>
#include <iomanip>
using namespace std;

int climbingSteps(int, int, vector<int>&);

int main(int argc, char* argv[]) {
	int input;
	cin >> input;
	vector<int> memo(input+1, 0);
	cout << climbingSteps(0, input, memo) << endl;
	return 0;
}


int climbingSteps( int i, int n, vector<int>& memo ) {
	if (i > n) return 0;
	if (i == n) return 1;
	if (memo[i] > 0) return memo[i];
	memo[i] = climbingSteps(i+1, n, memo) + climbingSteps(i+2, n, memo);
	return memo[i];
}


