#include <stack>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

map<char, char> brak_map =
{       { '{' ,'}' },
        { '[', ']' },
        { '(', ')' }
                               };

bool is_balanced(string expression) {
    // not balanced with odd # of chars 
    if( expression.size() % 2 != 0 )
        return false;
    
    stack<char> stk;
    for( auto ch : expression ){
        if( ch == '{' || ch == '[' || ch == '(' ){
            stk.push( ch );
        }
        else{ // right side bracket 
        	if( ch != brak_map[ stk.top() ] ){
        		return false;
        	}
            stk.pop();
        }
    }
    return true;
}

int main() {
    int t;

    ifstream strm("brackets.inputs");
    strm >> t;
    for(int a0 = 0; a0 < t; a0++){
        string expression;
        strm >> expression;
        bool answer = is_balanced( expression );
        if(answer)
            cout << "YES\n";
        else 
            cout << "NO\n";
    }
    return 0;
}
