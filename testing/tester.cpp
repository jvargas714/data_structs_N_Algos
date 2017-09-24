#include <iostream>
#include <cstdio>
#include <cfloat>

using namespace std;

int main(int argc, char* argv[]) {
	float x = .7234;
	float tmp = x;
	cout << "num of sig digs in floating pt" << DBL_DIG << endl; 
    for(int i = 0; i < 7; i++) {
        tmp = tmp*10;
        cout << tmp << endl;
        cout << (int)tmp << endl;
        tmp = tmp-(int)tmp;
        cout << "after subtraction: " << tmp << endl;
        cout << endl;
    }

    return 0;
}