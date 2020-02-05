#pragma once

int diff(const unordered_map<char, int> &f, const unordered_map<char, int> &s) {
    int res = 0;
    for (const auto &fchar: f) {
        auto schar = s.find(fchar.first);
        if (schar == s.end())
            res += fchar.second;
        else
            res += abs(fchar.second - schar->second);
    }
    return res;
}

int hmapDiff(const unordered_map<char, int> &f, const unordered_map<char, int> &s) {
    int res = diff(f, s);
    for (const auto &schar: s) {
        auto fchar = f.find(schar.first);
        if (fchar == s.end())
            res += schar.second;
    }
    return res;
}