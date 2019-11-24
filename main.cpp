#include <iostream>
#include <vector>
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

using namespace std;
struct Node {
    int data;
    Node *l;
    Node *r;
};

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

int main() {
    auto *root = new Node{1, nullptr, nullptr};
    root->l = new Node{3, nullptr, nullptr};
    root->r = new Node{2, nullptr, nullptr};
    //
    root->l->l = new Node{9, nullptr, nullptr};
    root->l->l->l = new Node{12, nullptr, nullptr};
    root->l->r = new Node{7, nullptr, nullptr};
    root->l->r->l = new Node{8, nullptr, nullptr};
    root->l->r->l->r = new Node{6, nullptr, nullptr};
    root->l->r->l->r->r = new Node{11, nullptr, nullptr};
    //
    root->r->r = new Node{10, nullptr, nullptr};
    root->r->l = new Node{4, nullptr, nullptr};
    root->r->l->r = new Node{5, nullptr, nullptr};
    auto res = distanceK(root, root->l->r, 3);
    for (auto n: res)
        cout << n << ' ';
    return 0;
}
