#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, char* argv[]) {
	string str = "jay";
	string str2 = "kelsey";
	string str3 = "jay";

	for( int i = 1; i < argc; i++) {
		cout << argv[i] << endl;
	}

	cout << true << endl; 
	cout << (str == str2) << endl;
	cout << (str == str3) << endl;   // strings can be compared using the == operator 
	cout << 'z'-'a' << " " << 'Z'-'A' << endl; 
    return 0;
}