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

struct Conn {
    int id;
    int w;
};

int networkDelayTime(vector<vector<int>> &times, int N, int K) {
    const int size = times.size();
    if (size == 0)
        return 0;
    vector<vector<Conn>> connections(N);
    for (const auto &t: times) {
        connections[t[0] - 1].push_back({t[1] - 1, t[2]});
    }
    //
    const auto inf = numeric_limits<int>::max();
    --K;
    vector<int> results(N, inf);
    results[K] = 0;
    vector<bool> visited(N, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; //res to v
    q.push({0, K});
    while (!q.empty()) {
        auto curN = q.top();
        const int cur = curN.second;
        const int curRes = curN.first;
        q.pop();
        if (visited[cur])
            continue;
        for (const auto &conn: connections[cur]) {
            const int v = conn.id;
            if (visited[v])
                continue;
            const int posDst = curRes + conn.w;
            results[v] = min(results[v], posDst);
            q.push({results[v], v});
        }
        visited[cur] = true;

    }
    int res = *max_element(results.begin(), results.end());
    if (res == inf)
        return -1;
    return res;
}

int main() {
    return 0;
}