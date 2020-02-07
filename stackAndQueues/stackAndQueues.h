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

// https://leetcode.com/problems/jump-game-ii/
// сделал jump-game, но видимо счетерил.
// TODO подумать над жадным решением
int jump(vector<int> &nums) {
    int size = nums.size();
    if (size < 2)
        return 0;
    deque<int> path;
    path.push_back(size - 1);
    for (int i = size - 2; i >= 0; --i) {
        if (i + nums[i] == path.front()) {
            path.push_front(i);
            continue;
        }

        int firstPossible = path.size();
        auto it = path.rbegin();
        for (; it != path.rend(); ++it) {
            if (i + nums[i] >= *it) {
                --firstPossible;
                break;
            }
            --firstPossible;
        }
        for (int j = 0; j < firstPossible; ++j)
            path.pop_front();
        path.push_front(i);
    }
    return path.size() - 1;
}

// https://leetcode.com/problems/sliding-window-maximum/
// супер показательная задача на очередь
vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    int size = nums.size();
    if (size == 0)
        return {};

    deque<int> decrQ;
    decrQ.push_front(0);
    for (int i = 1; i < k; ++i) {
        if (nums[i] >= nums[decrQ.front()]) {
            while (!decrQ.empty() && nums[i] >= nums[decrQ.front()])
                decrQ.pop_front();
            decrQ.push_front(i);
        } else {
            decrQ.push_front(i);
        }
    }
    vector<int> res;
    res.push_back(nums[decrQ.back()]);
    for (int i = k; i < size; ++i) {
        if (decrQ.back() < i - k + 1)
            decrQ.pop_back();
        if (nums[i] >= nums[decrQ.front()]) {
            while (!decrQ.empty() && nums[i] >= nums[decrQ.front()])
                decrQ.pop_front();
            decrQ.push_front(i);
        } else {
            decrQ.push_front(i);
        }
        res.push_back(nums[decrQ.back()]);
    }
    return res;
}

// самый большой прямоугольник из гистограммы
// https://leetcode.com/problems/largest-rectangle-in-histogram
struct Rect {
    int start;
    int height;
    int area;

    int length() {
        return area / height;
    }
};

void addRectangle(const int h, vector <Rect> &rects, int insertPos, int &res) {
    if (rects.empty() && h != 0)
        rects.push_back({insertPos, h, h});
    if (rects.empty() && h == 0)
        return;

    auto last = rects.back();
    int newStart = insertPos;
    while (!rects.empty() && last.height > h) {
        last.area = last.height * (insertPos - last.start);
        if (last.area > res) {
            res = last.area;
        }
        int possibleA = (insertPos - last.start + 1) * h;
        if (possibleA > res)
            res = possibleA;

        newStart = last.start;
        rects.pop_back();
        if (!rects.empty())
            last = rects.back();
    }
    if (rects.empty()) {
        if (h == 0)
            return;

        int newArea = h * (insertPos - newStart + 1);
        rects.push_back({newStart, h, newArea});
    } else {
        // back().height <= h
        // обновляем в любом случае
        int backArea = rects.back().height * (insertPos - rects.back().start + 1);
        rects.back().area = backArea;

        if (rects.back().height < h) {
            int newArea = h * (insertPos - newStart + 1);
            rects.push_back({newStart, h, newArea});
        }
    }
}

int largestRectangleArea(vector<int> &heights) {
    int size = heights.size();
    if (size == 0)
        return 0;
    vector <Rect> rects;
    int start = 0;
    while (start < size && heights[start] == 0)
        ++start;
    if (start == size)
        return 0;

    int res = 0;
    for (int i = start; i < size; ++i) {
        addRectangle(heights[i], rects, i, res);
        if (rects.size() == 100500) {
            cout << 1;
        }
    }
    if (rects.empty())
        return res;

    int lastPos = rects.back().start + rects.back().length() - 1;
    for (int i = 0; i < rects.size(); ++i) {
        auto r = rects[i];
        r.area = r.height * (lastPos - r.start + 1);
        if (r.area > res)
            res = r.area;
    }
    return res;
}