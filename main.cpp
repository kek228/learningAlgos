#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iterator>
#include <set>
#include <optional>
#include <stdint.h>
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <functional>

using namespace std;

int maxProfit(vector<int> &prices) {
    int size = prices.size();
    if (size == 0)
        return 0;
    vector<int> forwardRes(size, 0);
    int minEl = prices[0];
    for (int i = 1; i < size; ++i) {
        if (prices[i] > minEl) {
            int val = prices[i] - minEl;
            if (val > forwardRes[i - 1])
                forwardRes[i] = val;
            else
                forwardRes[i] = forwardRes[i - 1];
        } else {
            forwardRes[i] = forwardRes[i - 1];
            minEl = prices[i];
        }
    }
    //
    vector<int> backwardRes(size, 0);
    int maxEl = prices[size - 1];
    for (int i = size - 2; i >= 0; --i) {
        if (prices[i] < maxEl) {
            int val = maxEl - prices[i];
            if (val > backwardRes[i + 1])
                backwardRes[i] = val;
            else
                backwardRes[i] = backwardRes[i + 1];

        } else {
            backwardRes[i] = backwardRes[i + 1];
            maxEl = prices[i];
        }
    }
    int res = 0;
    for (int i = 0; i < size - 1; ++i) {
        int curRes = forwardRes[i] + backwardRes[i + 1];
        if (curRes > res)
            res = curRes;
    }
    if (forwardRes[size - 1] > res)
        res = forwardRes[size - 1];
    return res;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << maxProfit(nums);
    return 0;
}