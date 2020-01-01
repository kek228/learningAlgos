#include <iostream>
#include <stdint.h>
#include <limits>
using namespace std;

int64_t fib(int64_t f, int64_t s, int64_t n) {
    int64_t c = 3;
    int64_t res = f + s;
    while (c <= n) {
        s = f;
        f = res;
        res = f + s;
        ++c;
    }
    return res;
}

pair<bool, int64_t> searchIPlus1(int64_t i, int64_t fi, int64_t j, int64_t fj, int64_t top) {
    int64_t dst = j - i;
    if (dst == 1)
        return {true, fj};
    int64_t bottom = numeric_limits<int>::min();
    if (top > 0)
        bottom = 1;
    while (bottom < top) {
        int64_t m = (bottom + top) / 2;
        int64_t f = fib(m, fi, dst);
        if (f > fj)
            top = m;
        else
            bottom = m + 1;
    }
    int64_t f = fib(bottom, fi, dst);
    if (f == fj)
        return {true, bottom};
    else
        return {false, 0};
}

int nthFib(int64_t i, int64_t fi, int64_t j, int64_t fj, int64_t n) {
    int64_t dst = j - i;
    int64_t fiPlus1 = 0;
    int64_t zeroCheck = fib(fiPlus1, fi, dst);
    if (zeroCheck == n) {
        fiPlus1 = zeroCheck;
    } else {
        auto res = searchIPlus1(i, fi, j, fj, -1);
        if (res.first) {
            fiPlus1 = res.second;
        } else {
            res = searchIPlus1(i, fi, j, fj, numeric_limits<int>::max());
            fiPlus1 = res.second;
        }
    }

    return fib(fiPlus1, fi, n - i);
}

int main() {
    int64_t i, fi, j, fj, n;
    cin >> i >> fi >> j >> fj >> n;
    if (i > j) {
        swap(i, j);
        swap(fi, fj);
    }
    cout << nthFib(i, fi, j, fj, n);
    return 0;
}
// 3 5 -1 4 5
// 0 1 1 1 5