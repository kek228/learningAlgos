#pragma once

// https://leetcode.com/problems/remove-duplicate-letters
// Удаление повторов чтобы был лексиграфический порядок
string smallestSubsequence(string text) {
    if (text.empty())
        return "";
    string res;
    unordered_map<char, int> frequencies;
    for (const char c: text)
        ++frequencies[c];
    unordered_set<char> inRes;
    //
    res.push_back(text[0]);
    inRes.insert(text[0]);
    --frequencies[text[0]];
    if (frequencies[text[0]] == 0)
        frequencies.erase(text[0]);
    for (int i = 1; i < text.size(); ++i) {
        const char c = text[i];
        // if it's not in solution
        if (inRes.find(c) == inRes.end()) {
            // this is not the last c character
            while (!res.empty() && res.back() > c) {
                const char last = res.back();
                // no more last characters
                if (frequencies.find(last) == frequencies.end())
                    break;
                else {
                    inRes.erase(res.back());
                    res.pop_back();
                }
            }
            res.push_back(c);
            inRes.insert(c);
        }
        --frequencies[c];
        if (frequencies[c] == 0)
            frequencies.erase(c);
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