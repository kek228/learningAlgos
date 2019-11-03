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

void validParentheses(vector<char> &parentheses, int n,  int open, int close){
    if(parentheses.size() == 2*n){
        ++counter;
        if(counter == 8644)
        {
            for(auto el: parentheses)
                cout<<el<<' ';
            cout<<endl;

        }

        return;
    }
    if(open < n){
        parentheses.push_back('(');
        validParentheses(parentheses, n, open + 1, close);
        parentheses.pop_back();
    }
    if(close < open){
        parentheses.push_back(')');
        validParentheses(parentheses, n, open, close + 1);
        parentheses.pop_back();
    }
}

vector<vector<int>> dsts;
vector<int> path;
vector<int> respath;
vector<bool> used;
int cities;
void salesmanProblem(int curLen, int &res){
    if(curLen >= res)
        return;
    if(path.size() == cities){
        res = curLen + dsts[path.back()][0];// пути в первый город
        respath = path;
        for(auto el: respath)
            cout<<el<<' ';
        cout<<endl;
        return;
    }
    for(int i = 0; i < cities; ++i){
        if(used[i])
            continue;
        auto last = path.back();
        path.push_back(i);
        used[i] = true;
        salesmanProblem(curLen + dsts[last][i], res);
        path.pop_back();
        used[i] = false;
    }
}
int main(){
    string filepath = "/Users/nikita/CLionProjects/ALGOS/test.txt";
    std::ifstream infile(filepath);
    std::string line;
    while (std::getline(infile, line)){
        auto row = split(line);
        dsts.push_back(row);
    }
    path = {0};
    cities = dsts.size();
    used = vector<bool>(cities, false);
    used[0] = true;
    int res = INT_MAX;
    salesmanProblem(0, res);
    cout<<res<<endl;
    return 0;
}
// 4096
// ( ( ) ( ( ) ( ) ) ) ( ) ( ) ( ) ( ( ) )
// 172 0 3 8 7 ...
//