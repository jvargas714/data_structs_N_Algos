#include <iostream>
#include <fstream>
#include <vector>
#include "time.h"
#include <cstdlib>
using namespace std;

int main(void) 
{
    ifstream fstrm("trie_test2.input");
    string n, op, contact;
    fstrm >> n;
    fstrm >> op;
    fstrm >> contact;
    
    cout << n << endl;
    cout << op;
    cout << "\n" << contact << "\n";
    return 0;
}
