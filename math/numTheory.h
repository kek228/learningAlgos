#pragma once

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
