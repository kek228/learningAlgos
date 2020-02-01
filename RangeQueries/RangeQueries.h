#pragma once

// https://leetcode.com/problems/subarray-sum-equals-k
// отличная задача, по сути обратная префиксному массиву
int subarraySum(vector<int> &nums, int k) {
    int size = nums.size();
    if (size == 0)
        return 0;
    unordered_map<int, int> sumsCount;
    int sum = 0;
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        sum += nums[i];
        int diff = sum - k;
        if (diff == 0) {
            ++res;
        }
        auto sumN = sumsCount.find(diff);
        if (sumN != sumsCount.end())
            res += sumN->second;
        // обновим
        ++sumsCount[sum];
    }
    return res;
}