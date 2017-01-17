#include <iostream>
#include "problems.h"

using namespace std;
void display_input( int cnt, char** args );

int main( int argc, char* argv[] )
{
    string tmp( "This is a test, here we are   testing   testing " );
    arrays_n_strings::urlify( tmp );

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