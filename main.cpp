#include <iostream>
#include <vector>
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

using namespace std;

int minimumTotal(vector<vector<int>> &triangle) {
    auto rows = triangle.size();
    auto &prevRow = triangle[rows - 1];
    for (int row = rows - 2; row >= 0; --row) {
        auto &curRow = triangle[row];
        for (int j = 0; j < curRow.size(); ++j) {
            curRow[j] += min(prevRow[j], prevRow[j + 1]);
        }
        prevRow = curRow;
    }
    return triangle[0][0];
}


int main() {
    vector<vector<int>> triangle = {
            {2},
            {3, 4},
            {6, 5, 7},
            {4, 1, 8, 3}
    };
    cout << minimumTotal(triangle);
    return 0;
}