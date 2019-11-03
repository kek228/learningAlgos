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


int main(){
    vector<int> terms;
    allTerms(terms, 5, 0);
    return 0;
}
