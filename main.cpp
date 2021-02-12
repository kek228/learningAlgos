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
#include <thread>

using namespace std;

class Solution {
public:
    vector<bool> visited;
    vector<int> lowestReachable;
    vector<int> times;
    vector<vector<int>> res;
    int curTime = 0;

    void exploreConnections(const vector<vector<int>> &graph, const int v, const int p) {
        times[v] = curTime;
        ++curTime;
        visited[v] = true;
        for (const auto w: graph[v]) {
            if (!visited[w]) {
                exploreConnections(graph, w, v);
                // был ли заход через след вершину в вершину ДО текущей
                lowestReachable[v] = min(lowestReachable[v], lowestReachable[w]);
                if (lowestReachable[w] > times[v]) // случай когда такого захода не было
                    res.push_back({v, w});
            } else if (visited[w] && w != p) // уперлись в серую ( случай петли)
                lowestReachable[v] = min(lowestReachable[v], times[w]);
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections) {
        visited = vector<bool>(n, false);
        times = vector<int>(n, 0);
        lowestReachable = vector<int>(n, n + 1);

        vector<vector<int>> graph(n, vector<int>());
        for (auto &conn: connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                exploreConnections(graph, i, -1);
        }
        return res;
    }
};

int main() {
    Solution s;
    // [[0,1],[1,2],[2,0],[1,3]]
    vector<vector<int>> connections{{0, 1},
                                    {1, 2},
                                    {2, 0},
                                    {1, 3}};
    auto res = s.criticalConnections(connections.size(), connections);

    return 0;
}
