#pragma once

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};


// https://leetcode.com/problems/add-two-numbers/
ListNode *addBack(ListNode *cur, int residue) {
    if (!cur)
        return nullptr;

    int curVal = cur->val + residue;
    if (curVal >= 10) {
        residue = 1;
        curVal -= 10;
    } else {
        residue = 0;
    }

    ListNode *res = new ListNode(curVal);
    ListNode *curRes = res;
    cur = cur->next;
    //
    while (cur) {
        curVal = cur->val + residue;
        if (curVal >= 10) {
            residue = 1;
            curVal -= 10;
        } else {
            residue = 0;
        }
        curRes->next = new ListNode(curVal);
        curRes = curRes->next;
        cur = cur->next;
    }
    if (residue)
        curRes->next = new ListNode(residue);
    return res;
}

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    if (!l1)
        return l2;
    if (!l2)
        return l1;

    ListNode *resHead = nullptr;
    resHead = new ListNode(0);
    resHead->val = l1->val + l2->val;
    int residue = 0;
    if (resHead->val >= 10) {
        residue = 1;
        resHead->val -= 10;
    }
    ListNode *curRes = resHead;
    ListNode *curL1 = l1->next;
    ListNode *curL2 = l2->next;

    while (curL1 && curL2) {
        int cur = curL1->val + curL2->val + residue;
        if (cur >= 10) {
            residue = 1;
            cur -= 10;
        } else
            residue = 0;

        curRes->next = new ListNode(cur);
        // advance
        curL1 = curL1->next;
        curL2 = curL2->next;
        curRes = curRes->next;
    }
    if (!curL1 && !curL2) {
        if (residue)
            curRes->next = new ListNode(residue);
    } else if (!curL1 && curL2)
        curRes->next = addBack(curL2, residue);
    else if (!curL2 && curL1)
        curRes->next = addBack(curL1, residue);
    return resHead;
}