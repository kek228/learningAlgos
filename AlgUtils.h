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

    // Проверка валидности скобочной последовательности
    bool ArePair(char opening, char closing) {
        if (opening == '(' && closing == ')') return true;
        else if (opening == '{' && closing == '}') return true;
        else if (opening == '[' && closing == ']') return true;
        return false;
    }

    bool AreParanthesesBalanced(vector<char> &exp) {
        stack<char> S;
        for (int i = 0; i < exp.size(); i++) {
            if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
                S.push(exp[i]);
            else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
                if (S.empty() || !ArePair(S.top(), exp[i]))
                    return false;
                else
                    S.pop();
            }
        }
        return S.empty() ? true : false;
    }


    //  ДИНАМИКА
    int knapsackProblem(int W , vector<int> &prices, vector<int> &weights){
        vector<vector<int>> results;
        int n = prices.size();
        results.resize(n + 1);
        for(auto &r:results)
            r.resize(W + 1);
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= W; ++j){
                results[i][j] = results[i-1][j];
                auto &check = results[i][j];
                if(weights[i-1] <= j )
                    results[i][j] = max(results[i][j], results[i-1][j-weights[i-1]] + prices[i-1]);
            }
        }
        return results[n][W];
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
    // решето эратосфена
    vector<uint64_t> eratSieve(const uint64_t &n) {
        vector<uint64_t> res(n, 0);
        for (uint64_t i = 2; i < n; i++) {
            for (uint64_t j = i * i; j < n; j += i) {
                res[j - 1] = 1;
            }
        }
        return res;
    }
}
