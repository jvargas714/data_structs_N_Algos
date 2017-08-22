#include <iostream>
#include "problems.h"

using namespace std;
void display_input( int cnt, char** args );

int main( int argc, char* argv[] )
{
	string palinPhrase = "Tact Coa";
	string a, b;
	if( argc == 3 ) {
		a=argv[1];
		b=argv[2];
	} else {
		a=argv[1];
	}

	cout << arrays_n_strings::string_compression(a) << endl;
	
    return 0;
}

void display_input( int cnt, char** args ) {
    cout << "input: ";
    for( int i = 1; i < cnt; ++i ) {
        cout << args[i] << " ";
    }
    cout << endl;
}
