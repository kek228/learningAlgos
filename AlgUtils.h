#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>
#pragma once
using namespace std;
namespace alg_utils{
    // парсинг строки в вектор чисел
    vector<int> split(const string& str, char delim = ' '){
        vector<int> res;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delim)) {
            res.push_back(token);
        }
    }
    // все цифры в числе
    vector<int> getUnorderedDigits(string &s){
        bool digits[10] = {};
        for(auto c: s){
            digits[c - '0'] = true;
        }
        vector<int> res;
        for(int i = 1; i < 10; ++i){
            if(digits[i])
                res.push_back(i);
        }
        return res;
    }

    // все делители числа n
    vector<int> factors(int n) {
        vector<int> f;
        for (int x = 2; x * x <= n; x++) {
            while (n % x == 0) {
                f.push_back(x);
                n /= x;
            }
        }
        if (n > 1) f.push_back(n);
        return f;
    }

}
