#pragma once
// Задачки на массив, которые не вписываются в окно/рэнджи/ итд

// https://leetcode.com/problems/first-missing-positive
int firstMissingPositive(vector<int> &nums) {
    int size = nums.size();
    int minVal = numeric_limits<int>::max();
    for (const auto n: nums) {
        if (n > 0 && n < minVal)
            minVal = n;
    }
    if (minVal != 1)
        return 1;

    for (int i = 0; i < size; ++i) {
        int64_t realId = (int64_t) nums[i] - 1;
        while (realId >= 0 && realId < size) {
            swap(nums[realId], nums[i]);
            realId = nums[i] - 1;
            if (nums[i] == i + 1)
                break;
            if (realId >= 0 && realId < size && nums[i] == nums[realId])
                break;

        }
    }
    for (int i = 0; i < size; ++i) {
        if (nums[i] != i + 1)
            return i + 1;
    }
    return size + 1;
}