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

int main() {
    auto res = SieveEratosthenes(10);
    int answer = 0;
    for (int i = 1; i < res.size() - 1; ++i) {
        if (res[i])
            cout << i << ' ';
    }
    return 0;
}