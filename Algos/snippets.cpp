#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

std::vector<std::string> split( const std::string& str, char delim ) {
    std::vector<std::string> tokens;
    std::stringstream ss( str );
    std::string token;

    while( std::getline(ss, token, delim) )
        tokens.push_back(token);

    for(auto& t : tokens)
        std::cout << t << " ";
    std::cout << std::endl;
    return tokens;
}




int main()
{
	// get lines from stdin
	while ( getline(cin, line) )
    {
        cout << line << endl;
    }

	return 0;
}