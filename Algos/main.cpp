#include <cmath>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include "hackerrank/markup_parser.h"
using namespace std;

int main()
{
    int N;
    int Q;
    string tmp;
    getline( cin, tmp );
    stringstream ss( tmp );
    ss >> N >> Q;

    // process
    tag_map attr_map;
    pop_attr_map( attr_map, N );
    display( attr_map );
    process_queries( attr_map, Q );
    return 0;
}
