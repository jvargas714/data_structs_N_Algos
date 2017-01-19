#include "short_algos.h"

/* Problem: #168 */
std::string excel_column_title( int n )
{
    std::string res;
    while ( true )
    {
        int mod_res = n % 26;

        if (n <= 26)
        {
            res += (char)(n + 64);
            break;
        }
        else if( mod_res == 0 )
        {
            res += 'Z';
            n = (n / 26) - 1;
            continue;
        }
        else
        {
            res += (char)(mod_res + 64);
        }
        n /= 26;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

/* Problem: #59 */
std::vector<int> count_bits( int num )
{
    std::vector<int> result( 1,0 );
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


bool operator > ( envelope& env1, envelope& env2 ) {
    return (env1.first > env2.first) && (env1.second > env2.second);
}

int maxEnvelopes(std::vector<envelope>& envelopes) {
    sort( envelopes.begin(), envelopes.end());
    // display( envelopes );
    bool first_fit = false;
    int cnt = 0;

    for( int i = 0; i < envelopes.size()-1; ++i ) {
        if( !first_fit && envelopes[i+1] > envelopes[i] ) {
            cnt+=2;
            first_fit = true;
        }

        if( first_fit && envelopes[i+1] > envelopes[i] ) {
            cnt++;
        }
    }
    return cnt;
}

void display( std::vector<envelope>& envs ) {
    for(auto& el : envs ) {
        std::cout << " (" << el.first << ", " << el.second << "), ";
    }std::cout << std::endl;
}
