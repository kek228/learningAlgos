#pragma once

// https://leetcode.com/problems/longest-increasing-subsequence/
int lengthOfLIS(vector<int> &nums) {
    int size = nums.size();
    if (size == 0)
        return 0;
    vector<int> res(size, 0);
    res[0] = 1;
    int result = 1;
    for (int i = 1; i < size; ++i) {
        int resi = 1;
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                resi = max(resi, res[j] + 1);
                if (resi > result)
                    result = resi;
            }
        }
        res[i] = resi;
    }
    return result;
}

// LIS за nlogn очень крутое использование бин поиска
int lengthOfLISBinSearch(vector<int> &nums) {
    if (nums.size() == 0)
        return 0;
    // subsequencies[i] на что окончанчивается послед длинной i
    vector<int> subsequencies;
    subsequencies.push_back(nums[0]);
    for (int i = 1; i < nums.size(); ++i) {
        auto firstBigger = lower_bound(subsequencies.begin(), subsequencies.end(), nums[i]);
        if (firstBigger == subsequencies.begin())
            subsequencies[0] = nums[i];
        else if (firstBigger == subsequencies.end())
            subsequencies.push_back(nums[i]);
        else
            *firstBigger = nums[i];
    }
    return subsequencies.size();
}

// https://leetcode.com/problems/longest-common-subsequence/
int longestCommonSubsequence(string text1, string text2) {
    int rows = text1.size() + 1;
    int cols = text2.size() + 1;
    if (rows == 1 || cols == 1)
        return 0;
    auto resTable = constructTable(rows, cols);
    for (int col = 0; col < cols; ++col)
        resTable[0][col] = 0;
    for (int row = 0; row < rows; ++row)
        resTable[row][0] = 0;

    for (int row = 1; row < rows; ++row) {
        for (int col = 1; col < cols; ++col) {
            if (text1[row - 1] == text2[col - 1])
                resTable[row][col] = resTable[row - 1][col - 1] + 1;
            else
                resTable[row][col] = max(resTable[row - 1][col], resTable[row][col - 1]);
        }
    }
    return resTable[rows - 1][cols - 1];
}

// TODO переделать на бинарный поиск
// https://leetcode.com/problems/russian-doll-envelopes/
int maxEnvelopes(vector <vector<int>> &envelopes) {
    int size = envelopes.size();
    if (size == 0)
        return 0;
    //
    sort(envelopes.begin(), envelopes.end(), [](vector<int> &f, vector<int> &s) {
        if (f[0] != s[0])
            return f[0] < s[0];
        return f[1] < s[1];
    });
    vector<int> res(size, 0);
    res[0] = 1;
    int result = 1;
    for (int i = 1; i < size; ++i) {
        int resi = 1;
        for (int j = 0; j < i; ++j) {
            if (envelopes[i][0] > envelopes[j][0] && envelopes[i][1] > envelopes[j][1]) {
                resi = max(resi, res[j] + 1);
                if (resi > result)
                    result = resi;
            }
        }
        res[i] = resi;
    }
    return result;
}

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

// https://www.hackerrank.com/challenges/strplay/problem
int playWithWords(string s) {
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
    //
    int res = 1;
    for (int i = 0; i < size - 1; ++i) {
        int firstMul = resTable[i][i];
        vector<int> &secondPart = resTable[size - i - 2];
        auto secondMul = secondPart.back();
        auto curRes = firstMul * secondMul;
        if (curRes > res)
            res = curRes;
    }
    return res;
}

// https://www.hackerrank.com/challenges/sherlock-and-cost
int cost(vector<int> b) {
    int size = b.size();
    auto table = constructTable(2, size);
    for (int i = 1; i < size; ++i) {
        // решение заканчивается на 1
        table[0][i] = max(table[0][i - 1] + 0, table[1][i - 1] + abs(b[i - 1] - 1));
        // решение заканчивается на макс возможное
        table[1][i] = max(table[0][i - 1] + abs(b[i] - 1), table[1][i - 1] + abs(b[i] - b[i - 1]));
    }
    return max(table[0][size - 1], table[1][size - 1]);
}

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown
int maxProfit(vector<int> &prices) {
#define BUY 0
#define SELL 1
#define BUY_WAIT 2
#define SELL_WAIT 3
#define WAIT 4
    if (prices.size() < 2)
        return 0;
    int cols = static_cast<int>(prices.size());
    int rows = 5;
    auto table = constructTable(rows, cols);
    for (int row = 0; row < 5; ++row) {
        table[row][0] = numeric_limits<int>::min();
    }
    table[BUY][0] = -prices[0];
    table[WAIT][0] = 0;
    for (int col = 1; col < cols; ++col) {
        table[BUY][col] = max(table[SELL_WAIT][col - 1], table[WAIT][col - 1]) - prices[col];
        //
        table[SELL][col] = max(table[BUY][col - 1], table[BUY_WAIT][col - 1]) + prices[col];
        //
        table[BUY_WAIT][col] = max(table[BUY][col - 1], table[BUY_WAIT][col - 1]);
        //
        table[SELL_WAIT][col] = max(table[SELL][col - 1], table[SELL_WAIT][col - 1]);
        //
        table[WAIT][col] = 0;
    }
    int res = table[0][cols - 1];
    for (int row = 0; row < 5; ++row) {
        if (table[row][cols - 1] > res)
            res = table[row][cols - 1];
    }
    return res;
}

// https://www.hackerrank.com/challenges/two-robots/
int twoRobots(int m, vector <vector<int>> queries) {
    auto nqueries = queries.size();
    vector <vector<int>> table(nqueries + 1);
    for (auto &row: table)
        row = vector<int>(nqueries + 1, numeric_limits<int>::max());
    table[1][0] = abs(queries[0][1] - queries[0][0]);
    for (int i = 1; i < nqueries; ++i) {
        for (int j = 0; j < i; ++j) {
            // шаг c i
            auto queryPath = abs(queries[i][1] - queries[i][0]);
            //
            auto stepi = table[i][j] + abs(queries[i - 1][1] - queries[i][0]) + queryPath;
            table[i + 1][j] = min(table[i + 1][j], stepi);
            // шаг с j
            auto stepj = table[i][j] + queryPath;
            if (j != 0)
                stepj += abs(queries[j - 1][1] - queries[i][0]);
            table[i + 1][i] = min(table[i + 1][i], stepj);
        }
    }
    return *min_element(table.back().begin(), table.back().end());
}

// https://leetcode.com/problems/decode-ways/
enum class WAYS {
    ZERO, ADD_MIN_ONE, ADD_MIN_TWO, ADD_BOTH
};

int MAX_CODE = 26;

WAYS hasTwoWays(const char f, const char s) {
    int fval = f - '0';
    int sval = s - '0';
    int total = fval * 10 + sval;
    // WAYS::ZERO
    // "00"
    if (total == 0)
        return WAYS::ZERO;
    // "[3, 9]0" [] -> любой из включительно
    if (total > MAX_CODE && sval == 0)
        return WAYS::ZERO;

    // WAYS::ADD_MIN_ONE
    // "0[1,9]"
    if (fval == 0)
        return WAYS::ADD_MIN_ONE;
    // [3,9][1,9]
    if (total > MAX_CODE)
        return WAYS::ADD_MIN_ONE;

    // WAYS::ADD_MIN_TWO
    if (total == 10 || total == 20)
        return WAYS::ADD_MIN_TWO;
    //остальные
    return WAYS::ADD_BOTH;
}

int numDecodings(string s) {
    if (s[0] == '0')
        return 0;
    int res = 1;
    int n_minus_1 = 1;
    int n_minus_2 = 1;
    int cur = 1;
    while (cur < s.size()) {
        auto ways = hasTwoWays(s[cur - 1], s[cur]);
        if (ways == WAYS::ZERO)
            return 0;
        else if (ways == WAYS::ADD_MIN_ONE)
            res = n_minus_1;
        else if (ways == WAYS::ADD_MIN_TWO) {
            res = n_minus_2;
        } else
            res = n_minus_1 + n_minus_2;
        n_minus_2 = n_minus_1;
        n_minus_1 = res;
        ++cur;
    }
    return res;
}

// https://leetcode.com/problems/wildcard-matching/
vector <vector<int>> constructTable(int rows, int cols) {
    vector <vector<int>> table(rows);
    for (auto &row: table)
        row = vector<int>(cols, 0);
    return table;
}

bool isMatch(string s, string p) {
    int rows = p.size();
    int cols = s.size();

    if (!rows && !cols)
        return true;

    if (rows == 1 && p[0] == '*')
        return true;

    if (!rows && cols)
        return false;


    if (rows && !cols)
        return false;


    auto table = constructTable(rows, cols);
    bool match = false;

    if (p[0] == '*')
        table[0] = vector<int>(cols, 1);
    else {
        if (p[0] == '?' || p[0] == s[0])
            table[0][0] = 1;
        match = true;
    }

    for (int i = 1; i < rows; ++i) {
        if (p[i] == '*' && table[i - 1][0])
            table[i][0] = true;
        else {
            if (p[i - 1] == '*' && (p[i] == s[0] || p[i] == '?') && table[i - 1][0] && !match)
                table[i][0] = true;
            match = true;
        }
    }
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            if (p[i] == '*')
                table[i][j] = table[i - 1][j - 1] || table[i - 1][j] || table[i][j - 1];
            else {
                if (!table[i - 1][j - 1])
                    table[i][j] = false;
                else {
                    if (p[i] == '?')
                        table[i][j] = true;
                    else {
                        if (p[i] == s[j])
                            table[i][j] = true;
                        else
                            table[i][j] = false;
                    }
                }
            }
        }
    }
    return table[rows - 1][cols - 1];
}

// https://leetcode.com/problems/unique-binary-search-trees-ii/
// дано число n, а ты построй все возможные бин деревья ПОИСКА с нодами от 1 до n
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    using TreeList = vector<TreeNode *>;
    vector <vector<TreeList>> results;
public:
    TreeList allFromTo(int first, int last) {
        if (first > last) {
            return {nullptr};
        }
        if (results[first - 1][last - 1].size() != 0) {
            return results[first - 1][last - 1];
        }
        TreeList res;
        for (int i = first; i <= last; ++i) {
            auto possibleLeftTrees = allFromTo(first, i - 1);
            auto possibleRightTrees = allFromTo(i + 1, last);
            for (auto &leftTree: possibleLeftTrees) {
                for (auto &rightTree: possibleRightTrees) {
                    auto root = new TreeNode{i};
                    root->left = leftTree;
                    root->right = rightTree;
                    res.push_back(root);
                }
            }
        }
        results[first - 1][last - 1] = move(res);
        return results[first - 1][last - 1];
    }

    vector<TreeNode *> generateTrees(int n) {
        if (n == 0)
            return {};
        results.resize(n);
        for (auto &row: results) {
            row.resize(n);
        }
        //
        for (int i = 1; i <= n; ++i) {
            auto root = new TreeNode(i);
            results[i - 1][i - 1] = TreeList{root};
        }
        //
        auto res = allFromTo(1, n);
        return res;
    }
};

// https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule
// отлично зашла SparseTable
int minDifficulty(vector<int> &jobDifficulty, int days) {
    int jobs = jobDifficulty.size();
    if (days > jobs)
        return -1;
    vector <vector<int>> results(days);
    for (auto &day: results)
        day = vector<int>(jobs, numeric_limits<int>::max());

    SparseTable table(jobDifficulty);
    int maxJobsPerDay = jobs - days + 1;
    for (int i = 0; i < maxJobsPerDay; ++i)
        results[0][i] = table.getMax(0, i);

    for (int day = 0; day < days - 1; ++day) {
        int curLastJob = day + maxJobsPerDay;
        for (int job = day; job < curLastJob; ++job) {
            for (int nextJob = job + 1; nextJob < curLastJob + 1; ++nextJob) {
                int jval = table.getMax(job + 1, nextJob) + results[day][job];
                results[day + 1][nextJob] = min(results[day + 1][nextJob], jval);
            }

        }
    }
    return results[days - 1][jobs - 1];

}


// https://www.hackerrank.com/challenges/swappermutation/problem
//int main() {
//    const int N = 5;
//    const int K = 4;
//    int dp[N + 1][K + 1];
//
//    for(int i = 0; i <= N; i++)
//        dp[i][0] = 1;
//
//    for(int i = 1; i <= N; i++) {
//        for (int j = 1; j <= K; j++) {
//            for (int k = 0; k <= i - 1 && k <= j; k++) {
//                dp[i][j] += dp[i - 1][j - k];
//            }
//        }
//    }
//    return 0;
//}