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
	// ll.push_back( 22 );
	// ll.push_back( 33 );
	// ll.push_back( 44 );
	// ll.push_back( 55 );
	// ll.push_back( 66 );

	// cout << ll.to_string() << endl;

	// ll.insert( 99, 3 );

	// cout << ll.to_string() << endl;

	// ll.insert( 111, 0 );

	// cout << ll.to_string() << endl;

	// ll.push_front( 333 );

	// cout << ll.to_string() << endl;

	// cout << "size(): " << ll.size() << endl;

	// cout << "deleting list --> " << endl; 
	// ll.delete_list();
	// cout << "size(): " << ll.size() << endl;

	for(int i = 0; i < 5000; i++)
	{
		int data = rand() % 1001;
		ll.push_back( data );
	}
	cout << ll.to_string() << endl;
	return 0;

}