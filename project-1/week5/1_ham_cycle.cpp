#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<vector<int>> graph;
int N;  

bool isHamiltonianCycle(int v, int start, vector<bool>& visited, int visitedCount) {
    visited[v] = true;
    visitedCount++;

    if (visitedCount == N) {
        if (graph[v][start])
            return true;
    }

    for (int u = 0; u < N; u++) {
        if (graph[v][u] && !visited[u]) {
            if (isHamiltonianCycle(u, start, visited, visitedCount))
                return true;
        }
    }

    visited[v] = false; 
    return false;
}

bool isHamiltonianPath(int v, vector<bool>& visited, int visitedCount) {
    visited[v] = true;
    visitedCount++;

    if (visitedCount == N) {
        return true;
    }

    for (int u = 0; u < N; u++) {
        if (graph[v][u] && !visited[u]) {
            if (isHamiltonianPath(u, visited, visitedCount))
                return true;
        }
    }

    visited[v] = false; 
    return false;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int m;
        cin >> N >> m;
        graph = vector<vector<int>>(N, vector<int>(N, 0));

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            graph[u][v] = 1;
            graph[v][u] = 1;
        }

        vector<bool> visited(N, false);
        bool isHamiltonian = false;

        for (int i = 0; i < N; i++) {
            if (isHamiltonianCycle(i, i, visited, 1) || isHamiltonianPath(i, visited, 1)) {
                isHamiltonian = true;
                break;
            }
            visited.assign(N, false); 
        }

        if (isHamiltonian)
            cout << "1" << endl;
        else
            cout << "0" << endl;
    }

    return 0;
}
