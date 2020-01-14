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
#include <limits>
#include <list>

using namespace std;
int ithOfTwoSorted(const int i, const vector<int> &first, const vector<int> &second) {
    int b1 = 0;
    int e1 = first.size() - 1;
    int b2 = 0;
    int e2 = second.size() - 1;
    int last = 0;
    if (i == 0)
        return min(first[b1], second[b2]);
    int from = 0;
    int to = e1 + e2;
    while (b1 <= e1 && b2 <= e2) {
        int _max = max(first[e1], second[e2]);
        int _min = min(first[b1], second[b2]);
        if (_min == _max)
            return _max;
        int m = (_max + _min) / 2;
        auto firstGreater = upper_bound(first.begin() + b1, first.begin() + e1 + 1, m);
        int firstLast = firstGreater - first.begin() - 1;
        auto secondGreater = upper_bound(second.begin() + b2, second.begin() + e2 + 1, m);
        int secondLast = secondGreater - second.begin() - 1;
        last = firstLast + secondLast + 1;
        if (i <= last) {
            e1 = firstLast;
            e2 = secondLast;
            to = last;
        } else {
            b1 = firstLast + 1;
            b2 = secondLast + 1;
            from = b1 + b2;
        }
    }
    if (b1 <= e1) {
        if (b1 == e1)
            return first[b1];
        return first[b1 + i - from];

    }
    if (b2 <= e2) {
        if (b2 == e2)
            return second[b2];
        return second[b2 + i - from];
    }
    return 0;
}


double findMedianSortedArrays(const vector<int> &a, const vector<int> &b) {
    int asize = a.size();
    int bsize = b.size();
    int size = asize + bsize;
    if (!asize && !bsize)
        return 0;
    if (!asize && bsize) {
        if (bsize % 2 == 1)
            return b[bsize / 2];
        else {
            int m = size / 2;
            auto f = b[m];
            auto s = b[m - 1];
            return double(f + s) / 2;
        }
    }

    if (asize && !bsize) {
        if (asize % 2 == 1)
            return a[asize / 2];
        else {
            int m = size / 2;
            auto f = a[m];
            auto s = a[m - 1];
            return double(f + s) / 2;
        }
    }

    if (size % 2 == 1)
        return ithOfTwoSorted(size / 2, a, b);
    else {
        int m = size / 2;
        auto f = ithOfTwoSorted(m, a, b);
        auto s = ithOfTwoSorted(m - 1, a, b);
        return double(f + s) / 2;
    }
}

int main() {
//    vector<int> first = {1, 2};
//    vector<int> second = {3, 4};
//    cout<<findMedianSortedArrays(first, second);
//    // cout<<ithOfTwoSorted(1, first, second)<<endl;
////    for(int i = 0; i < 4; ++i){
////        cout<<ithOfTwoSorted(i, first, second)<<endl;
////    }
    vector<int> first = {1, 1};
    vector<int> second = {1, 1};
    cout << ithOfTwoSorted(1, first, second) << endl;
//    for(int i = 0; i < 4; ++i){
//        cout<<ithOfTwoSorted(i, first, second)<<endl;
//    }

    return 0;
}
