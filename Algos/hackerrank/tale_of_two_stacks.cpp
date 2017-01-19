#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

void transfer_elements( stack<int>& from_stk, stack<int>& to_stk ){
    while( !from_stk.empty() ){
        to_stk.push( from_stk.top() );
        from_stk.pop();
    }
}

class MyQueue {
    public:
        stack<int> new_top_stk;
        stack<int> old_top_stk;
    
        void push(int x) {  // op 1
        	//if( old_top_stk.size() )
              //  transfer_elements( old_top_stk, new_top_stk );
        	new_top_stk.push( x );
        }

        // when popping the oldest element must go, which would be the first one to enter 
        void pop() {    // op 2
            if( !old_top_stk.empty() ){ // when old top stk is not empty, top item is next to leave
                old_top_stk.pop();
                return;
            }
            else {   // case where old top stack is empty and needs a refill
                    transfer_elements( new_top_stk, old_top_stk );
            }
        	old_top_stk.pop();
        }

        int front() { // op 3 -- oldest element gets revealed
            if( old_top_stk.empty() ){
                transfer_elements( new_top_stk, old_top_stk );
            }
        	return old_top_stk.top();
        }
};

int main() {
    MyQueue q1;
    int q, type, x;
    ifstream strm( "tale_of_two_stacks_12.input" );
    strm >> q;
    
    for(int i = 0; i < q; i++) {
        strm >> type;
        if(type == 1) {
            strm >> x;
            q1.push(x);
        }
        else if(type == 2) {
            q1.pop();
        }
        else cout << q1.front() << endl;
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}


