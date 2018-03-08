#ifndef ALGOS_MARKUP_PARSER_H_H
#define ALGOS_MARKUP_PARSER_H_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>       // std::isspace()
#define  QUERY_DELIM '~'
#define  QUERY_FAIL "Not Found!"

typedef std::pair<std::string, std::string> val_pair;
typedef std::vector<val_pair> val_pairs;
typedef std::string tag;
typedef std::map<tag, val_pairs> tag_map;

void collect_tag_values( std::vector<std::string>&, const std::string&, tag_map& );
std::vector<std::string> split( const std::string&, char );
void pop_attr_map( tag_map&, const int& );
void process_queries( tag_map& attr_map, const int& q );


// helpers
void display( const std::vector<std::string>& );
void display( const val_pairs& );
void display( const tag_map& );
std::string elim_whitespace( std::string& );
tag build_tag( const std::vector<tag>& );
val_pairs::const_iterator get_attr( const val_pairs&, const std::string& );

#endif //ALGOS_MARKUP_PARSER_H_H
