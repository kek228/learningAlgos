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
#include <set>

using namespace std;

vector<vector<int>> constructTable(int rows, int cols) {
    vector<vector<int>> table(rows);
    for (auto &row: table)
        row = vector<int>(cols, 0);
    return table;
}

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


int main() {
    //cout<<longestPalindromeSubseq("kecampaep");
    // cout<<longestPalindromeSubseq("abbkeb");
    // cout<<longestPalindromeSubseq("dkecampaed");
    // cout<<longestPalindromeSubseq("bbbab");
    //cout<<longestPalindromeSubseq("aabaa");
    cout << longestPalindromeSubseq("abcdabcdabcdabcd");

    return 0;
}