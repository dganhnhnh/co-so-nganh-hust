#include <bits/stdc++.h>
#include <limits.h>
#include <queue>
#include <vector>
using namespace std;

#define INF INT_MAX

int n;
vector<vector<int>> adj;
vector<vector<int>> capacity;

void printParent(const vector<int>& parent) {
    cout << "Parent: ";
    for (int i = 1; i < parent.size(); ++i) {
        cout << parent[i] << " ";
    }
    cout << endl;
}

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        // cout << "q.size(): " << q.size() << endl;
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            // cout << "next: " << next << endl;
            // cout << "capacity "<< "["<<cur<<"]["<<next<<"]: ";
            // cout << capacity[cur][next] << endl;
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    {   
                        // cout<< "new_flow: "<<new_flow<<endl;
                        return new_flow;
                    }
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n+1);
    int new_flow=1;

    while (new_flow = bfs(s, t, parent)) {
        // cout << "new_flow: " << new_flow << endl;
        flow += new_flow;
        // cout << "flow: " << flow << endl;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    // cout << flow << endl;
    return flow;
}

int main(){
    int m;
    cin >> n >> m;
    int s,t;
    cin >> s >> t;

    for (int i = 0; i <= n; ++i) {
        adj.push_back(vector<int>());
    }
    for (int i = 0; i <= n; ++i) {
        capacity.push_back(vector<int>());
        for (int j = 0; j <= n; ++j) {
            capacity[i].push_back(0);
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        capacity[u][v] = w;
    }
    // // print adj
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << ": ";
    //     for (int j = 0; j < adj[i].size(); ++j) {
    //         cout << adj[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // // print capacity 
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << ": ";
    //     for (int j = 1; j <= n; ++j) {
    //         cout << capacity[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout << maxflow(s, t);
    return 0;
}