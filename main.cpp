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

//class Solution {
//    const vector<vector<int>> graph = {
//            {1, 3, 4},
//            {0, 2, 3, 4, 5},
//            {1, 4, 5},
//            {0, 1, 4, 6, 7},
//            {0, 1, 2, 3, 5, 6, 7, 8},
//            {1, 2, 4, 7, 8},
//            {3, 4, 7},
//            {3, 4, 5, 6, 8},
//            {4, 5, 7}
//    };
//
//    int res = 0;
//public:
//    void _numberOfPatterns(unordered_set<int> &used, const int m, const int n){
//        if(used.size() == 9 && n ==9){
//            ++res;
//            return;
//        }
//        if(used.size() > n)
//            return;
//        if(used.size() >= m)
//            ++res;
//        for(int usedV: used){
//            // список смежности iй вершины в used
//            for(int v: graph[usedV]){
//                auto check = used.find(v);
//                if(check != used.end())
//                    continue;
//                used.insert(v);
//                _numberOfPatterns(used, m, n);
//                used.erase(v);
//            }
//        }
//    }
//
//    int numberOfPatterns(int m, int n) {
//        unordered_set<int> used;
//        for(int i = 0; i < 9; ++i){
//            used.insert(i);
//            _numberOfPatterns(used, m, n);
//            used.erase(i);
//        }
//        return res;
//    }
//};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    int res = numeric_limits<int>::min();
public:
    int whatReturn(int path, int val) {
        int curRes = 0;
        if (path >= 0) {
            if (val >= 0)
                res = max(res, val + path);
            else
                res = max(res, path);
            return val + path;
        } else {
            return val;
        }
    }

    optional<int> _maxPathSum(TreeNode *root) {
        if (!root)
            return numeric_limits<int>::min();;
        if (res < 0)
            res = max(res, root->val);
        auto maxL = _maxPathSum(root->left);
        auto maxR = _maxPathSum(root->right);
        int curRes = 0;

        return 0;
    }

    int maxPathSum(TreeNode *root) {
        _maxPathSum(root);
        return res;
    }
};


int _maxCoins(const vector<int> &nums, const int l, const int r, vector<vector<int>> &cache) {
    if (l + 1 == r) {
        return 0;
    }
    if (cache[l][r] != -1)
        return cache[l][r];
    int res = 0;
    for (int i = l + 1; i < r; ++i) {
        res = max(res, nums[l] * nums[i] * nums[r] +
                       _maxCoins(nums, l, i, cache) + _maxCoins(nums, i, r, cache));
    }
    cache[l][r] = res;
    return res;
}

int maxCoins(vector<int> &nums) {
    if (nums.empty())
        return 0;
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    const int size = nums.size();
    vector<vector<int>> cache(size);
    for (auto &v: cache)
        v = vector<int>(size, -1);
    return _maxCoins(nums, 0, size - 1, cache);
}

int main() {
    //Solution sol;
////    cout<<sol.numberOfPatterns(1, 1);

//    TreeNode *root = new TreeNode{-2};
//    root->left = new TreeNode{-1};
//    root->right = new TreeNode{3};
    //cout << sol.maxPathSum(root);
    vector<int> nums = {3, 1, 5, 8};
    cout << maxCoins(nums);
    return 0;
}


// matrix:
// std::vector of length 4, capacity 4 =
// {std::vector of length 5, capacity 5 = {49 '1', 48 '0', 49 '1', 48 '0', 48 '0'},
// std::vector of length 5, capacity 5 = {49 '1', 48 '0', 49 '1', 49 '1', 49 '1'},
// std::vector of length 5, capacity 5 = {49 '1', 49 '1', 49 '1', 49 '1', 49 '1'},
// std::vector of length 5, capacity 5 = {49 '1', 48 '0', 48 '0', 49 '1', 48 '0'}}
// ["great","acting","skills"]
// ["fine","painting","talent"]
// [["great","fine"],["drama","acting"],["skills","talent"]]