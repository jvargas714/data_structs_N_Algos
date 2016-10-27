#include "heap.h"

using namespace std;

int main(int arc, char* argv[] )
{
	vector<int> data = { 41, 14, 32, 90, 23, 5, 87, 53, 64, 50 };
	min_heap hp;

	for( int& el : data )
		hp.insert( el );
	
	cout << "After being filled..." << endl;
	hp.display();
	
	cout << "size: " << hp.size() << endl;

	unsigned int heap_size = hp.size();

	for( unsigned int i=0; i<heap_size; i++ )
	{
		cout << "\nAfter removing min ... " << endl;
		hp.extract_min();
		hp.display();
	}
	return 0;
}