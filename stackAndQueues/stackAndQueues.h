#pragma once

// https://leetcode.com/problems/remove-duplicate-letters
// нужно удалить все повторы и вывести первую в лексиграф порядки строку без повторов
// решил мапой из dqueue
bool okToInsert(map<char, deque<int>> &charIds, decltype(charIds.begin()) start,
                int lastId, int idFrom) {
    auto it = start;
    ++it;
    if (it == charIds.end())
        it = charIds.begin();
    while (it->second.front() < lastId)
        it->second.pop_front();
    //
    while (it != start) {
        if (it->second.back() < idFrom)
            return false;
        ++it;
        if (it == charIds.end())
            it = charIds.begin();
        while (it->second.front() < lastId)
            it->second.pop_front();
    }
    return true;
}

std::pair<char, int> findNextChar(map<char, deque<int>> &charIds, int lastId) {
    auto wantInsert = charIds.begin();
    while (wantInsert->second.front() < lastId)
        wantInsert->second.pop_front();
    //
    while (!okToInsert(charIds, wantInsert, lastId, wantInsert->second.front())) {
        ++wantInsert;
    }
    char nextChar = wantInsert->first;
    int newLastId = wantInsert->second.front();
    charIds.erase(wantInsert);
    return {nextChar, newLastId};
}

string removeDuplicateLetters(string s) {
    int size = s.size();
    if (size == 0)
        return "";
    map<char, deque<int>> charIds;
    for (int i = 0; i < size; ++i) {
        auto c = s[i];
        auto qptr = charIds.find(c);
        if (qptr == charIds.end())
            charIds[c] = {};
        charIds[c].push_back(i);
    }
    //
    string res = "";
    char nextChar;
    int lastId = -1;
    while (!charIds.empty()) {
        tie(nextChar, lastId) = findNextChar(charIds, lastId);
        res.push_back(nextChar);
    }
    return res;
}
