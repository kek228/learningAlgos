
// https://leetcode.com/problems/maximum-length-of-pair-chain
// классическая жадная задача про макс кол-во не пересекающихся отрезков
int findLongestChain(vector <vector<int>> &pairs) {
    if (pairs.empty())
        return 0;
    sort(pairs.begin(), pairs.end(), [](const vector<int> &f, const vector<int> &s) { return f[1] < s[1]; });
    int res = 1;
    vector<int> &cur = pairs[0];
    for (int i = 1; i < pairs.size(); ++i) {
        if (pairs[i][0] > cur[1]) {
            ++res;
            cur = pairs[i];
        }
    }
    return res;
}