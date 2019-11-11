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

struct Task {
    Task(int deadline, int price) : _deadline(deadline), _price(price) {}

    int _deadline;
    int _price;
};

size_t scheduleTask(vector<Task> &tasks) {
    vector<bool> usedDates(tasks.size(), false);
    size_t res = 0;
    sort(tasks.begin(), tasks.end(), [](Task &l, Task &r) { return l._price > r._price; });
    for (auto &t: tasks) {
        int index = t._deadline - 1;
        while (index >= 0 && usedDates[index]) {
            --index;
        }
        if (index >= 0) {
            usedDates[index] = true;
            res += t._price;
        }
    }
    return res;
}


int main() {
    vector<Task> tasks;
    std::ifstream infile("/Users/nikita/CLionProjects/ALGOS/test.txt");
    string input;
    getline(infile, input);
    int n = stoi(input);
    while (n > 0) {
        getline(infile, input);
        vector<int> oneApp = split(input);
        tasks.emplace_back(oneApp[0], oneApp[1]);
        --n;
    }
    cout << scheduleTask(tasks);
    return 0;
}

// Ответы
// 4
// n^2
//
//
// 4
// 372
// 4
// 1021