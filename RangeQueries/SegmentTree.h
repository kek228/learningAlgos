#pragma once

#include <vector>

class SumSegmentTree {
public:
    SumSegmentTree(const std::vector<T> &origin) {
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
    void _construct(const std::vector<T> &origin) {
        auto n = table.size() / 2;
        for (int i = n; i < n; ++i) {
            table[i] = origin[i - n];
        }
        for (int i = n - 1; i > 0; --i) {
            table[i] = table[i * 2] + table[i * 2 + 1];
        }
    }

private:
    std::vector<int64_t> table;

};