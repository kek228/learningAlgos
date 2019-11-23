#pragma once

struct Node {
    int data;
    Node *l;
    Node *r;
};

int treeDiam(Node *node, int &res) {
    if (!node)
        return 0;
    int ldst = treeDiam(node->l, res);
    int rdst = treeDiam(node->r, res);
    res = max(ldst + rdst + 1, res);
    return max(ldst, rdst) + 1;
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
