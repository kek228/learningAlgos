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

vector<int> split(const string &str, char delim = ' ') {
    vector<int> res;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        res.push_back(stoi(token));
    }
    return res;
}


int main() {
    int n;
    cin >> n;
    cin.ignore();
    string input;

    vector<pair<int, int>> tasks;
    while (getline(cin, input) && n > 0) {
        auto parced = split(input);
        tasks.push_back({parced[0], parced[1]});
        --n;
    }
    cout << scheduleTask(tasks);
    return 0;
}