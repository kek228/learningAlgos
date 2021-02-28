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
#include <set>
#include <optional>
#include <stdint.h>
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <functional>
#include <thread>

using namespace std;

class Solution {
public:
    void _fillMatrix(vector<vector<int>> &res, vector<int> &rowSum, vector<int> &colSum, int row, int col) {
        if (row >= rowSum.size() || col >= colSum.size())
            return;
        if (rowSum[row] <= colSum[col]) {
            colSum[col] -= rowSum[row];
            res[row][col] = rowSum[row];
            for (int _col = col + 1; _col < colSum.size(); ++_col)
                res[row][_col] = 0;
            _fillMatrix(res, rowSum, colSum, row + 1, col);
        } else {
            rowSum[row] -= colSum[col];
            res[row][col] = colSum[col];
            for (int _row = row + 1; _row < rowSum.size(); ++_row)
                res[_row][col] = 0;
            _fillMatrix(res, rowSum, colSum, row, col + 1);
        }
    }

    vector<vector<int>> restoreMatrix(vector<int> &rowSum, vector<int> &colSum) {
        auto res = vector<vector<int>>(rowSum.size(), vector<int>());
        for (auto &row: res)
            row = vector<int>(colSum.size(), 0);
        _fillMatrix(res, rowSum, colSum, 0, 0);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> rowSum = {4, 12, 10, 1, 0};
    vector<int> colSum = {1, 0, 3, 16, 7};
    s.restoreMatrix(rowSum, colSum);
    return 0;
}
