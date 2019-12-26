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
#include <set>

using namespace std;

vector<vector<int>> constructTable(int rows, int cols) {
    vector<vector<int>> table(rows);
    for (auto &row: table)
        row = vector<int>(cols, 0);
    return table;
}

int processDiag(int row, int col, int l, int k, vector<vector<int>> &table) {
    int zeroCounter = 0;
    int b = 0;
    int e = 1;
    int res = 0;
    // e на 1 вперед
    while (e < l) {
        if (table[row + e - 1][col + e - 1] == 0)
            ++zeroCounter;
        int segmentLength = e - b;
        if (segmentLength > res && zeroCounter <= k)
            res = segmentLength;
        //
        if (zeroCounter > k) {
            while (b < e && zeroCounter > k) {
                ++b;
                if (table[row + b - 1][col + b - 1] == 0)
                    --zeroCounter;
            }
        }
        ++e;
    }
    if (table[row + e - 1][col + e - 1] == 0)
        ++zeroCounter;
    int segmentLength = e - b;
    if (segmentLength > res && zeroCounter <= k)
        res = segmentLength;
    return res;
}

int substringDiff(int k, string s1, string s2) {
    int rows = s1.size();
    int cols = s2.size();
    auto table = constructTable(rows, cols);
    //
    for (int col = 0; col < cols; ++col) {
        if (s1[0] == s2[col]) {
            table[0][col] = 1;
        }
    }
    //
    for (int row = 1; row < rows; ++row) {
        if (s2[0] == s1[row]) {
            table[row][0] = 1;
        }
    }
    //
    for (int row = 1; row < rows; ++row) {
        for (int col = 1; col < cols; ++col) {
            if (s2[col] != s1[row])
                table[row][col] = 0;
            else {
                table[row][col] = table[row - 1][col - 1] + 1;
            }
        }
    }
    //
    int res = 0;
    for (int row = rows - 1; row >= 0; --row) {
        int curRes = processDiag(row, 0, rows - row, k, table);
        if (curRes > res)
            res = curRes;
    }
    for (int col = 1; col < cols; ++col) {
        int curRes = processDiag(0, col, cols - col, k, table);
        if (curRes > res)
            res = curRes;
    }
    return res;
}

int main() {
    cout << substringDiff(2, "torino", "tabriz");
    //cout << substringDiff(0, "abacba", "abcaba");
    //cout << substringDiff(3, "helloworld", "yellomarin");
    return 0;
}