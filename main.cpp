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
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <functional>

using namespace std;

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


int main() {
    vector<int> nums = {3, 1, 1, 5, 2, 2, 2, 2, 5, 1, 1, 1, 0};
    cout << jump(nums);
    return 0;
}
