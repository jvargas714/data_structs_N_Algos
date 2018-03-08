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

bool is_balanced(string expr) {
    // not balanced with odd # of chars 
    if( expr.size() % 2 != 0 )
        return false;

    if( expr[0] == '}' || expr[0] == ']' || expr[0] == ')' )
        return false;
    
    int last = expr.size()-1;
    if( expr[last] == '(' || expr[last] == '{' || expr[last] == '[' )
        return false;

    stack<char> stk;
    for( auto ch : expr ){
        if( ch == '{' || ch == '[' || ch == '(' ){
            stk.push( ch );
        }
        else{ // right side bracket 
        	if( !stk.size() || ch != brak_map[ stk.top() ] ){
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
        string expr;
        strm >> expr;
        bool answer = is_balanced( expr );
        if(answer)
            cout << "YES\n";
        else 
            cout << "NO\n";
    }
    return 0;
}
