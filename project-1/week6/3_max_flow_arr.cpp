#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

bool bfs(int** rGraph, int s, int t, int parent[], int n) {
    bool visited[n];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

int fordFulkerson(int** graph, int s, int t, int n) {
    int** rGraph = new int*[n];
    for (int i = 0; i < n; ++i) {
        rGraph[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            rGraph[i][j] = graph[i][j];
        }
    }

    int* parent = new int[n];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent, n)) {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    for (int i = 0; i < n; ++i) {
        delete[] rGraph[i];
    }
    delete[] rGraph;
    delete[] parent;

    return max_flow;
}

int main() {
    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;

    int** rg = new int*[n];
    for (int i = 0; i < n; ++i) {
        rg[i] = new int[n];
        memset(rg[i], -1, n * sizeof(int));
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        rg[u][v] = w;
    }

    cout << fordFulkerson(rg, s, t, n);

    for (int i = 0; i < n; ++i) {
        delete[] rg[i];
    }
    delete[] rg;

    return 0;
}