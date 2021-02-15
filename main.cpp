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
//int getSum(const vector<vector<int>> &sums, const int row1, const int col1, const int row2, const int col2) {
//    const int A = sums[row2][col2];
//    const int D = sums[row1-1][col1-1];
//    const int C = sums[row2][col1-1];
//    const int B = sums[row1-1][col2];
//    return A + D - C - B;
//}


int getSum(const vector<vector<int>> &sums, const int row1, const int col1, const int row2, const int col2) {
    return sums[row2][col2] + sums[row1 - 1][col1 - 1] - sums[row2][col1 - 1] - sums[row1 - 1][col2];
}

void placeShip(vector<vector<int>> &sums, const int row1, const int col1, const int row2, const int col2) {
    for (int curRow = row1; curRow <= row2; ++curRow) {
        for (int curCol = col1; curCol <= col2; ++curCol) {
            sums[curRow][curCol] = 1;
        }
    }
}

void placeHit(vector<vector<int>> &sums, const int row, const int col) {
    sums[row][col] = 0;
}

unordered_map<string, string> split(const std::string &s, const char delim) {
    stringstream ss(s);
    string item;
    unordered_map<string, string> res;
    while (std::getline(ss, item, delim)) {
        const int spacePos = find(item.begin(), item.end(), ' ') - item.begin();
        res[item.substr(0, spacePos)] = item.substr(spacePos + 1);
    }
    return res;
}

pair<int, int> stringToRowCol(const string &coord) {
    const int row = stoi(coord.substr(0, coord.size() - 1));
    const int col = coord.back() - 'A' + 1;
    return {row, col};
}

// S = '1A 1B,2C 2C', '1B')
string solution(int N, string &S, string &T) {
    vector<vector<int>> sums(N + 1, vector<int>());
    for (auto &r: sums)
        r = vector<int>(N + 1, 0);
    // place ships
    unordered_map<string, string> ships = split(S, ',');
    for (const auto &ship: ships) {
        const string &topL = ship.first;
        const pair<int, int> rowCol1 = stringToRowCol(topL);
        const string &bottomR = ship.second;
        const pair<int, int> rowCol2 = stringToRowCol(bottomR);
        placeShip(sums, rowCol1.first, rowCol1.second, rowCol2.first, rowCol2.second);
    }
    // place hits
    stringstream ss(T);
    string item;
    while (getline(ss, item, ' ')) {
        const pair<int, int> rowCol = stringToRowCol(item);
        placeHit(sums, rowCol.first, rowCol.second);
    }
    // calculate square sums
    for (int i = 1; i < sums.size(); ++i) {
        for (int j = 1; j < sums[0].size(); ++j) {
            sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + sums[i][j];
        }
    }
    //
    int hitNum = 0;
    int sinkNum = 0;
    for (int row = 1; row < sums.size(); ++row) {
        for (int col = 1; col < sums[0].size(); ++col) {
            string topL = to_string(row);
            topL.push_back(col + 'A' - 1);
            auto findShip = ships.find(topL);
            if (findShip != ships.end()) {
                const string &bottomR = findShip->second;
                const pair<int, int> rowCol2 = stringToRowCol(bottomR);
                const int realSum = getSum(sums, row, col, rowCol2.first, rowCol2.second);
                const int expectedSum = (rowCol2.first - row + 1) * (rowCol2.second - col + 1);
                const int diff = realSum - expectedSum;
                if (diff == -expectedSum)
                    ++sinkNum;
                else if (diff != 0)
                    ++hitNum;
            }
        }
    }
    string res = to_string(sinkNum);
    res.push_back(',');
    res += to_string(hitNum);
    return res;
}

int main() {
//    string S = "1B 2C,2D 4D";
//    string T = "2B 2D 3D 4D 4A";
    //
//    string S = "1A 1B,2C 2C"; //3
//    string T = "1B";
    string S = "1B 1B";
    string T = "1A";
    cout << solution(2, S, T).data();
    return 0;
}
