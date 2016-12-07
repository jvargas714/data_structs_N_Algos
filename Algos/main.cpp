#include <map>
#include <iostream>

using namespace std;


int main()
{
    int tmp;
    size_t len;
    string word;
    map<char, unsigned int> char_map;
    const int ascii_a   = 97;
    unsigned int h      = 0;
    int tallest_char    = 0;

    // map out characters
    for( int i = 0; i < 26; i++ )
    {
        cin >> h;
        char_map[ (char)(ascii_a + i) ] = h;
    }
    cin >> word;
    len = word.size();

    // get tallest char
    for( char& ch : word )
    {
        tmp = char_map[ ch ];
        if( tmp > tallest_char )
        {
            tallest_char = tmp;
        }
    }
    cout << tallest_char * len;
    return 0;
}
