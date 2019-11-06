#pragma once

// задача о расписании pair->first: deadline pair->second: price
int scheduleTask(vector <pair<int, int>> &tasks) {
    vector<bool> used(tasks.size(), false);
    int res = 0;
    sort(tasks.begin(), tasks.end(), [](pair<int, int> &l, pair<int, int> &r) { return l.first < r.first; });
    for (auto &t: tasks) {
        int index = t.first;
        while (index >= 0 && used[index]) {
            --index;
        }
        if (index >= 0) {
            used[index] = true;
            res += t.second;
        }
    }
    return res;
}
