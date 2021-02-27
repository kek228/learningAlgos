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
#include <thread>

using namespace std;

class Solution {
public:
    int minSwap(vector<int> &A, vector<int> &B) {
        int s = 1; // i-1 элемент мы крутанули
        int n = 0; // i-1 элемент мы НЕ крутанули
        // 3 варианта :
        // ВАРИАНТ 1
        // 1 min(A[i], B[i]) > max(A[i-1], B[i-1]) -> можно
        // куритить а можно и не крутить оба iх > i - 1 х
        // общее для 2 и 3 что: min(A[i-1], B[i-1]) <= min(A[i], B[i]) < max(A[i-1], B[i-1])
        // ВАРИАНТ 2
        // A[i] <= A[i-1] || B[i] <= B[i-1]
        // мы обязанны крутануть относительно нормального положения i-1 элемента
        // а если i-1 уже покручен то не надо крутить
        // ВАРИАНТ 3
        // это нормальное положение при общем условии для 2 и 3
        // Если бы i-1 был покручен то надо было бы покрутить, но в нормальном положении i-1 не надо
        for (int i = 1; i < A.size(); ++i) {
            if (min(A[i], B[i]) > max(A[i - 1], B[i - 1])) {
                int _s = min(s, n) + 1;
                n = min(s, n);
                s = _s;
            } else {
                if (A[i] <= A[i - 1] || B[i] <= B[i - 1]) {
                    int _s = n + 1;
                    n = s;
                    s = _s;
                } else {
                    s = s + 1;
                    n = n;
                }
            }
        }
        return min(s, n);
    }
};

int main() {
    Solution s;
    vector<int> rowSum = {0, 3, 5, 8, 9};
    vector<int> colSum = {2, 1, 4, 6, 9};
    cout << s.minSwap(rowSum, colSum);
    return 0;
}
