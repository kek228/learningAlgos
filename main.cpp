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
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <functional>

using namespace std;

int leastSignifisantBit(int n) {
    return (n & (~n + 1));
}

bool
checkSubset(const vector<int> &rods, const vector<vector<bool>> &sumsSubsets, const int sum, const uint32_t subset) {
    uint32_t bits = subset;
    while (bits != 0) {
        uint32_t bit = leastSignifisantBit(bits);
        bits = bits & (~bit);
        uint32_t element = rods[log2(bit)];
        const int checkSum = sum - element;
        uint32_t subsetWithoutEl = subset ^bit;
        if (checkSum >= 0 && sumsSubsets[checkSum][subsetWithoutEl])
            return true;
    }
    return false;
}

int inverseBits(const uint32_t subset, const uint32_t maxSubset) {
    uint32_t res = ~subset;
    return res & (maxSubset - 1);
}

bool _canPartitionKSubsets(vector<int> &nums, vector<int> &cache, int s, int k, const int baseSum, uint32_t subset) {
    string cacheVal = to_string(s) + to_string(k);
    if (cache[subset] != -1)
        return cache[subset];
    if (s == 0) {
        --k;
        s = baseSum;
    }
    if (k == 0)
        return true;
    if (s < 0)
        return false;

    uint32_t bits = subset;
    while (bits != 0) {
        uint32_t bit = leastSignifisantBit(bits);
        bits = bits & (~bit);
        const uint32_t newSubset = subset ^bit;
        uint32_t element = nums[log2(bit)];
        const int newSum = s - element;
        bool res = _canPartitionKSubsets(nums, cache, newSum, k, baseSum, newSubset);
        if (res) {
            cache[subset] = true;
            return true;
        }
    }
    cache[subset] = false;
    return false;


}

bool canPartitionKSubsets(vector<int> &nums, int k) {
    int subsetsN = 1 << nums.size();
    vector<int> cache(subsetsN, -1);
    int sum = 0;
    for (auto n: nums)
        sum += n;
    sum /= k;
    return _canPartitionKSubsets(nums, cache, sum, k, sum, subsetsN - 1);
}


int main() {
    // vector<int> rods = {1,2,2,3,3};
    // vector<int> rods = {2, 4, 8, 16};
    // vector<int> rods = {1,2,3,4,5,6};
    // vector<int> rods = {1,2};
    // vector<int> rods = {100, 100};

    vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
    //nums = { 5, 5, 4, 1 };
    //nums = { 5, 5, 4, 1 };
    cout << canPartitionKSubsets(nums, 3);
    return 0;
}