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


// https://leetcode.com/problems/minimum-window-substring
// отличный пример окна, главное грамотно составить правила для сжатия
bool checkS1inS2(unordered_map<char, int> &s1, unordered_map<char, int> &s2) {
    for (const auto &c1: s1) {
        auto c2 = s2.find(c1.first);
        if (c2 == s2.end())
            return false;
        if (c2->second < c1.second)
            return false;
    }
    return true;
}

void erase(unordered_map<char, int> &smap, const char c) {
    auto it = smap.find(c);
    it->second--;
    if (!it->second)
        smap.erase(it);
}

bool canShrink(const char c, unordered_map<char, int> &smap, unordered_map<char, int> &tmap) {
    auto inT = tmap.find(c);
    if (inT == tmap.end()) {
        return true;
    }
    auto inS = smap.find(c);
    if (inS->second > inT->second)
        return true;
    return false;
}

string minWindow(string s, string t) {
    if (t.empty())
        return t;
    unordered_map<char, int> tmap;
    for (auto c: t)
        ++tmap[c];
    unordered_map<char, int> smap;
    int i = 0;
    int size = s.size();
    for (; i < size; ++i) {
        if (tmap.find(s[i]) != tmap.end())
            break;
    }
    if (t.size() == 1) {
        if (i == size)
            return "";
        else
            return t;
    }

    int j = i;
    int resi = -1;
    int resj = -1;
    int ressize = numeric_limits<int>::max();
    while (j < size) {
        const char c = s[j];
        ++smap[c];
        bool found = checkS1inS2(tmap, smap);
        if (found) {
            // попробуем уменьшить окно
            while (found && i <= j) {
                erase(smap, s[i]);
                found = checkS1inS2(tmap, smap);
                ++i;
            }
            int wsize = j - i + 2;
            if (wsize < ressize) {
                ressize = wsize;
                resi = i - 1;
                resj = j;
            }
            // сейчас found == false, попробуем еще подрезать интервал
            while (canShrink(s[i], smap, tmap) && i < j) {
                erase(smap, s[i]);
                ++i;
            }
        }
        ++j;
    }
    bool found = checkS1inS2(tmap, smap);
    if (found) {
        while (found && i <= j) {
            erase(smap, s[i]);
            found = checkS1inS2(tmap, smap);
            ++i;
        }
        int wsize = j - i + 2;
        if (wsize < ressize) {
            ressize = wsize;
            resi = i - 1;
            resj = j;
        }
    }

    if (resi != -1) {
        return s.substr(resi, resj - resi + 1);
    }
    return "";
}
