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
    vector<size_t> res(n + 1, 0);
    // в какой индекс надо идти из позиции i
    vector<size_t> steps(n + 1, 0);
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

int main() {
    //cout<<bricksGame({321, 386, 740, 595, 161, 176, 606, 64, 577, 316});
    cout << std::numeric_limits<int>::max();
    return 0;
}
// 249 791 261 588
//   2 147 483 647