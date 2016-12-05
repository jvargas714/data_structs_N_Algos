//
// Created by JAY VARGAS on 11/27/16.
//

#include "Solution_Class.h"
using namespace std;

// #168
string Solution::excel_column_title(int n)
{
    string result = "%";
    int cycles = n/26;

    if( n <= 26 )
    {
        result = (char)(n+64);
        return result;
    }
    else if( n > 26 )
    {
        bool new_cycle = true;

        // build result  28 --> AB and 27 --> AA
        for( int i = 0; i < n/26; ++i )
        {
            char ch = (char)(n%26 + 64);
            if( new_cycle )
            {
                result[0] = ch;
                new_cycle = false;
            }
            cout << "n: "  << n  << endl;
            cout << "ch: " << ch << endl;
            n %= 26;

            if( ch == 'Z' )
                new_cycle = true;
            else
                result[result.size()-1] = ch;


        }
    }
    return result;
}


// O(num*sizeof(int)*8) solution #59
vector<int> Solution::count_bits( int num )
{
    vector<int> result( 1,0 );
    int mask;
    int cnt = 0;

    for( uint i = 1; i <= num; i++ )
    {
        cnt = 0;
        mask = 0x1;
        for( uint j = 0; j < 8*sizeof( int ); j++ )
        {
            if( mask & i )
                cnt++;
            mask <<= 1;
        }
        result.push_back( cnt );
    }
    return result;
}

// O(n) solution #59
vector<int> Solution::countBits( int num )
{
    vector<int> result( 1, 0 );
    int cnt = 0;
    int mask = 0x1;

    for( int i = 0; i <= num; i++ )
    {
        ;
    }
    return result;
}