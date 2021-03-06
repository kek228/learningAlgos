#pragma once

struct Node {
    int data;
    Node *l;
    Node *r;
};

/* ДИАМЕТР ДЕРЕВА */
int treeDiam(Node *node, int &res) {
    if (!node)
        return 0;
    int ldst = treeDiam(node->l, res);
    int rdst = treeDiam(node->r, res);
    res = max(ldst + rdst + 1, res);
    return max(ldst, rdst) + 1;
}

/* kй сверху наследник */
Node *res;
void findKAns(Node *node, int val, int &k, bool &found) {
    if (!node)
        return;
    if (node->data == val) {
        found = true;
        return;
    }
    if (!found)
        findKAns(node->l, val, k, found);
    if (!found)
        findKAns(node->r, val, k, found);
    if (found) {
        --k;
        if (k == 0)
            res = node;
    }
}


//auto *root = new Node{1, nullptr, nullptr};
//root->l = new Node{3, nullptr, nullptr};
//root->r = new Node{2, nullptr, nullptr};
////
//root->l->l = new Node{4, nullptr, nullptr};
//root->l->l->l = new Node{5, nullptr, nullptr};
//root->l->l->l->r = new Node{11, nullptr, nullptr};
////
//root->l->r = new Node{6, nullptr, nullptr};
//root->l->r->r= new Node{8, nullptr, nullptr};
//root->l->r->l = new Node{7, nullptr, nullptr};
//root->l->r->l->r = new Node{9, nullptr, nullptr};
//root->l->r->l->r->r = new Node{10, nullptr, nullptr};
//root->l->r->l->r->r->r = new Node{11, nullptr, nullptr};

/* ВСЕ НОДЫ НА РАССТОЯНИИ K*/
void findDown(Node *node, int k, vector<int> &res) {
    if (!node)
        return;
    if (k == 0) {
        res.push_back(node->data);
        return;
    }
    findDown(node->l, k - 1, res);
    findDown(node->r, k - 1, res);
}

bool kdst(Node *node, int val, int &k, vector<int> &res) {
    if (!node)
        return false;
    if (node->data == val) {
        findDown(node->l, k - 1, res);
        findDown(node->r, k - 1, res);
        return true;
    }
    auto fl = kdst(node->l, val, k, res);
    auto fr = kdst(node->r, val, k, res);
    if (fl) {
        --k;
        if (k == 0)
            res.push_back(node->data);
        else
            findDown(node->r, k - 1, res);
    }
    if (fr) {
        --k;
        if (k == 0)
            res.push_back(node->data);
        else
            findDown(node->l, k - 1, res);
    }
    return fl || fr;
}

vector<int> distanceK(Node *root, Node *target, int K) {
    vector<int> res;
    if (K == 0) {
        res.push_back(target->data);
        return res;
    }

    kdst(root, target->data, K, res);
    return res;
}

//auto *root = new Node{1, nullptr, nullptr};
//root->l = new Node{3, nullptr, nullptr};
//root->r = new Node{2, nullptr, nullptr};
////
//root->l->l = new Node{9, nullptr, nullptr};
//root->l->l->l = new Node{12, nullptr, nullptr};
//root->l->r = new Node{7, nullptr, nullptr};
//root->l->r->l = new Node{8, nullptr, nullptr};
//root->l->r->l->r = new Node{6, nullptr, nullptr};
//root->l->r->l->r->r = new Node{11, nullptr, nullptr};
////
//root->r->r = new Node{10, nullptr, nullptr};
//root->r->l = new Node{4, nullptr, nullptr};
//root->r->l->r = new Node{5, nullptr, nullptr};
//auto res = distanceK(root, root->l->r, 3);
//for(auto n: res)
//cout<<n<<' ';

// https://leetcode.com/problems/count-complete-tree-nodes
// COMPLETE это такие у которых нижний запонен до упора влево, надо посчитать ноды
//          1
//       2     3
//     4  5  6

int countNodes(TreeNode *root) {
    if (!root)
        return 0;
    queue < TreeNode * > q;
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

void findMin(TreeNode *root, std::vector<int> &res) {
    if (!root)
        return;
    findMin(root->left, res);
    res.push_back(root->val);
    findMin(root->right, res);
}


// https://leetcode.com/problems/minimum-absolute-difference-in-bst
// внезапно ниасилил простую сходу
int getMinimumDifference(TreeNode *root) {
    if (!root)
        return 0;
    std::vector<int> res;
    findMin(root, res);

    int diff = numeric_limits<int>::max();
    for (int i = 0; i < res.size() - 1; ++i) {
        int curD = res[i + 1] - res[i];
        if (curD < diff)
            diff = curD;
    }
    return diff;
}

// https://leetcode.com/problems/maximum-width-of-binary-tree
// максимальная ширина бинарного дерева
// фишка это вычисление позиции ноды в очереди
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *root = new TreeNode{1};
root->
left = new TreeNode{2};
root->left->
left = new TreeNode{4};
root->left->
right = new TreeNode{5};
root->
right = new TreeNode{3};
root->right->
right = new TreeNode{6};
cout<<
widthOfBinaryTree(root);
//         1
//       /   \
//      2     3
//     / \     \
//    4   5     6

int widthOfBinaryTree(TreeNode *root) {
    if (!root)
        return 0;
    queue <pair<TreeNode *, size_t>> q;
    q.push({root, 0});
    //
    int res = 0;
    int dst = 0;
    pair < TreeNode * , int > firstFound = {root, 0};
    size_t curMaxId = 1;
    while (!q.empty()) {
        auto curNode = q.front();
        q.pop();
        if (curNode.second < curMaxId) {
            dst = curNode.second - firstFound.second + 1;
            if (dst > res)
                res = dst;
        } else {
            firstFound = curNode;
            curMaxId = curMaxId * 2 + 1;
        }


        // сквозной индекс
        if (curNode.first->left) {
            size_t ind = curNode.second * 2 + 1;
            q.push({curNode.first->left, ind});
        }
        if (curNode.first->right) {
            size_t ind = curNode.second * 2 + 2;
            q.push({curNode.first->right, ind});
        }
        //
    }
    return res;
}

// https://leetcode.com/problems/merge-two-binary-trees
// занятная задача на мерж деревьев
void merge(TreeNode *n1, TreeNode *n2, TreeNode *n1root, bool left) {
    if (!n2)
        return;
    if (!n1) {
        if (left) {
            n1root->left = new TreeNode(n2->val);
            n1 = n1root->left;
        } else {
            n1root->right = new TreeNode(n2->val);
            n1 = n1root->right;
        }
    } else {
        n1->val += n2->val;
    }
    merge(n1->left, n2->left, n1, true);
    merge(n1->right, n2->right, n1, false);
}

TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2) {
    if (!t1)
        return t2;
    if (!t2)
        return t1;
    t1->val += t2->val;
    merge(t1->left, t2->left, t1, true);
    merge(t1->right, t2->right, t1, false);
    return t1;
}