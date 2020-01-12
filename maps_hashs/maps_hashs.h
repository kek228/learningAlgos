#pragma once

// всякие считалки
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
