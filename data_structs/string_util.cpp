#include "string_util.h"


std::string elim_whitespace( std::string& str )
{
    // find char index of first none white space
    uint32_t ind = 0;
    for( auto& ch : str )
    {
        if( std::isspace( ch ) )
            ind++;
        else
            break;
    }
    return str.substr( ind, str.size() );
}