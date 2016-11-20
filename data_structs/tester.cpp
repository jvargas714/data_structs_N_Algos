#include <iostream>
#include <fstream>
#include <vector>
#include "time.h"
#include <cstdlib>
#include <iomanip>
#include "heap.h"
using namespace std;

int main(void) 
{

	int a = 2;
	int b = 3;
	float sum = a + b;
	float ave = (float)sum / (float)2; 
	float e = 56;
	float f = .123;

	vector<int> vv;
	vv.push_back(a);
	vv.push_back(b);
	float c = (float)vv[0];
	float d = (float)vv[1];
	cout << setprecision(1) << c << " and  " << d << endl; 
	cout << setprecision(1) << e << " and " << f << endl;
	cout << setprecision(5) << c + e << endl; 

	double res = (c + d) / 2.0;

	cout << setprecision(1) << res << endl;
	cout << setprecision(1) << "ave: " << 2.0 << endl; 


	printf("%.1f\n", );
    return 0;
}
