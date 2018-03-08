#include <iostream>
#include <algorithm>
#include <cstdint>
#include <stack> 
#include <map>
#include <vector>
#include <iomanip>
#include <string>
#include <chrono>

//--------------------------------------typedefs & namespace----------------------------------------
using namespace std;
using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;

//-----------------------------------------declarations---------------------------------------------
// display contents of an iterable 
template<typename T>
void display(const T& t);

// handle input args from terminal 
template<typename T>
vector<T> handle_input(int argc, char* argv[]);

// algo solution 
int maxProfit(vector<int>& prices);

//------------------------------------------execution-----------------------------------------------
int main(int argc, char* argv[]) {
	auto input = handle_input<int>(argc, argv);
	t_point t1_bub, t2_bub;
	auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    t1_bub = hrc::now();
	maxProfit(input);
	t2_bub = hrc::now();
	milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    cout << "time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << endl;
	return 0;
}




//----------------------------------------Implementations ------------------------------------------

template<typename T>
void display(const T& t) {
	cout << "container size: " << t.size() << endl;
	for (auto& el : t)
		cout << el << " ";
	cout << endl;
}

template<typename T>
vector<T> handle_input(int argc, char* argv[]) {
	vector<T> input;
	for (int i = 1; i < argc; i++) {
		input.push_back(stoi(argv[i]));
	}
	display(input);
	cout << "------------------------------------------------------------------------------"<< endl;
	return input;
}

int maxProfit(vector<int>& prices) {
	return 0;
}
