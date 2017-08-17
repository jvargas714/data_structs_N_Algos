#include <iostream>
#include "problems.h"

using namespace std;
void display_input( int cnt, char** args );

int main( int argc, char* argv[] )
{
	string palinPhrase = "Tact Coa";
	if( arrays_n_strings::palindrome_permutation(palinPhrase) )
	{
		cout << palinPhrase << " is a palindrome_permutation!!" << endl;
	}
	else 
	{
		cout << palinPhrase << " is not a palindrome_permutation :(" << endl; 
	}
    return 0;
}

void display_input( int cnt, char** args )
{
    cout << "input: ";
    for( int i = 1; i < cnt; ++i )
    {
        cout << args[i] << " ";
    }
    cout << endl;
}