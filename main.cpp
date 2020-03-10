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

//class Solution {
//    const vector<vector<int>> graph = {
//            {1, 3, 4},
//            {0, 2, 3, 4, 5},
//            {1, 4, 5},
//            {0, 1, 4, 6, 7},
//            {0, 1, 2, 3, 5, 6, 7, 8},
//            {1, 2, 4, 7, 8},
//            {3, 4, 7},
//            {3, 4, 5, 6, 8},
//            {4, 5, 7}
//    };
//
//    int res = 0;
//public:
//    void _numberOfPatterns(unordered_set<int> &used, const int m, const int n){
//        if(used.size() == 9 && n ==9){
//            ++res;
//            return;
//        }
//        if(used.size() > n)
//            return;
//        if(used.size() >= m)
//            ++res;
//        for(int usedV: used){
//            // список смежности iй вершины в used
//            for(int v: graph[usedV]){
//                auto check = used.find(v);
//                if(check != used.end())
//                    continue;
//                used.insert(v);
//                _numberOfPatterns(used, m, n);
//                used.erase(v);
//            }
//        }
//    }
//
//    int numberOfPatterns(int m, int n) {
//        unordered_set<int> used;
//        for(int i = 0; i < 9; ++i){
//            used.insert(i);
//            _numberOfPatterns(used, m, n);
//            used.erase(i);
//        }
//        return res;
//    }
//};

string smallestSubsequence(string text) {
    if (text.empty())
        return "";
    string res;
    unordered_map<char, int> frequencies;
    for (const char c: text)
        ++frequencies[c];
    unordered_set<char> inRes;
    //
    res.push_back(text[0]);
    inRes.insert(text[0]);
    --frequencies[text[0]];
    if (frequencies[text[0]] == 0)
        frequencies.erase(text[0]);
    for (int i = 1; i < text.size(); ++i) {
        const char c = text[i];
        // if it's not in solution
        if (inRes.find(c) == inRes.end()) {
            // this is not the last c character
            while (!res.empty() && res.back() > c) {
                const char last = res.back();
                // no more last characters
                if (frequencies.find(last) == frequencies.end())
                    break;
                else {
                    inRes.erase(res.back());
                    res.pop_back();
                }
            }
            res.push_back(c);
            inRes.insert(c);
        }
        --frequencies[c];
        if (frequencies[c] == 0)
            frequencies.erase(c);
    }
    return res;
}

int main() {
    cout << smallestSubsequence("bdaccdbddc"); // "adbc"
    return 0;
}
