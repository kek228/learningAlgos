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
//#include <optional>
#include <stdint.h>
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <functional>

using namespace std;

int firstMissingPositive(vector<int> &nums) {
    int size = nums.size();
    int minVal = numeric_limits<int>::max();
    for (const auto n: nums) {
        if (n > 0 && n < minVal)
            minVal = n;
    }
    if (minVal != 1)
        return 1;

    for (int i = 0; i < size; ++i) {
        int realId = nums[i] - 1;
        while (realId >= 0 && realId < size) {
            swap(nums[realId], nums[i]);
            realId = nums[i] - 1;
            if (nums[i] == i + 1)
                break;
            if (nums[i] == nums[realId])
                break;
        }
    }
    for (int i = 0; i < size; ++i) {
        if (nums[i] != i + 1)
            return i + 1;
    }
    return size + 1;
}


int main() {
    // vector<int> nums = {3,4,-1,1};
    vector<int> nums = {1, 1};
    cout << firstMissingPositive(nums);
    return 0;
}