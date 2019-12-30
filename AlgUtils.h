#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>
#pragma once
using namespace std;
namespace alg_utils {
    // парсинг строки в вектор чисел
    vector<int> split(const string &str, char delim = ' ') {
        vector<int> res;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delim)) {
            res.push_back(stoi(token)
            _;
        }
    }

    // из файлика
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

    // все цифры в числе
    vector<int> getUnorderedDigits(string &s) {
        bool digits[10] = {};
        for (auto c: s) {
            digits[c - '0'] = true;
        }
        vector<int> res;
        for (int i = 1; i < 10; ++i) {
            if (digits[i])
                res.push_back(i);
        }
        return res;
    }

}

vector<vector<int>> constructTable(int rows, int cols) {
    vector<vector<int>> table(rows);
    for (auto &row: table)
        row = vector<int>(cols, 0);
    return table;
}
