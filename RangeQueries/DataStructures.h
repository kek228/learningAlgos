#pragma once

class SumSegmentTree {
public:
    explicit SumSegmentTree(const std::vector <int64_t> &origin) {
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
    void _construct(const std::vector <int64_t> &origin) {
        auto n = table.size() / 2;
        for (size_t i = n; i < table.size(); ++i) {
            table[i] = origin[i - n];
        }
        for (size_t i = n - 1; i > 0; --i) {
            table[i] = table[i * 2] + table[i * 2 + 1];
        }
    }

private:
    std::vector <int64_t> table;
};


// Полезная штука для запросов min/max от b до e включительно
class SparseTable {
public:
    explicit SparseTable(const vector<int> &nums) {
        int size = nums.size();
        int k = log2(size) + 1;
        _table.resize(k);
        for (auto &t: _table)
            t = vector<int>(size, 0);
        constructTable(nums);
    }

    // ВКЛЮЧАЯ e
    int getMax(const int b, const int e) {
        int k = log2(e - b + 1);
        return max(_table[k][b], _table[k][e - pow(2, k) + 1]);
    }

private:
    void constructTable(const vector<int> &nums) {
        int size = nums.size();
        for (int i = 0; i < size; ++i)
            _table[0][i] = nums[i];
        for (int k = 1; k < _table.size(); ++k) {
            int curLast = size - pow(2, k) + 1;
            int next = pow(2, k - 1);
            for (int i = 0; i < curLast; ++i)
                _table[k][i] = max(_table[k - 1][i], _table[k - 1][i + next]);
        }
    }

private:
    vector <vector<int>> _table;
};