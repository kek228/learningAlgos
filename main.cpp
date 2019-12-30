#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iterator>
#include <limits>
#include <fstream>
#include <set>
#include <optional>

using namespace std;

vector<vector<int>> constructTable(int rows, int cols) {
    vector<vector<int>> table(rows);
    for (auto &row: table)
        row = vector<int>(cols, 0);
    return table;
}


int maxProfit(vector<int> &prices) {
#define BUY 0
#define SELL 1
#define BUY_WAIT 2
#define SELL_WAIT 3
#define WAIT 4

    if (prices.size() < 2)
        return 0;
    int cols = static_cast<int>(prices.size());
    int rows = 5;
    auto table = constructTable(rows, cols);
    for (int row = 0; row < 5; ++row) {
        table[row][0] = numeric_limits<int>::min();
    }
    table[BUY][0] = -prices[0];
    table[WAIT][0] = 0;
    for (int col = 1; col < cols; ++col) {
        table[BUY][col] = max(table[SELL_WAIT][col - 1], table[WAIT][col - 1]) - prices[col];
        //
        table[SELL][col] = max(table[BUY][col - 1], table[BUY_WAIT][col - 1]) + prices[col];
        //
        table[BUY_WAIT][col] = max(table[BUY][col - 1], table[BUY_WAIT][col - 1]);
        //
        table[SELL_WAIT][col] = max(table[SELL][col - 1], table[SELL_WAIT][col - 1]);
        //
        table[WAIT][col] = 0;
    }
    int res = table[0][cols - 1];
    for (int row = 0; row < 5; ++row) {
        if (table[row][cols - 1] > res)
            res = table[row][cols - 1];
    }
    return res;
}

int main() {
    // vector<int> prices = {1, 2, 3, 0, 2};
    vector<int> prices = {1, 2, 4};
    cout << maxProfit(prices);
    return 0;
}