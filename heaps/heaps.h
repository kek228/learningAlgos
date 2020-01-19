#pragma once

// Сортировка n отсортированных списков. Часть сортировки файлов когда не влезает в оперативу
// https://leetcode.com/problems/merge-k-sorted-lists/

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *mergeKLists(vector<ListNode *> &lists) {
    if (lists.size() == 0)
        return NULL;
    priority_queue < pair < int, ListNode * >, vector < pair < int, ListNode * >>, greater < pair < int, ListNode * >> >
                                                                                                         heap;
    for (auto &node: lists) {
        if (node) {
            heap.push({node->val, node});
            node = node->next;
        }
    }
    if (heap.empty())
        return NULL;
    ListNode *res = new ListNode{0};
    auto nextNode = heap.top();
    res->val = nextNode.second->val;
    //
    heap.pop();
    if (nextNode.second->next)
        heap.push({nextNode.second->next->val, nextNode.second->next});
    //
    auto cur = res;
    while (!heap.empty()) {
        nextNode = heap.top();
        cur->next = new ListNode{0};
        cur->next->val = nextNode.second->val;
        heap.pop();
        if (nextNode.second->next)
            heap.push({nextNode.second->next->val, nextNode.second->next});
        cur = cur->next;
    }
    return res;
}