#include <iostream>
#include <vector>
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
	node* nd1 = new node( 15 );
	node* nd2 = new node( 20 );
	node* nd3 = new node( 20 );

	if( *nd2 > *nd1 ){
		cout << "this is true " << endl; 
	}
	else
	{
		cout << "that shit aint true kiiiid!!!!" << endl; 
	}

	if( *nd2 == *nd3 ) {
		cout << "they are equal" << endl;
	}
	else{
		cout << "they are not equal..." << endl; 
	}

    return 0;
}
