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

vector<int> split(char delim = ' ') {
    std::ifstream t("/Users/nikita/CLionProjects/ALGOS/test.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    vector<int> res;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        res.push_back(stoi(token));
    }
    return res;
}

int cost(vector<int> b) {
    int size = b.size();
    auto table = constructTable(2, size);
    for (int i = 1; i < size; ++i) {
        // решение заканчивается на 1
        table[0][i] = max(table[0][i - 1] + 0, table[1][i - 1] + abs(b[i - 1] - 1));
        // решение заканчивается на макс возможное
        table[1][i] = max(table[0][i - 1] + abs(b[i] - 1), table[1][i - 1] + abs(b[i] - b[i - 1]));
    }
    return max(table[0][size - 1], table[1][size - 1]);
}


int main() {
    // cout << cost({100, 10, 5});
    // cout << cost({1, 2, 3});
    // 10 62 30 19 71 49 13 40 16 44 28 -> 426
    auto b = split();
    cout << cost({100, 2, 100, 2, 100});
    return 0;
}