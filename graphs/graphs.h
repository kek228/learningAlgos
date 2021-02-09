#pragma once

using namespace std;
using Labyrinth = std::vector <std::vector<int>>;

vector <vector<int>> constructTable(int rows, int cols) {
    vector <vector<int>> table(rows);
    for (auto &row: table)
        row = vector<int>(cols, 0);
    return table;
}

struct Cell {
    Cell() = default;

    Cell(const Cell &right) = default;

    Cell(int _row, int _column) : row(_row), column(_column) {}

    bool operator==(const Cell &right) {
        return row == right.row && column == right.column;
    }

    int row;
    int column;
};

bool operator==(const Cell &left, const Cell &right) {
    return left.row == right.row && left.column == right.column;
}


std::optional <Cell> top(const Labyrinth &world, vector <vector<int>> &marker, const Cell &cur) {
    auto targetRow = cur.row - 1;
    if (targetRow < 0)
        return std::nullopt;
    if (world[targetRow][cur.column] == 1 && marker[targetRow][cur.column] == 0)
        return {{targetRow, cur.column}};
    else
        return std::nullopt;
}

std::optional <Cell> right(const Labyrinth &world, vector <vector<int>> &marker, const Cell &cur) {
    auto targetColumn = cur.column + 1;
    if (targetColumn == world[0].size())
        return std::nullopt;
    if (world[cur.row][targetColumn] == 1 && marker[cur.row][targetColumn] == 0)
        return {{cur.row, targetColumn}};
    else
        return std::nullopt;
}

std::optional <Cell> bottom(const Labyrinth &world, vector <vector<int>> &marker, const Cell &cur) {
    auto targetRow = cur.row + 1;
    if (targetRow == world.size())
        return std::nullopt;
    if (world[targetRow][cur.column] == 1 && marker[targetRow][cur.column] == 0)
        return {{targetRow, cur.column}};
    else
        return std::nullopt;
}

std::optional <Cell> left(const Labyrinth &world, vector <vector<int>> &marker, const Cell &cur) {
    auto targetColumn = cur.column - 1;
    if (targetColumn < 0)
        return std::nullopt;
    if (world[cur.row][targetColumn] == 1 && marker[cur.row][targetColumn] == 0)
        return {{cur.row, targetColumn}};
    else
        return std::nullopt;
}

void
checkAndSet(Labyrinth &marker, std::queue <Cell> &cellsToVisit, vector <Cell> &component, std::optional <Cell> &cell,
            int label) {
    if (cell) {
        component.push_back(*cell);
        cellsToVisit.push(*cell);
        marker[(*cell).row][(*cell).column] = label;
    }
}

vector <Cell> findComponent(Cell start, vector <vector<int>> &world, vector <vector<int>> &marker, int label) {
    vector <Cell> res;
    queue <Cell> cellsToVisit;
    cellsToVisit.push(start);
    res.push_back(start);
    marker[start.row][start.column] = label;
    while (!cellsToVisit.empty()) {
        auto curCell = cellsToVisit.front();
        cellsToVisit.pop();
        auto topCell = top(world, marker, curCell);
        checkAndSet(marker, cellsToVisit, res, topCell, label);
        //
        auto rightCell = right(world, marker, curCell);
        checkAndSet(marker, cellsToVisit, res, rightCell, label);
        //
        auto bottomCell = bottom(world, marker, curCell);
        checkAndSet(marker, cellsToVisit, res, bottomCell, label);
        //
        auto leftCell = left(world, marker, curCell);
        checkAndSet(marker, cellsToVisit, res, leftCell, label);
    }
    return res;
}

int shortestBridgeRoutine(const vector <Cell> &v1, const vector <Cell> &v2) {
    int res = numeric_limits<int>::max();
    for (const auto &cell1: v1) {
        for (const auto &cell2: v2) {
            int dst = abs(cell1.row - cell2.row) + abs(cell1.column - cell2.column) - 1;
            if (dst < res)
                res = dst;
        }
    }
    return res;
}

// https://leetcode.com/problems/shortest-bridge
int shortestBridge(vector <vector<int>> &A) {
    int rows = A.size();
    int cols = A[0].size();
    vector <vector<int>> marker = constructTable(rows, cols);
    vector <vector<Cell>> components;
    int label = 1;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (A[row][col] == 1 && marker[row][col] == 0) {
                auto component = findComponent({row, col}, A, marker, label);
                ++label;
                components.push_back(component);
            }
        }
    }
    return shortestBridgeRoutine(components[0], components[1]);
}


// https://leetcode.com/problems/network-delay-time/
// Дейкстра
struct Conn {
    int id;
    int w;
};

int networkDelayTime(vector <vector<int>> &times, int N, int K) {
    const int size = times.size();
    if (size == 0)
        return 0;
    vector <vector<Conn>> connections(N);
    for (const auto &t: times) {
        connections[t[0] - 1].push_back({t[1] - 1, t[2]});
    }
    //
    const auto inf = numeric_limits<int>::max();
    --K;
    vector<int> results(N, inf);
    results[K] = 0;
    vector<bool> visited(N, false);
    priority_queue < pair < int, int >, vector < pair < int, int >>, greater < pair < int, int >> > q; //res to v
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

void find_components(const int start, const vector <vector<int>> &graph, vector<int> &which_comp,
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

// finding cycles and connected components
bool cycles(const int cur, const vector <vector<int>> &graph, vector<int> &which_comp) {
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

void find_components(const int start, const vector <vector<int>> &graph, vector<int> &which_comp,
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

bool canFinish(int numCourses, vector <vector<int>> &prerequisites) {
    if (numCourses < 2 || prerequisites.empty())
        return true;
    unordered_map<int, unordered_set<int>> components;
    vector <vector<int>> graph(numCourses, vector<int>());
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