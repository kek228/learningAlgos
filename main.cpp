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
//#include <optional>
#include <stdint.h>
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <functional>

using namespace std;

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


int main() {
    // cout << minWindow("ADOBECODEBANC", "ABC").data();
    cout << minWindow("aaddabdbddc", "abc").data();
    return 0;
}