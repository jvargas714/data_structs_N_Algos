#include <iostream>
#include <vector>
#include "time.h"
#include <cstdlib>
using namespace std;
typedef vector< vector<char> > matrix; 

class node 
{
    node* left;
    node* right;
    int data;

public:
    bool operator < ( node nd ) { return this->data < nd.data;  }
    bool operator > ( node nd ) { return this->data > nd.data; }
    bool operator == ( node nd ) { return this->data == nd.data; }    
    node() : data( 0 ), left( nullptr ), right( nullptr ){}
    node( int input ) : data( input ), left( nullptr ), right( nullptr ){}
};

int main(void) 
{
	srand(time(NULL));

	for(int i = 0; i < 50; i++)
		cout << rand() % 10 << endl;

    return 0;
}
