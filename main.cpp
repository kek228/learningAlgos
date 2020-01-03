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
#include <stdint.h>
#include <limits>

using namespace std;

// 4, 10, 4, 3, 8, 9
int lengthOfLIS(vector<int> &nums) {
    int size = nums.size();
    if (size == 0)
        return 0;
    vector<int> res(size, 0);
    res[0] = 1;
    int result = 1;
    for (int i = 1; i < size; ++i) {
        int resi = 1;
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                resi = max(resi, res[j] + 1);
                if (resi > result)
                    result = resi;
            }
        }
        res[i] = resi;
    }
    return result;
}


int main() {
    // vector<int> nums = {4,10,4,3,8,9};
    // vector<int> nums = {10,9,2,5,3,7,101,18};
    vector<int> nums = {1, 3, 6, 7, 9, 4, 10, 5, 6};
    cout << lengthOfLIS(nums);
    return 0;
}
//}