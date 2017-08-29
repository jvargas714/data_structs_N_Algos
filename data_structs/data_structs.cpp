#include <cstdlib>          // rand()
#include <iostream>         // cout, endl
#include <vector>           // vector, size_t
#include <chrono>
#include "time.h"           // time(NULL)
#include "linked_list.h"

using namespace std; 

int main()
{
	srand( time(NULL) );
	linked_list ll;
	ll.push_back( 22 );
	ll.push_back( 33 );
	ll.push_back( 44 );
	ll.push_back( 55 );
	ll.push_back( 66 );

	cout << ll.to_string() << endl;

	cout << "inserting 99 to the 3rd index" << endl;
	ll.insert( 99, 3 );

	cout << ll.to_string() << endl;

	cout << "removing 2nd index" << endl;
	ll.remove(5);

	cout << ll.to_string() << endl;
	
	cout << "Testing Copy Constructor..." << endl;
	linked_list newll(ll);

	cout << endl;
	cout << newll.to_string() << endl;

	cout << "Testing subscripting of LList." << endl; 
	for(int i = 0; i < ll.size(); i++)
		cout << ll[i] << endl;

	cout << "Assigning 999 to index 2" << endl; 
	ll[2] = 999;
	for(int i = 0; i < ll.size(); i++)
		cout << ll[i] << endl;
	
	return 0;
}