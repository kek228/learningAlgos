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


int main() {
    // vector<int> jobDifficulty = {11, 111, 22, 222, 33, 333, 44, 444};
    vector<int> jobDifficulty = {6, 5, 4, 3, 2, 1};
    cout << minDifficulty(jobDifficulty, 2);
    return 0;
}
