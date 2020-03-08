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

// https://leetcode.com/problems/median-of-two-sorted-arrays
int ithOfTwoSorted(const int i, const vector<int> &first, const vector<int> &second) {
    int b1 = 0;
    int e1 = first.size() - 1;
    int b2 = 0;
    int e2 = second.size() - 1;
    int last = 0;
    if (i == 0)
        return min(first[b1], second[b2]);
    int from = 0;
    int to = e1 + e2;
    while (b1 <= e1 && b2 <= e2) {
        int _max = max(first[e1], second[e2]);
        int _min = min(first[b1], second[b2]);
        if (_min == _max)
            return _max;
        int m = (_max + _min) / 2;
        auto firstGreater = upper_bound(first.begin() + b1, first.begin() + e1 + 1, m);
        int firstLast = firstGreater - first.begin() - 1;
        auto secondGreater = upper_bound(second.begin() + b2, second.begin() + e2 + 1, m);
        int secondLast = secondGreater - second.begin() - 1;
        last = firstLast + secondLast + 1;
        if (i <= last) {
            e1 = firstLast;
            e2 = secondLast;
            to = last;
        } else {
            b1 = firstLast + 1;
            b2 = secondLast + 1;
            from = b1 + b2;
        }
    }
    if (b1 <= e1) {
        if (b1 == e1)
            return first[b1];
        return first[b1 + i - from];

    }
    if (b2 <= e2) {
        if (b2 == e2)
            return second[b2];
        return second[b2 + i - from];
    }
    return 0;
}


double findMedianSortedArrays(const vector<int> &a, const vector<int> &b) {
    int asize = a.size();
    int bsize = b.size();
    int size = asize + bsize;
    if (!asize && !bsize)
        return 0;
    if (!asize && bsize) {
        if (bsize % 2 == 1)
            return b[bsize / 2];
        else {
            int m = size / 2;
            auto f = b[m];
            auto s = b[m - 1];
            return double(f + s) / 2;
        }
    }

    if (asize && !bsize) {
        if (asize % 2 == 1)
            return a[asize / 2];
        else {
            int m = size / 2;
            auto f = a[m];
            auto s = a[m - 1];
            return double(f + s) / 2;
        }
    }

    if (size % 2 == 1)
        return ithOfTwoSorted(size / 2, a, b);
    else {
        int m = size / 2;
        auto f = ithOfTwoSorted(m, a, b);
        auto s = ithOfTwoSorted(m - 1, a, b);
        return double(f + s) / 2;
    }
}

// https://leetcode.com/problems/search-insert-position
// бинпоиск с поиском места для вставки
int searchInsert(vector<int> &nums, int target) {
    const int size = nums.size();
    if (size == 0)
        return 0;
    if (size == 1) {
        if (nums[0] < target)
            return 1;
        else
            return 0;
    }

    int b = 0;
    int e = size - 1;
    while (b < e) {
        int m = (b + e) / 2;
        if (nums[m] > target) {
            e = m;
        } else if (nums[m] < target) {
            b = m + 1;
        } else {
            return m;
        }
    }
    if (b == size - 1 && nums[b] < target) {
        return size;
    }
    if (e == 0 && nums[e] > target)
        return 0;
    return e;
}