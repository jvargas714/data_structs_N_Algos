#include <iostream> 

using namespace std; 

int main()
{
	int sum;
	for( int i = 0; i < 100; i++ )
	{
		sum+=i;
	}

	cout << "sum of every number between 0-100: " << sum << endl;

	return 0; 
}