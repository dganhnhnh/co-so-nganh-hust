#include <bits/stdc++.h>
#include <vector>
#include <queue>
using namespace std;

void BFS(vector<vector<int>> graph, int start){
    queue<int> q;
    int nodesCount = graph.size()-1;
    vector<bool> visited(nodesCount, false);
    int nodesVisited=0;

    q.push(start);
    visited[start] = true;
    nodesVisited=1;

    while (!q.empty() || nodesVisited < nodesCount) {
        int curr = q.front();
        q.pop();
        cout <<  curr << " ";
        // cout << endl<< "loop "<< nodesVisited <<" "<<q.empty() << endl;
        // cout << "current: "<< curr << endl;
        for (int i = 0; i < graph[curr].size(); i++) {
            int adj = graph[curr][i];
            if (!visited[adj]) {
                q.push(adj);
                visited[adj] = true;
                nodesVisited++;
            }
        }
        if (q.empty() && nodesVisited < nodesCount) {
            // cout << "queue empty" << endl;
            for (int i = 1; i < visited.size(); i++) {
                if (!visited[i]) {
                    q.push(i);
                    // cout << "multipart "<< i << " ";
                    visited[i] = true;
                    nodesVisited++;
                    break;
                }
            }
        }
        // // print queue
        // queue<int> copyQueue = q;
        // while (!copyQueue.empty())
        // {
        //     cout << copyQueue.front() << " ";
        //     copyQueue.pop();
        // }
        // cout << endl;
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1); // Adding 1 to the size for 1-based indexing

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u); 
    }

    int startNode = 1;

    // sort adjacency list for each node
    for (int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end());
    }

    //     // print adjacency list of node i
    // for (int i = 1; i <= n; i++) {
    //     cout << i << ": ";
    //     for (int j = 0; j < graph[i].size(); j++) {
    //         cout << graph[i][j] << " ";
    //     }
    //     cout<< endl;
    // }
    BFS(graph, startNode);

    return 0;
}