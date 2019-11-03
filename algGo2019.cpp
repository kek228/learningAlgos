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

// все перестановки числе от [from, to) размера permutsize
void genPermuts(vector<int> &permut, vector<bool> &used, int from, int to, int permutsize){
    if(permut.size() == permutsize){
        for(auto el: permut)
            cout<<el<<' ';
        cout<<endl;
        return;
    }
    for(int j = from; j < to; ++j){
        if(used[j])
            continue;
        permut.push_back(j);
        used[j] = true;
        genPermuts(permut, used, from, to, permutsize);
        permut.pop_back();
        used[j] = false;
    }
}

int main(){
    int n = 4;
    vector<int> permut;
    vector<bool> used(n, false);
    genPermuts(permut, used, 1, 5, 3);
    return 0;
}
