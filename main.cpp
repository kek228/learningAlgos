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
#include <limits>
#include <fstream>
#include <set>
#include <optional>

using namespace std;

int deleteAndEarn(vector<int> &nums) {
    if (nums.size() == 0)
        return 0;

    int N = *max_element(nums.begin(), nums.end());
    vector<int> counters(N + 1, 0);
    for (auto n : nums) {
        ++counters[n];
    }
    vector<pair<int, int>> groups;
    int res = 0;
    int start = 0;
    while (start < N + 1) {
        if (counters[start] != 0) {
            if (start != N && counters[start + 1] != 0) {
                int j = start + 1;
                while (j < N && counters[j] != 0)
                    ++j;
                groups.push_back({start, j});
                start = j + 1;
            } else {
                res += start * counters[start];
                ++start;
            }
        } else {
            ++start;
        }
    }
    //
    for (auto &g: groups) {
        int pp = counters[g.first] * (g.first);
        int p = counters[g.first + 1] * (g.first + 1);
        if (p < pp)
            p = pp;
        int curRes = max(p, pp);
        for (int i = g.first + 2; i <= g.second; ++i) {
            int add = counters[i] * (i);
            if (add + pp > p) {
                int _prev = add + pp;
                pp = p;
                p = _prev;
            } else {
                pp = p;
            }
            curRes = p;
        }
        res += curRes;
    }
    return res;
}


int main() {
    vector<int> nums = {10, 8, 4, 2, 1, 3, 4, 8, 2, 9, 10, 4, 8, 5, 9, 1, 5, 1, 6, 8, 1, 1, 6, 7, 8, 9, 1, 7, 6, 8, 4,
                        5, 4, 1, 5, 9, 8, 6, 10, 6, 4, 3, 8, 4, 10, 8, 8, 10, 6, 4, 4, 4, 9, 6, 9, 10, 7, 1, 5, 3, 4, 4,
                        8, 1, 1, 2, 1, 4, 1, 1, 4, 9, 4, 7, 1, 5, 1, 10, 3, 5, 10, 3, 10, 2, 1, 10, 4, 1, 1, 4, 1, 2,
                        10, 9, 7, 10, 1, 2, 7, 5};
    cout << deleteAndEarn(nums) << endl;
    nums = {3, 4, 2};
    cout << deleteAndEarn(nums) << endl;
    nums = {1};
    cout << deleteAndEarn(nums) << endl;
    return 0;
}