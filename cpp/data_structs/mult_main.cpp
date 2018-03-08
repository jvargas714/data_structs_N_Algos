#include <iostream>
#include "queue.h"

 /*
  *
  * Display Multiplication table
  *
  */
template<typename T>
void display( queue<T>& );
uint64_t line_len;

int main( int argc, char** argv )
{
    std::cout << "Enter multiplication table size: " << std::endl;
    std::cin >> line_len;
    uint64_t mult_size = line_len * line_len;
    std::cout << "\n\n\n" << std::endl;

	uint64_t tmp = 0;
    unsigned long multiplier = 1;
    queue<uint64_t>* que = new queue<uint64_t>;
    for( uint64_t i = 1; i <= mult_size; i++ )
    {
        tmp += multiplier;
        que->enqueue( tmp );
        if( i % line_len == 0 )
        {
            multiplier++;
            tmp = 0;
        }
    }
    display( *que );
    delete que;
	return 0; 
}

template<typename T>
void display( queue<T>& Q )
{
    size_t tmp_sz = Q.size();
    std::string delim;
    std::cout << "Size of queue: " << Q.size() << std::endl;
    for( size_t i = 1; i <= tmp_sz; ++i )
    {
        T t = Q.dequeue();

        if ( t < 10 ) delim = "       ";
        else if( t >= 10 && t < 100 ) delim = "      ";
        else if ( t >= 100 && t < 1000 ) delim = "     ";
        else if ( t >= 1000 && t < 10000 ) delim = "    ";
        else if (t >= 10000 && t < 100000 ) delim = "   ";
        else if (t >= 100000 && t < 1000000) delim = "  ";
        else if ( t >= 1000000 ) delim = " ";

        std::cout << t << delim;

        if( i % line_len == 0 )
            std::cout << std::endl;
    }
}
