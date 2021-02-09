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

void find_components(const int start, const vector<vector<int>> &graph, vector<int> &which_comp,
                     unordered_map<int, unordered_set<int>> &components) {
    queue<int> q;
    q.push(start);
    unordered_set<int> newComp;
    newComp.insert(start);
    const int compC = components.size();
    while (q.size()) {
        const int cur = q.front();
        q.pop();
        which_comp[cur] = compC;
        newComp.insert(cur);
        for (const int conn: graph[cur]) {
            if (which_comp[conn] != compC && which_comp[conn] != -1) {
                if (which_comp[conn] != -1) {
                    auto comp = components.find(which_comp[conn]);
                    for (const int v: comp->second) {
                        which_comp[v] = compC;
                        newComp.insert(v);
                    }
                    components.erase(comp);
                }
            } else if (which_comp[conn] == -1) {
                q.push(conn);
            }
        }
    }
    components[compC] = newComp;
}

bool cycles(const int cur, const vector<vector<int>> &graph, vector<int> &which_comp) {
    which_comp[cur] = 0;
    for (int i = 0; i < graph[cur].size(); ++i) {
        const int next = graph[cur][i];
        if (which_comp[next] == 0)
            return true;
        if (which_comp[next] == 2)
            continue;
        if (cycles(next, graph, which_comp))
            return true;
    }
    which_comp[cur] = 1;
    return false;
}

bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    if (numCourses < 2 || prerequisites.empty())
        return true;
    unordered_map<int, unordered_set<int>> components;
    vector<vector<int>> graph(numCourses, vector<int>());
    //
    for (auto &p : prerequisites)
        graph[p[1]].push_back(p[0]);
    //
    vector<int> which_comp(numCourses, -1);
    for (int i = 0; i < numCourses; ++i) {
        if (which_comp[i] == -1)
            find_components(i, graph, which_comp, components);
    }
    if (components.size() != 1)
        return false;
    which_comp = vector<int>(numCourses, -1);
    return !cycles(0, graph, which_comp);
}


int main() {
    // [[1,4],[2,4],[3,1],[3,2]]

    // vector<vector<int>> prerequisites = {{1,4},{2,4},{3,1},{3,2}};
    vector<vector<int>> prerequisites = {{1, 0},
                                         {0, 1}};
    cout << canFinish(2, prerequisites);
    return 0;
}
