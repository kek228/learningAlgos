#pragma once

// https://www.hackerrank.com/challenges/play-game/problem
size_t bricksGame(vector<int> arr) {
    auto n = arr.size();
    if (arr.size() <= 3) {
        int res = 0;
        for (auto n: arr) {
            res += n;
        }
        return res;
    }
    // решение для подзадачи [i:n]
    vector <size_t> res(n + 1, 0);
    // в какой индекс надо идти из позиции i
    vector <size_t> steps(n + 1, 0);
    int c = 3;
    int i = n - 1;
    for (; c > 0; --i) {
        res[i] += res[i + 1] + arr[i];
        steps[i] = n;
        --c;
    }
    for (; i >= 0; --i) {
        auto minIter = min_element(res.begin() + i + 1, res.begin() + i + 4);
        auto minId = minIter - res.begin();
        res[i] = res[steps[minId]];
        for (int j = i; j < minId; ++j)
            res[i] += arr[j];
        steps[i] = minId;
    }
    return res[0];
}

// https://leetcode.com/problems/edit-distance
int minDistance(string s1, string s2) {

    int rows = s1.size();
    int cols = s2.size();
    vector <vector<int>> editDst = constructTable(rows, cols);

    bool meet = true;
    if (s1[0] != s2[0]) {
        editDst[0][0] = 1;
        meet = false;
    }

    for (int col = 1; col < cols; ++col) {
        if (s1[0] == s2[col] && !meet) {
            editDst[0][col] = editDst[0][col - 1];
            meet = true;
        } else {
            editDst[0][col] = editDst[0][col - 1] + 1;
        }
    }
    //
    meet = true;
    if (s1[0] != s2[0]) {
        meet = false;
    }
    for (int row = 1; row < rows; ++row) {
        if (s2[0] == s1[row] && !meet) {
            editDst[row][0] = editDst[row - 1][0];
            meet = true;
        } else {
            editDst[row][0] = editDst[row - 1][0] + 1;
        }
    }
    //
    for (int row = 1; row < rows; ++row) {
        for (int col = 1; col < cols; ++col) {
            editDst[row][col] = min(editDst[row - 1][col] + 1, editDst[row][col - 1] + 1);
            int cost = 1;
            if (s1[row] == s2[col])
                cost = 0;
            editDst[row][col] = min(editDst[row][col], editDst[row - 1][col - 1] + cost);
        }
    }
    return editDst[rows - 1][cols - 1];
}

// longest common substring
int longestCommonSubstring(int k, string s1, string s2) {

    int rows = s1.size();
    int cols = s2.size();
    int res = 1;
    auto table = constructTable(rows, cols);
    //
    for (int col = 0; col < cols; ++col) {
        if (s1[0] == s2[col]) {
            table[0][col] = 1;
            res = 1;
        }
    }
    //
    for (int row = 1; row < rows; ++row) {
        if (s2[0] == s1[row]) {
            table[row][0] = 1;
            res = 1;
        }
    }
    //
    for (int row = 1; row < rows; ++row) {
        for (int col = 1; col < cols; ++col) {
            if (s2[col] != s1[row])
                table[row][col] = 0;
            else {
                table[row][col] = table[row - 1][col - 1] + 1;
                if (table[row][col] > res)
                    res = table[row][col];
            }
        }
    }
    return res;
}

// https://www.hackerrank.com/challenges/substring-diff/problem
int processDiag(int row, int col, int l, int k, vector <vector<int>> &table) {
    int zeroCounter = 0;
    int b = 0;
    int e = 1;
    int res = 0;
    // e на 1 вперед
    while (e < l) {
        if (table[row + e - 1][col + e - 1] == 0)
            ++zeroCounter;
        int segmentLength = e - b;
        if (segmentLength > res && zeroCounter <= k)
            res = segmentLength;
        //
        if (zeroCounter > k) {
            while (b < e && zeroCounter > k) {
                ++b;
                if (table[row + b - 1][col + b - 1] == 0)
                    --zeroCounter;
            }
        }
        ++e;
    }
    if (table[row + e - 1][col + e - 1] == 0)
        ++zeroCounter;
    int segmentLength = e - b;
    if (segmentLength > res && zeroCounter <= k)
        res = segmentLength;
    return res;
}

int substringDiff(int k, string s1, string s2) {
    int rows = s1.size();
    int cols = s2.size();
    auto table = constructTable(rows, cols);
    //
    for (int col = 0; col < cols; ++col) {
        if (s1[0] == s2[col]) {
            table[0][col] = 1;
        }
    }
    //
    for (int row = 1; row < rows; ++row) {
        if (s2[0] == s1[row]) {
            table[row][0] = 1;
        }
    }
    //
    for (int row = 1; row < rows; ++row) {
        for (int col = 1; col < cols; ++col) {
            if (s2[col] != s1[row])
                table[row][col] = 0;
            else {
                table[row][col] = table[row - 1][col - 1] + 1;
            }
        }
    }
    //
    int res = 0;
    for (int row = rows - 1; row >= 0; --row) {
        int curRes = processDiag(row, 0, rows - row, k, table);
        if (curRes > res)
            res = curRes;
    }
    for (int col = 1; col < cols; ++col) {
        int curRes = processDiag(0, col, cols - col, k, table);
        if (curRes > res)
            res = curRes;
    }
    return res;
}

// https://leetcode.com/problems/longest-palindromic-subsequence/
int longestPalindromeSubseq(string s) {
    int size = s.size();
    if (size == 0)
        return 0;
    if (size == 1)
        return 1;
    auto resTable = constructTable(size, size);
    resTable[0][0] = 1;
    for (int col = 1; col < size; ++col) {
        resTable[0][col] = 1;
        if (s[col] == s[col - 1])
            resTable[1][col] = 2;
        else
            resTable[1][col] = 1;
    }
    //
    for (int row = 2; row < size; ++row) {
        for (int col = row; col < size; ++col) {
            if (s[col] == s[col - row])
                resTable[row][col] = resTable[row - 2][col - 1] + 2;
            else
                resTable[row][col] = max(resTable[row - 1][col - 1], resTable[row - 1][col]);
        }
    }
    return resTable[size - 1][size - 1];
}