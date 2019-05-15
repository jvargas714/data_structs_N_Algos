#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
    double bestProfit = 0.0, secondBest = 0.0;
    size_t buy = 0, sell = 1, len = prices.size();
    while (buy < len && sell < len) {
        if (prices[sell] > prices[buy]) {
            double tmp = prices[sell] - prices[buy];
            if (tmp > bestProfit) {
                secondBest = bestProfit;
                bestProfit = tmp;
            }
        } else if (prices[sell] < prices[buy]) {
            buy = sell;
        }
        sell++;
    }
      return bestProfit + secondBest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
