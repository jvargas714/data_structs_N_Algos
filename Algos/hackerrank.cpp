#include <vector>
#include <iostream> 
#include <unordered_map>
#include <sstream>

using namespace std;
// n elements in array 
// k rotations performed
// q number of queries to come 
// m index of element after k rotations
// Performs k rotations as specified above and returns index of desired element

// problem mains
void circular_array_rotation_main();
void is_this_a_bst_main();
void arrays_left_rotation_main();
void time_conversion_main();
void hash_tables_ransom_note_main();


// helpers
int rotate_vector( vector<int>&, int, int );
int translate_vector( vector<int>&, int, int );
bool check_sorted(vector<int>&);
vector<int> array_left_rotation( vector<int>&, int, int);
bool ransom_note( unordered_map<string, int>&, vector<string>& );
bool bin_search( string& str, const char target);
void tester();

int main()
{
    tester();
    return 0;
}








/****************************************Implementations*******************************************/

int rotate_vector( vector<int>& vect, int k, int query_index ){
    int sz = vect.size();
    int max_index = sz-1;
    int offset, translated_index;
    ( k > sz ) ? 
        offset = k % sz :
        offset = k;
    
    if( (offset + query_index) > max_index )
    {
        translated_index = (offset + query_index) - max_index - 1;
    }
    else
    {
        translated_index = (offset + query_index) - 1;
    }
    cout << "translated_index: " << translated_index << "\n" << endl; 
    return translated_index;
}

int translate_vector( vector<int>& vect, int k, int query_index )
{
    int offset, translated_index;
    int max_index = vect.size()-1;
    
    // get within one rotation 
    ( k > (max_index+1) ) ? 
        offset = k % (max_index+1) :
        offset = k;

    // mapped location of first index
    if( offset < query_index )
    {
        translated_index = query_index - offset;
    }
    else if( offset > query_index )
    {
        int diff = offset - query_index;
        translated_index = max_index - (diff-1);
    }
    else
    {
        translated_index = 0;
    }
    return translated_index;
}

void circular_array_rotation_main()
{
    int n, k, q, trans_index, m, tmp;
    vector<int> a;
    
    // get n k q
    cin >> n >> k >> q;
    
    // fill vector with elements
    for( int a_i = 0; a_i < n; a_i++ )
    {
       cin >> tmp;
        a.push_back(tmp);
    }
    
    // display queries
    for(int a0 = 0; a0 < q; a0++)
    {
        cin >> m;
        
        // perform necessary rotations
        trans_index = translate_vector( a, k, m );
        cout << a[trans_index] << endl;
    }
}

// void is_this_a_bst_main()
// {
//    vector<int> v = inorder_trav( root );
//    return check_sorted( v );

// }

bool check_sorted( vector<int>& v ){
   // now we can check if its a bin tree or not
   for( unsigned int i = 0; i < v.size(); i++ )
   {
       for( unsigned int j = i+1; j < v.size(); j++ ) 
       {
           if( v[i] > v[j] || v[i] == v[j] )
           {
               return false;
           }
       }
   }
   return true;
}

vector<int> array_left_rotation( vector<int>& a, int n, int k)
{
    if( k == n )
        return a;
    
    // k < n
    int offset = k; // offset at zero index
    vector<int> ans( n );
    
    for(int i = 0; i < n; i++){
        if( offset == n ){
            offset = 0;
        }
        // cout << offset << endl;
        ans[i] = a[offset];
        offset++;
    }
    return ans;
}

void arrays_left_rotation_main()
{
    int n;
    int k;
    cin >> n >> k;
    vector<int> a(n);
    for(int a_i = 0;a_i < n;a_i++){
        cin >> a[a_i];
    }
    vector<int> output = array_left_rotation(a, n, k);
    for(int i = 0; i < n;i++)
        cout << output[i] << " ";
    cout << endl;
}

// US time to standard time
void time_conversion_main()
{
    string time;
    stringstream output;
    cin >> time;
    string hr_  = time.substr(0, 2);
    string min_ = time.substr(3, 2);
    string sec_ = time.substr(6, 2);
    string ampm = time.substr(8, 2);
    int hr      = stoi(hr_);
    int min     = stoi(min_);
    int sec     = stoi(sec_);
    
    if( ampm == "AM" ){
        if( hr == 12 )
            hr = 0;
        (hr > 10) ? 
            output << hr_ << ":" : 
            output << "0" << hr << ":" ;
    }
    else{  // PM section
        if( hr != 12 )
            output << hr+12 << ":";
        else
            output << hr << ":";
    }
    
    // rest of time formatting
    (min > 10) ?
        output << min_ << ":" :
        output << "0" << min << ":";
    
    (sec > 10) ?
        output << sec_ :
        output << "0" << sec;
    
    cout << output.str() << endl;
}

/*
The first line contains two space-separated integers describing the respective values of  
    mag:  (the number of words in the magazine) and  
    note: (the number of words in the ransom note). 
The second line contains  space-separated strings denoting the words present in the magazine. 
The third line contains  space-separated strings denoting the words present in the ransom note.
    - words are case sensative 
    - words in magazine must match exactly to the words in the ransom note 
    - each word consist a-z and A-Z
    - print Yes if he can use the magazine otherwise print No
    - 1 <= m, n <= 30k 
*/
void hash_tables_ransom_note_main()
{
    int m;
    int n;
    cin >> m >> n;
    unordered_map<string, int> magazine;
    string tmp;
    for( int magazine_i = 0; magazine_i < m; magazine_i++ )
    {
       cin >> tmp;
       magazine[tmp]++;
    }

    vector<string> ransom(n);

    for(int ransom_i = 0;ransom_i < n;ransom_i++)
    {
       cin >> ransom[ransom_i];
    }

    if( ransom_note(magazine, ransom) )
        cout << "Yes\n";
    else
        cout << "No\n";
}

// loop through ransom and perform lookup in mag map 
bool ransom_note( unordered_map<string, int>& mag, vector<string>& ransom )
{
    for( auto& word : ransom )
    {
        if( mag[word] > 0 )
            mag[word]--;
        else
            return false;
    }
    return true;
}

// binary search, false indicates deletion and true indicates found 
// O(log n)
bool bin_search( string& str, const char target ){
    int lo = 0; 
    int hi = str.size()-1;
    int midpt;
    while( lo <= hi ){
        midpt = lo + (hi-lo) / 2; 
        if( str[midpt] == target ){
            return true;
        }
        else if( str[midpt] < target ){
            lo = midpt+1;
        }
        else{
            hi = midpt-1;
        }
    }
    // target was not found
    return false;
}

// misc scrap 
void tester()
{

}