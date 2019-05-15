#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

/*
 * write a program that takes an array denoting the daily stock price, and returns
 * the maximum profit that could be made by buying and selling a single stock
 *
 * Average running time:    5 us
 * Median running time:     2 us
 * runtime complexity: O(n)
 * space complexity: O(1)
 */
double BuyAndSellStockOnce(const vector<double>& prices) {
    if (prices.size() < 2) return 0;
    double profit = 0.0;
    size_t buy = 0, sell = 1, len = prices.size();
    while (buy < len && sell < len) {
        if (prices[sell] > prices[buy])             // we have a profit, take the max profit
            profit = std::max(profit, prices[sell] - prices[buy]);
        else if (prices[sell] < prices[buy])        // finds min price up to this point, set buy pointer
            buy = sell;
        sell++;
    }
    return profit;
}


/*
    Average running time:    6 us
    Median running time:     2 us
*/
double BuyAndSellStockOnce_fromBook(const vector<double>& prices) {
    double min_price_so_far = std::numeric_limits<double>::max(), max_profit = 0;
    for (double price : prices) {
        double max_profit_sell_today = price - min_price_so_far;
        max_profit = std::max(max_profit, max_profit_sell_today);
        min_price_so_far =std::min(min_price_so_far, price);
    }
    return max_profit;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
