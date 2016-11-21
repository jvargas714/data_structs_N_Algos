#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/*
    1. sort
    2. xor every two
*/

int lonely_integer(vector < int > a) {
    if( a.size() == 1 ) return a[0];
    
    sort(a.begin(), a.end());
    for(auto& el : a)
    	cout << el << " ";
    cout << endl; 
    
    int i=0;
    int j=1;
    for(int n = 0; n < a.size()/2; n++){
        if( (a[i]^a[j]) != 0 ){
                return a[i];
        }
        i+=2; j+=2;
        cout << a[i] << " and " << a[j] << " check good " << endl;
    }
    return a[a.size()-1];
}

int main(){
    int n, tmp;
    cin >> n;
    vector<int> a;
    for(int a_i = 0;a_i < n;a_i++){
       cin >> tmp;
       a.push_back(tmp);
    }
    cout << lonely_integer(a) << endl;
    return 0;
}
