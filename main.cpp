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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2) {
    if (!t1)
        return t2;
    if (!t2)
        return t1;
    queue<pair<TreeNode *, bool> > q1;
    queue<TreeNode *> q2;
    q2.push(t2);
    q1.push({t1, false});
    while (!q2.empty()) {
        auto cur2Node = q2.front();
        q2.pop();
        auto[cur1Node, isNewNode] = q1.front();
        q1.pop();
        if (!isNewNode)
            cur1Node->val += cur2Node->val;

        bool addLeft = false;
        if (cur2Node->left) {
            if (!cur1Node->left) {
                addLeft = true;
                cur1Node->left = new TreeNode(cur2Node->left->val);
            }
            q2.push(cur2Node->left);
        }

        bool addRight = false;
        if (cur2Node->right) {
            if (!cur1Node->right) {
                addRight = true;
                cur1Node->right = new TreeNode(cur2Node->right->val);
            }
            q2.push(cur2Node->right);
        }

        if (cur1Node->left)
            q1.push({cur1Node->left, addLeft});
        if (cur1Node->right)
            q1.push({cur1Node->right, addRight});
    }
    return t1;
}

int main() {
    return 0;
}