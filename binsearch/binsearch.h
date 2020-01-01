#pragma once

// https://leetcode.com/problems/find-k-th-smallest-pair-distance/
int smallestDistancePair(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int lo = 0;
    int hi = nums[nums.size() - 1] - nums[0];
    while (lo != hi) {
        int mi = (lo + hi) / 2;
        int count = 0, left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            while (nums[right] - nums[left] > mi)
                left++;
            count += right - left;
        }
        if (count >= k)
            hi = mi;
        else
            lo = mi + 1;
    }
    return lo;
}

//
