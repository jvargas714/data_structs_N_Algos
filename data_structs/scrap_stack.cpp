#include "stack.h"
#include <iostream>

using namespace std;

int main()
{

    stack<int> stk( 55 );
    stk.push( 12 );
    int xx = 789;
    stk.push( 456 );
    stk.push( xx );

    cout << "stk.size(): " << stk.size() << endl;

    cout << stk.top() << endl;
    stk.pop();
    cout << stk.top() << endl;
    stk.pop();
    cout << stk.top() << endl;
    stk.pop();
    cout << stk.top() << endl;
    stk.pop();
    return 0;
}