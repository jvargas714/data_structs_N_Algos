#include <iostream>
#include <vector>

using namespace std;

// utilizes memoization for optimized recursion
int ways( int n, vector<int>& mem ){
    if( n == 1 || n == 2 ) return n;
    if( n == 3 ) return 4;
    
    // check to see if already computed
    if( mem[n] != -1 )
        return mem[n];
    
    if( n > 3 ) {
        mem[n] = ( ways(n-1, mem) + ways(n-2, mem) + ways(n-3, mem) );
    }
    return mem[n];
}

int main(){
    int s;
    cin >> s;
    for(int a0 = 0; a0 < s; a0++){
        int n;
        cin >> n;
        vector<int> mem(50, -1);
        cout << ways(n, mem) << endl;
    }
    return 0;
}
