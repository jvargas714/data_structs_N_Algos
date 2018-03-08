#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

typedef std::pair<int, int> envelope;
#ifndef ALGOS_SHORT_ALGOS_H
#define ALGOS_SHORT_ALGOS_H

// Problem #168
std::string excel_column_title( int n );

// Problem #59
std::vector<int> count_bits( int num );

// Problem #122
int best_time_to_buy_and_sell_stock( std::vector<int>& prices );


bool operator > ( envelope& env1, envelope& env2 );

#endif //ALGOS_SHORT_ALGOS_H
