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
    int h;
};

int largestRectangleArea(vector<int> &heights) {
    const int size = heights.size();
    if (size == 0)
        return 0;
    vector <Rect> rectStack;
    rectStack.push_back({0, heights[0]});
    int res = 0;
    for (int i = 1; i < size; ++i) {
        if (heights[i] > rectStack.back().h) {
            rectStack.push_back({i, heights[i]});
        }
        if (heights[i] < rectStack.back().h) {
            int lastStart = -1;
            while (!rectStack.empty() && heights[i] < rectStack.back().h) {
                auto popedRect = rectStack.back();
                rectStack.pop_back();
                const int popedArea = (i - popedRect.start) * popedRect.h;
                lastStart = popedRect.start;
                if (popedArea > res)
                    res = popedArea;
            }
            rectStack.push_back({lastStart, heights[i]});
        }
    }
    for (const auto &r: rectStack) {
        const int area = (size - r.start) * r.h;
        if (area > res)
            res = area;
    }
    return res;
}

// https://leetcode.com/problems/trapping-rain-water/ почти без ошибок
// ВСЕГДА ПРОВЕРЯЙ НА ПУСТОТУ ЕСЛИ СДЕЛАЛ ПОП
struct Bar {
    int index;
    int h;
    int usedh;
};

int trap(vector<int> &height) {
    int size = height.size();
    if (size == 0)
        return 0;
    stack <Bar> barStack;
    int start = 1;
    for (; start < size; ++start) {
        if (height[start] < height[start - 1])
            break;
    }
    start--;
    int res = 0;
    barStack.push({start, height[start], 0});
    for (int i = start + 1; i < size; ++i) {
        if (height[i] >= barStack.top().h) {
            const int newh = height[i];
            while (!barStack.empty()) {
                if (barStack.top().h < newh) {
                    auto topBar = barStack.top();
                    barStack.pop();
                    res += (topBar.h - topBar.usedh) * (i - topBar.index - 1);
                    if (!barStack.empty())
                        barStack.top().usedh = topBar.h;
                } else {
                    auto topBar = barStack.top();
                    res += (newh - topBar.usedh) * (i - topBar.index - 1);
                    break;
                }
            }
        }
        barStack.push({i, height[i], 0});
    }
    return res;
}