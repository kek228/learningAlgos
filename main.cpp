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

// 0 1 2 3 5 7 11 13 17 19 23 29 31 37 41 43

using namespace std;

vector<vector<int>> constructTable(int rows, int cols) {
    vector<vector<int>> table(rows);
    for (auto &row: table)
        row = vector<int>(cols, 0);
    return table;
}

bool prime(int n) {
    if (n == 0)
        return false;
    if (n == 1)
        return true;
    for (int x = 2; x * x <= n; ++x) {
        if (n % x == 0) return false;
    }
    return true;
}

string vtostr(vector<int> &permut) {
    string res;
    for (int i = 0; i < permut.size(); ++i) {
        char c = '0' + permut[i];
        res.push_back(c);
    }
    return res;
}


class PrimeDigitSums {
public:
    PrimeDigitSums() {
        vector<int> permut;
        genAllPermutsWithDoubles(permut, 0, 10, 5);
    }

    int primeDigitSums(int n) {
        int res = 0;
        // возможные комбинации с прошлой пятерки
        unordered_set<string> lastStepPermuts;
        for (const auto &permut: valid5Nums) {
            if (permut[0] != '0')
                lastStepPermuts.insert(permut);
        }
        //
        int step = 6;
        while (step <= n) {
            lastStepPermuts = genNewPermuts(lastStepPermuts);
            res += lastStepPermuts.size();
            ++step;
        }
        return res;
    }

private:
    unordered_set<string> genNewPermuts(unordered_set<string> &lastStepPermuts) {
        unordered_set<string> newPermuts;
        for (const auto &permut: lastStepPermuts) {
            for (int i = 0; i < 10; ++i) {
                auto newPermut = permut.substr(1);
                newPermut.push_back('0' + i);
                if (valid5Nums.find(newPermut) != valid5Nums.end()) {
                    // cout<<permut[0]<<newPermut.data()<<endl;
                    newPermuts.insert(newPermut);
                }
            }
        }
        return newPermuts;
    }


    bool checkPrime(vector<int> &permut) {
        int sum = 0;
        for (int i = 0; i < 3; ++i)
            sum += permut[i];
        if (!prime(sum))
            return false;
        //
        sum -= permut[0];
        sum += permut[3];
        if (!prime(sum))
            return false;
        //
        sum -= permut[1];
        sum += permut[4];
        if (!prime(sum))
            return false;
        //
        sum = 0;
        for (int i = 0; i < 4; ++i)
            sum += permut[i];
        if (!prime(sum))
            return false;
        sum -= permut[0];
        sum += permut[4];
        if (!prime(sum))
            return false;
        //
        sum += permut[0];
        return prime(sum);
    }

    void genAllPermutsWithDoubles(vector<int> &permut, int from, int to, int permutsize) {
        if (permut.size() == permutsize) {
            if (checkPrime(permut)) {
                valid5Nums.insert(vtostr(permut));
            }
            return;
        }
        for (int j = from; j < to; ++j) {
            permut.push_back(j);
            genAllPermutsWithDoubles(permut, from, to, permutsize);
            permut.pop_back();
        }
    }

    unordered_set<string> valid5Nums;
};

int primeDigitSums(int n) {
    PrimeDigitSums sumsHandler;
    return sumsHandler.primeDigitSums(n);
}


int main() {
    cout << primeDigitSums(6);
    return 0;
}