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
using namespace std;

vector<int> split(const string& str, char delim = ' '){
    vector<int> res;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        res.push_back(stoi(token));
    }
    return res;
}

int counter = 0;

void chipPlacing(vector<char> &chips, int n, int m, int last, int placed){
    if(placed == m){
        for(auto c: chips){
            cout<<c;
        }
        cout<<endl;
        return;
    }
    for(int i = last + 2; i < n; ++i){
        chips[i] = '*';
        chipPlacing(chips, n, m, i, placed + 1);
        chips[i] = '.';
    }
}

int main(){
    int n = 25;
    int m = 8;
    vector<char> chips(n, '.');
    chipPlacing(chips, n, m, -2, 0);
    return 0;
}
// 3 1 4 2 2 4
// 7 2 3 1 5 6 4
// 1 3 3
// 2 3 3 4 4 6 13
// .*.*.*.
// .*.*.....*.*.*.*....*..*.