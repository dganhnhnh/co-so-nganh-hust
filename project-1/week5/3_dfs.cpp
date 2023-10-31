#include <bits/stdc++.h>
#include <vector>
#include <queue>
using namespace std;


void DFS(vector<vector<int>> graph, int start){

    stack<int> s;
    int nodesCount = graph.size()-1;
    vector<bool> visited(nodesCount, false);
    vector<bool> closed(nodesCount, false);
    int nodesVisited=0;

    s.push(start);
    visited[start] = true;
    nodesVisited=1;

    while (!s.empty() || nodesVisited < nodesCount) {
        int curr = s.top();
        s.pop();
        if (!closed[curr]) cout << curr << " ";
        closed[curr] = true;
        
        for (int i = 0; i < graph[curr].size(); i++) {
        // for (int i = graph[curr].size()-1; i >= 0; i--) {
            int adj = graph[curr][i];
            if (!closed[adj]) {
                s.push(adj);
                // cout<< "adj: "<< adj << endl;
                visited[adj] = true;
                nodesVisited++;
            }
        }
        if (s.empty() && nodesVisited < nodesCount) {
            for (int i = 1; i < nodesCount; i++) {
                if (!visited[i]) {
                    s.push(i);
                    visited[i] = true;
                    nodesVisited++;
                    break;
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1); 

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u); 
    }

    int startNode = 1;

    for (int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end(), greater<int>());
    }

    DFS(graph, startNode);

    return 0;
}