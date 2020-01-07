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