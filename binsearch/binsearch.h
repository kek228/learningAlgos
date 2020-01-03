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

// TODO зарефакторить этот пиздец
// https://leetcode.com/problems/k-th-smallest-prime-fraction/
struct Fraction {
    size_t num;
    size_t div;

    bool operator<(const Fraction &right) {
        if (div != right.div) {
            size_t leftNum = num * right.div;
            size_t rightNum = right.num * div;
            return leftNum < rightNum;
        }
        return num < right.num;
    }

    bool operator<=(const Fraction &right) {
        if (div != right.div) {
            size_t leftNum = num * right.div;
            size_t rightNum = right.num * div;
            return leftNum <= rightNum;
        }
        return num <= right.num;
    }

    bool operator==(const Fraction &right) {
        return num == right.num && div == right.div;
    }
};

Fraction createMiddle(const Fraction &f, const Fraction &s) {
    if (f.div != s.div) {
        size_t dif = f.div * s.div;
        size_t num = (f.num * s.div + s.num * f.div) / 2;
        return {num, dif};
    }
    size_t num = (f.num + s.num) / 2;
    return {num, f.div};
}

double calcDst(Fraction &f, Fraction &s) {
    return abs((double) f.num / f.div - (double) s.num / s.div);
}

vector<int> kthSmallestPrimeFraction(vector<int> &A, int K) {
    int size = A.size();
    if (size == 2)
        return {A[0], A[1]};
    Fraction maxFraction = {(size_t) A[0], (size_t) A[1]};

    for (int i = 1; i < size; ++i) {
        Fraction cur{(size_t) A[i - 1], (size_t) A[i]};
        if (maxFraction < cur)
            maxFraction = cur;
    }
    //
    Fraction lo = {1, (size_t) A[size - 1]};
    Fraction hi = maxFraction;
    Fraction beforeMid; // наиболее близкий к mi снизу
    Fraction afterMid; // наиболее близкий к mi сверху
    while (lo < hi) {
        double beforeDst = numeric_limits<int>::max();
        double aboveDst = numeric_limits<int>::max();
        Fraction mi = createMiddle(lo, hi);
        int count = 0, left = size - 1;
        for (int right = size - 1; right >= 0; --right) {
            if (left == -1)
                left = 0;
            Fraction cur = Fraction{(size_t) A[left], (size_t) A[right]};
            if (left != right && mi < cur) {
                auto dst = calcDst(mi, cur);
                if (dst < aboveDst) {
                    aboveDst = dst;
                    afterMid = cur;
                }
            }
            while (left >= 0 && mi < cur) {
                --left;
                if (left >= 0)
                    cur.num = A[left];
                if (mi < cur) {
                    auto dst = calcDst(mi, cur);
                    if (dst < aboveDst) {
                        aboveDst = dst;
                        afterMid = cur;
                    }
                }
            }
            count += left + 1;
            if (left == -1)
                cur.num = 0;
            // cur, первая меньшая чем dst с таким знаменателем
            auto curDst = calcDst(mi, cur);
            if (curDst < beforeDst) {
                beforeMid = cur;
                beforeDst = curDst;
            }

        }
        if (count == K)
            return {beforeMid.num, beforeMid.div};
        if (count > K)
            hi = beforeMid;
        else {
            lo = afterMid;
        }
    }
    return {lo.num, lo.div};
}