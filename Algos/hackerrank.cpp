#include <vector>
#include <iostream> 

using namespace std;
// n elements in array 
// k rotations performed
// q number of queries to come 
// m index of element after k rotations

// Performs k rotations as specified above and returns index of desired element
int rotate_vector( vector<int>& vect, int k, int query_index ){
    int sz = vect.size();
    int max_index = sz-1;
    int offset, translated_index;
    ( k > sz ) ? 
        offset = k % sz :
        offset = k;
    
    // cout << "offset: " << offset << endl;
    // cout << "query_index: " << query_index << endl;
    // cout << "max_index: " << max_index << endl;
    // cout << "sz: " << sz << endl;
     
    // [ * * * ]  1 2 3  --> 3 1 2   --> 2 3 1 
    if( (offset + query_index) > max_index ){ // q=1
        translated_index = (offset + query_index) - max_index - 1;  // (2 + 1) - 2 - 1
    }
    else{
        translated_index = (offset + query_index) - 1;
    }
    cout << "translated_index: " << translated_index << "\n" << endl; 
    return translated_index;
}

int translate_vector( vector<int>& vect, int k, int query_index ){
    int offset, translated_index;
    int max_index = vect.size()-1;
    
    // get within one rotation 
    ( k > (max_index+1) ) ? 
        offset = k % (max_index+1) :
        offset = k;

    // mapped location of first index
    if( offset < query_index ){
        translated_index = query_index - offset;
    }
    else if( offset > query_index ){
        int diff = offset - query_index;
        translated_index = max_index - (diff-1);
    }
    else{
        translated_index = 0;
    }
    return translated_index;
}

int main(){
    int n, k, q, trans_index, m, tmp;
    vector<int> a;
    
    // get n k q
    cin >> n >> k >> q;
    
    // fill vector with elements
    for( int a_i = 0; a_i < n; a_i++ ){
       cin >> tmp;
        a.push_back(tmp);
    }
    
    // display queries
    for(int a0 = 0; a0 < q; a0++){
        cin >> m;
        
        // perform necessary rotations
        trans_index = translate_vector( a, k, m );
        cout << a[trans_index] << endl;
    }
    return 0;
}


/*
 1 2 3 

3 1 2
0:1 
1:2 
2:0

2 3 1 
0 : 2 
1 : 0
2 : 1 

every index counts up till hits last index and resets 
so if asking for query index of say 1
so
- puts us within on rotation k % sz   

say sz = 10 and k = 14 
if k > sz --> offset = 14 % 10 --> 4 
orig + offset = num --> say 13 

if num > max_index:
    then trans is 13 % 10 - 1   ---> 
else 
    trans is num - 1


take zero of orig get offset from that 
get offset like normal but instead 
zeroInd + offset = num --> say 13 

if num > max_index:
    then trans is 13 % 10 - 1 
else 
    trans is num - 1

then to query index value say 8 
0 : 6
1 : 7
2 : 8

trans = 8 - 6  = 2 

if offset < query index ---> say q index is 8
if offset > query index --> say q index is 3
    then we start at last index then subtract from there so 
    9 or max index 
    diff = offset - q index  = 6 - 3 = 3 
    so 
    9 : 5
    8 : 4
    7 : 3 
    or  
    max ind - (diff -1)

            
*/








