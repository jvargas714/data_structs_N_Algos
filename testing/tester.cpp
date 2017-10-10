#include <iostream>
#include <cstdio>
#include <cfloat>
#include <string> 

using namespace std;

int main(int argc, char* argv[]) {
	char x = 't';
	string name = "jay vargas";
	string name2 = "jay vargas";
	cout << "str cmp: " << (name == name2) << endl; 
	string tmp(name); 
	tmp.front() = 'h';
	tmp.back() = 'z';
	tmp[1] = x;
	cout << tmp << endl;
	cin >> x;
    return 0;
}