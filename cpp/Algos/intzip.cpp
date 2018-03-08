#include "intzip.h"
#include <cstdlib>  // std::abs
#include <stack>
#include <cmath>    // std::pow

int zip_ints(int A, int B);
void display(std::vector<int> a);
void display( std::stack<int> a );
typedef unsigned int uint;
 

int main(){
    
    std::cout << "result: " << zip_ints(0, 1234) << std::endl;
    return 0;    
}




int zip_ints(int A, int B)
{
    std::stack<int> digs_a;
    std::stack<int> digs_b;
    int pwr = 0;
    int res = 0;

    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;

    if( B == 0 )
    {
        digs_b.push(0);
    }

    if( A == 0 )
    {
        digs_a.push(0);
    }

    // collect digits of number into an array in reverse order
    for( int i = 0; i < MAX_DIGITS; i++ )
    {
        if( A%10 != 0 )
        {
            digs_a.push( A%10 );
            A/=10;
        }
        else if( A > 0 )
        {
            digs_a.push( 0 );
            A/=10;
        }

        if( B%10 != 0 )
        {
            digs_b.push( B%10 );
            B/=10;
        }
        else if( B > 0 )
        {
            digs_b.push( 0 );
            B/=10;
        }
    }
    display(digs_a);
    display(digs_b);

    int a_size = digs_a.size();
    int b_size = digs_b.size();
    int diff = a_size - b_size;
    int total_digits = a_size + b_size;
    pwr = (int)std::pow(10, total_digits-1);  // so if res is 4 digits then pwr is 10^4 or 10,000

    // if vectors are diff length place extra digits first
    if( diff < 0 )  // a < b
    {
        // todo
        diff = std::abs( diff );
        while( digs_b.empty() )
        {

        }

    } 
    else if( diff > 0 ) // a > b
    {
        diff = std::abs( diff );
        int cnt = 0;
        while( !digs_a.empty() )
        {
            if( cnt >= b_size )
            {
                std::cout << "now adding remaining digit " << digs_a.top() << std::endl;
                res += digs_a.top()*pwr;
                pwr /= 10;
                digs_a.pop();
            }
            else
            {
                res += digs_a.top()*pwr;
                pwr /= 10;
                res += digs_b.top()*pwr;
                pwr /= 10;
                digs_a.pop();
                digs_b.pop();
                cnt++;
            }
        }
    }
    else    // are equal in length
    {
        while( !digs_a.empty() )
        {
            res += digs_a.top()*pwr;
            digs_a.pop();
            pwr/=10;

            res += digs_b.top()*pwr;
            digs_b.pop();
            pwr/=10;
        }
    }

    display(digs_a);
    display(digs_b);
    return res;
}

void display( std::vector<int> a )
{
    for( auto& el : a )
    {
        std::cout << el << " ";
    }
    std::cout << std::endl; 
}

void display( std::stack<int> a )
{
    while( !a.empty() )
    {
        std::cout << a.top() << " ";
        a.pop();
    }
    std::cout << std::endl; 
}