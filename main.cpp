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

int substringDiff(string s1, string s2) {

    int rows = s1.size();
    int cols = s2.size();
    vector<vector<int>> editDst = constructTable(rows, cols);

    bool meet = true;
    if (s1[0] != s2[0]) {
        editDst[0][0] = 1;
        meet = false;
    }

    for (int col = 1; col < cols; ++col) {
        if (s1[0] == s2[col] && !meet) {
            editDst[0][col] = editDst[0][col - 1];
            meet = true;
        } else {
            editDst[0][col] = editDst[0][col - 1] + 1;
        }
    }
    //
    meet = true;
    if (s1[0] != s2[0]) {
        meet = false;
    }
    for (int row = 1; row < rows; ++row) {
        if (s2[0] == s1[row] && !meet) {
            editDst[row][0] = editDst[row - 1][0];
            meet = true;
        } else {
            editDst[row][0] = editDst[row - 1][0] + 1;
        }
    }
    //
    for (int row = 1; row < rows; ++row) {
        for (int col = 1; col < cols; ++col) {
            editDst[row][col] = min(editDst[row - 1][col] + 1, editDst[row][col - 1] + 1);
            int cost = 1;
            if (s1[row] == s2[col])
                cost = 0;
            editDst[row][col] = min(editDst[row][col], editDst[row - 1][col - 1] + cost);
        }
    }
    return editDst[rows - 1][cols - 1];
}

int main() {
    cout << substringDiff("execution", "intention");
    return 0;
}