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

class SumSegmentTree {
public:
    explicit SumSegmentTree(const std::vector<int64_t> &origin) {
        auto originSize = origin.size();
        table.resize(originSize * 2);
        _construct(origin);
    }

    int64_t sum(size_t l, size_t r) {
        const auto n = table.size() / 2;
        int64_t res = 0;
        l += n;
        r += n;
        while (l <= r) {
            if (l % 2 == 1)
                res += table[l++];
            if (r % 2 == 0)
                res += table[r--];
            l /= 2;
            r /= 2;
        }
        return res;
    }

    void update(size_t pos, const int64_t val) {
        pos += table.size() / 2;
        table[pos] = val;
        while (pos > 0) {
            table[pos] = table[pos * 2] + table[pos * 2 + 1];
            pos /= 2;
        }
    }

private:
    void _construct(const std::vector<int64_t> &origin) {
        auto n = table.size() / 2;
        for (size_t i = n; i < table.size(); ++i) {
            table[i] = origin[i - n];
        }
        for (size_t i = n - 1; i > 0; --i) {
            table[i] = table[i * 2] + table[i * 2 + 1];
        }
    }

private:
    std::vector<int64_t> table;
};


int main() {
    std::vector<int64_t> origin = {5, 8, 6, 3, 2, 7, 2, 6};
    SumSegmentTree sumSegmentTree(origin);
    cout << sumSegmentTree.sum(2, 6);
    return 0;
}

// Ответы
// 4
// n^2
//
//
// 4
// 372
// 4
// 1021