#pragma once

// проверка на простоту
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
vector<bool> SieveEratosthenes(const int n) {
    vector<bool> nums(n + 1, true);
    for (int i = 2; i * i <= n; ++i) {
        if (nums[i]) {
            int x = i * 2;
            while (x <= n) {
                nums[x] = false;
                x += i;
            }
        }
    }
    return nums;
}

void showPrimes(const int n) {
    auto res = SieveEratosthenes(n);
    for (int i = 0; i < res.size(); ++i) {
        if (res[i])
            cout << i << ' ';
    }
}


int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}


// https://leetcode.com/problems/rotate-function
// найди максимальный поворот вправо F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1].
// F функция от массива. Прикольный пример на подумать.
int maxRotateFunction(vector<int> &A) {
    int size = A.size();
    if (size == 0)
        return 0;
    int64_t simpleSum = 0;
    int64_t sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += A[i] * i;
        simpleSum += A[i];
    }
    int res = sum;
    for (int rot = 1; rot < A.size(); ++rot) {
        int64_t newSum = sum + simpleSum -
                         ((int64_t) A[size - rot]) * size;
        if (newSum > res)
            res = newSum;
        sum = newSum;
    }
    return res;
}

// быстрое возведение в степень
class Solution {
    double binpow(double a, int n) {
        if (n == 0)
            return 1;
        if (n % 2 == 1)
            return binpow(a, n - 1) * a;
        else {
            double b = binpow(a, n / 2);
            return b * b;
        }
    }

    double minusBinpow(double a, int n) {
        if (n == 0)
            return 1;
        if (n % 2 == -1)
            return minusBinpow(a, n + 1) * (1 / a);
        else {
            double b = minusBinpow(a, n / 2);
            return b * b;
        }
    }

public:
    double myPow(double x, int n) {
        if (n == 0)
            return 1;
        if (x == 1)
            return 1;
        else if (n < 0) {
            double res = minusBinpow(x, n);
            return res;
        } else {
            double res = binpow(x, n);
            return res;
        }
    }
};