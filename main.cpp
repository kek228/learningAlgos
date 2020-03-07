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
struct Bar {
    int index;
    int h;
    int usedh;
};

int trap(vector<int> &height) {
    int size = height.size();
    if (size == 0)
        return 0;
    stack<Bar> barStack;
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


int main() {
    vector<int> nums = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << trap(nums);
    return 0;
}


//vector<string> req_skills = {"java","nodejs","reactjs"};
//vector<vector<string>> people = {{"java"},{"nodejs"},{"nodejs","reactjs"}};
//cout << smallestSufficientTeam(req_skills, people);

// vector<int> rods = {1,2,2,3,3};
// vector<int> rods = {2, 4, 8, 16};
// vector<int> rods = {1,2,3,4,5,6};
// vector<int> rods = {1,2};
// vector<int> rods = {100, 100};

// vector<int> rods = {4, 3, 2, 3, 5, 2, 1};
// rods = { 5, 5, 4, 1 };
// rods = { 5, 5, 4, 1 };
