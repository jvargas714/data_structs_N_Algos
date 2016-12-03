#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

class MyQueue {
    public:
        stack<int> new_top_stk;
        stack<int> old_top_stk;
    
        void push(int x) {
        	if( old_top_stk.size() ){
        		while( !old_top_stk.empty() ){
        			new_top_stk.push( old_top_stk.top() );
        			old_top_stk.pop();
        		}
        	}
        	new_top_stk.push( x );
        }

        // when popping the oldest element must go, which would be the first one to enter 
        void pop() {
            if( !old_top_stk.empty() ){   // when old top stk is not empty, top item is next to leave
                old_top_stk.pop();
                return;
            }
            else{   // case where old top stack is empty and needs a refill
                if( !new_top_stk.empty() ){
                   while( !new_top_stk.empty() ){ // cpy so that oldest is now at the top 
        		      old_top_stk.push( new_top_stk.top() );
        		      new_top_stk.pop();
        	       }
                }
            }
        	old_top_stk.pop();
        }

        int front() { // 
        	return old_top_stk.top();
        }
};

int main() {
    MyQueue q1;
    int q, type, x;
    cin >> q;
    
    for(int i = 0; i < q; i++) {
        cin >> type;
        if(type == 1) {
            cin >> x;
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


