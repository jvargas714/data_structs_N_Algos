#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "snippets.h"
using namespace std;

// split a string by delimiter
std::vector<std::string> split( const std::string& str, char delim ) {
    std::vector<std::string> tokens;
    std::istringstream iss( str );
    std::string token;

    while( std::getline(iss, token, delim) )
        tokens.push_back(token);

    for(auto& t : tokens)
        std::cout << t << " ";
    std::cout << std::endl;
    return tokens;
}

// split string by space delimiter only
std::vector<std::string> split_by_space( const std::string& str ) {
    std::istringstream iss(str);
    std::vector<std::string> results( (std::istream_iterator<std::string>(iss)), 
                                                    std::istream_iterator<std::string>() );
    return results;
}


int main()
{
    std::string line;
    std::vector<std::string> splitStrBySpace;
    std::vector<std::string> splitByDelim;
	while ( getline(cin, line) ) {
        splitStrBySpace = split_by_space(line);
        splitByDelim = split(line, ' ');
        std::cout << "Split String by space: " << std::endl;
        std::for_each(splitStrBySpace.begin(), splitStrBySpace.end(), [](std::string& str){
                std::cout << str << "\n";
            }
        );
        std::cout << std::endl;
        // std::cout << "\n split by delim: \n" <<  splitByDelim << std::endl;
    }

	return 0;
}