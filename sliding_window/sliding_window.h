#pragma once

// https://leetcode.com/problems/subarrays-with-k-different-integers
bool checkVal(unordered_set<int> &vals, int val) {
    auto it = vals.find(val);
    if (it != vals.end())
        return true;
    return false;
}

int subarraysWithKDistinct(vector<int> &A, int k) {
    int size = A.size();
    unordered_map<int, int> vals;
    unordered_set<int> possibleVals;

    int e = 0;
    for (; e < size; ++e) {
        ++vals[A[e]];
        possibleVals.insert(A[e]);
        if (vals.size() == k)
            break;
    }
    if (vals.size() != k)
        return 0;
    int res = 0;
    int b = 0;
    int at_least1 = 0;
    bool outMeet = true;
    while (e < size) {
        // вернем [b, e] к состоянию минимального подмассива
        if (outMeet) {
            outMeet = false;
            at_least1 = 0;
        }
        while (b <= e - k + 1 && vals.size() == k) {
            --vals[A[b]];
            if (vals[A[b]] == 0)
                vals.erase(A[b]);
            if (vals.size() == k) {
                ++res;
                ++at_least1;
            }
            ++b;
        }
        ++at_least1;
        ++res;
        // расширим диапазон
        while (e < size && vals.size() != k) {
            ++e;
            if (e < size && !checkVal(possibleVals, A[e])) {
                outMeet = true;
                break;
            }
            if (e < size)
                ++vals[A[e]];
            if (e < size && !outMeet)
                res += at_least1;
        }
        if (e < size && outMeet) {
            possibleVals.erase(A[b - 1]);
            possibleVals.insert(A[e]);
            ++vals[A[e]];
        }
    }
    return res;
}
