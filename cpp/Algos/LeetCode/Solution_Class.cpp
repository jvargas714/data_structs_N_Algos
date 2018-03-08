#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

typedef pair<int, int> envelope;

bool operator > ( envelope& env1, envelope& env2 )
{
    return (env1.first > env2.first) && (env1.second > env2.second);
}

bool operator < ( envelope& env1, envelope& env2 )
{
    return (env1.first < env2.first) && (env1.second < env2.second);
}

class Solution
{
public:
    // find solution from left to right and right to left in size return larger result
    int maxEnvelopes( vector<envelope>& envelopes )
    {
        size_t len = envelopes.size();
        if( !len )
            return 0;

        if( len == 1 )
            return 1;

        sort( envelopes.begin(), envelopes.end());
        display(envelopes);
        envelope inner_most;
        envelope base;
        bool first_fit = false;
        int cnt_RL = 0;
        int cnt_LR = 0;
        int i = 0;
        int j = 0;

        // first find first pair
        for( i = len-1; i > 0; --i )
        {
            for( j = i-1; j > 0; --j )
                if( envelopes[i] > envelopes[j] )
                {
                    cnt_RL+=2;
                    first_fit = true;
                    inner_most = envelopes[j];
                    j--; // keep track of inner_most envelope
                    break;
                }
            if( first_fit )
                break;
        }

        if( !cnt_RL )
            return 1;

        // find rest that fit
        for( int k = j; k >= 0; --k )
        {
            if(  inner_most > envelopes[k] )
            {
                cnt_RL++;
                inner_most = envelopes[k];
            }
        }
        // end RL to left portion
        first_fit = false;

        // begin LR portion
        for( i = 0; i < len-1; ++i )
        {
            for( j = i+1; j < len-1; ++j )
                if( envelopes[j] > envelopes[i] )
                {
                    cnt_LR+=2;
                    first_fit = true;
                    base = envelopes[j];
                    i++; // keep track of base envelope
                    break;
                }
            if( first_fit )
                break;
        }

        if( !cnt_LR )
            return 1;

        // find rest that fit
        for( int k = i; k <= len-1; ++k )
        {
            if( envelopes[k+1] > base )
            {
                cnt_LR++;
                base = envelopes[k+1];
            }
        }
        if( cnt_LR >= cnt_RL )
            return cnt_LR;
        return cnt_RL;
    }

    void display( std::vector<envelope>& envs )
    {
        for(auto& el : envs )
        {
            std::cout << " (" << el.first << ", " << el.second << "), ";
        }std::cout << std::endl;
    }
};