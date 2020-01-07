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
#include <limits>

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

// https://www.hackerrank.com/challenges/prime-xor
int primeXor(vector<int> a) {
    const int m = 1000000007;
    int size = a.size();
    const unsigned int maxXOR = 8192;
    auto table = constructTable(size, maxXOR);
    for (int xorSum = 0; xorSum < maxXOR; ++xorSum) {
        if (xorSum == a[0])
            table[0][xorSum] = 1;

    }
    table[0][0] = 1;
    //
    for (unsigned int i = 1; i < size; ++i) {
        for (unsigned int xorSum = 0; xorSum < maxXOR; ++xorSum) {
            auto xori = i ^xorSum;
            auto without = table[i - 1][xorSum];
            auto with = table[i - 1][xori];
            table[i][xorSum] = (without + with) % m;
        }
    }

    int res = 0;
    for (int i = 1; i < maxXOR; ++i) {
        if (prime(i))
            res += table[size - 1][i] % m;
    }
    return res;
}


//vector<int> lexicalOrder(int n) {
//
//}


int main() {
//    unsigned a = 3511;
//    unsigned b = 3671;
//    unsigned i =  a ^ b;
//    cout<<i<<endl;
//    cout<<primeXor({3511, 3671, 4153});
    return 0;
}
