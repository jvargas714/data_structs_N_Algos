#include "misc.h"
using namespace std;

int main()
{
	vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	bool rc = check_order( a );

	if(rc)
		cout << "it is in order!!!" << endl; 
	else
		cout << "out of order " << endl; 

	
	return 0;
}