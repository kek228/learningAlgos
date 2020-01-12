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
#include <limits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int countNodes(TreeNode *root) {
    if (!root)
        return 0;
    queue<TreeNode *> q;
    q.push(root);
    int res = 0;
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        ++res;
        if (node->left)
            q.push(node->left);
        else
            return res + q.size();

        if (node->right)
            q.push(node->right);
        else
            return res + q.size();

    }
    return -1;
}

int main() {
    return 0;
}
