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

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii
// в задаче используется отличный прием который помогает найти
// forwardRes содержит решения следующей задачи: от 0 до i найди МАКСИМАЛЬНУЮ
// разницу между prices[j] и prices[i] где j > i
// backwardRes аналогично только от i до size-1
int maxProfit(vector<int> &prices) {
    int size = prices.size();
    if (size == 0)
        return 0;
    vector<int> forwardRes(size, 0);
    int minEl = prices[0];
    for (int i = 1; i < size; ++i) {
        if (prices[i] > minEl) {
            int val = prices[i] - minEl;
            if (val > forwardRes[i - 1])
                forwardRes[i] = val;
            else
                forwardRes[i] = forwardRes[i - 1];
        } else {
            forwardRes[i] = forwardRes[i - 1];
            minEl = prices[i];
        }
    }
    //
    vector<int> backwardRes(size, 0);
    int maxEl = prices[size - 1];
    for (int i = size - 2; i >= 0; --i) {
        if (prices[i] < maxEl) {
            int val = maxEl - prices[i];
            if (val > backwardRes[i + 1])
                backwardRes[i] = val;
            else
                backwardRes[i] = backwardRes[i + 1];

        } else {
            backwardRes[i] = backwardRes[i + 1];
            maxEl = prices[i];
        }
    }
    int res = 0;
    for (int i = 0; i < size - 1; ++i) {
        int curRes = forwardRes[i] + backwardRes[i + 1];
        if (curRes > res)
            res = curRes;
    }
    if (forwardRes[size - 1] > res)
        res = forwardRes[size - 1];
    return res;
}