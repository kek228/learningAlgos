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

class LRUQueue {
public:
    using ItemCache = std::unordered_map<int, typename std::list<int>::iterator>;

    LRUQueue() = default;

    ~LRUQueue() = default;

    void insert(int item) {
        items.emplace_front(item);
        itemCache[item] = items.begin();
    }

    void insertBack(int pos, int item) {
        auto listItem = itemCache.find(pos);
        auto newPos = items.insert(listItem->second, item);
        itemCache[item] = newPos;
    }

    void erase(int item) {
        auto listItem = itemCache.find(item);
        items.erase(listItem->second);
        itemCache.erase(listItem);
    }

    bool empty() {
        return itemCache.empty();
    }

    size_t size() {
        return itemCache.size();
    }

    string serialize() {
        string res;
        for (auto &el : items)
            res += to_string(el) + "|";
        return res;
    }

    int nextVal(int item) {
        auto listItem = itemCache.find(item);
        auto nextIt = listItem->second;
        ++nextIt;
        if (nextIt == items.end())
            return -1;
        return *nextIt;
    }

    int prevVal(int item) {
        auto listItem = itemCache.find(item);
        auto prevIt = listItem->second;
        if (prevIt == items.begin())
            return -1;
        --prevIt;
        return *prevIt;
    }


    ItemCache itemCache;
    std::list<int> items;
};