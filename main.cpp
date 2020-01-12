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
#include <limits>
#include <list>

using namespace std;

unordered_map<char, int> createCounter(const string &s) {
    unordered_map<char, int> res;
    for (auto c: s)
        ++res[c];
    return res;
}

bool cmp(unordered_map<char, int> &f, unordered_map<char, int> &s) {
    for (auto &fc: f) {
        auto sc = s.find(fc.first);
        if (sc == s.end())
            return false;
        if (fc.second != sc->second)
            return false;
    }
    return true;
}

bool equal(unordered_map<char, int> &f, unordered_map<char, int> &s) {
    if (!f.size() && !s.size())
        return true;
    if (f.size() != s.size())
        return false;
    return cmp(f, s) && cmp(s, f);
}


vector<vector<string>> groupAnagrams(vector<string> &strs) {
    int size = strs.size();
    if (strs.size() == 0)
        return {};

    list<pair<unordered_map<char, int>, int>> annagrams;
    for (int i = 0; i < size; ++i) {
        annagrams.push_back({createCounter(strs[i]), i});
    }
    vector<vector<string>> res;
    vector<string> cur;
    while (!annagrams.empty()) {
        cur.push_back(strs[annagrams.front().second]);
        auto curangr = annagrams.front().first;
        annagrams.pop_front();
        auto it = annagrams.begin();
        while (it != annagrams.end()) {
            if (equal(curangr, (*it).first)) {
                cur.push_back(strs[it->second]);
                annagrams.erase(it++);
            } else
                ++it;
        }
        res.push_back(cur);
        cur = {};
    }
    return res;
}

int main() {
    // vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<string> strs = {"a", "a", "a"};
    auto res = groupAnagrams(strs);
    return 0;
}
