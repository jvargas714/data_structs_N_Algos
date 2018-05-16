#include <iostream>
#include <cstdio>
#include <cfloat>
#include <string>
#include <cstdint>
#include <vector>

using namespace std;
/*
 *
 * 1, 2, 3, 4, 5
 */
int main(int argc, char* argv[]) {
	std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t midpt = data.size()/2;
	while (midpt > 0) {
	    cout << data[midpt] << " ";
	    midpt /= 2;
	}
	cout << endl;
    return 0;
}