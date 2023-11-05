#include <bits/stdc++.h>
#include <vector>
using namespace std;

vector<vector<int>> graph;
int n, m; int res = -1;
// dynamic allocate for x, visited
int *x; bool *visited;

void print_arr(int x[], int n){
    cout << "x: ";
    for (int i=1; i<=n+1; i++){
        cout << x[i] << " "  ;
    }
    cout << endl;
}

void TRY(int k, int n){

    for (int i = 0; i < graph[x[k]].size(); i++) {
        // cout << "k: " << k << endl;
        // cout << "x[k]: " << x[k] << endl;

        int temp = graph[x[k]][i];
        // cout << temp << " " << visited[temp] << endl ;
        if (k == n && temp == x[1]) {
            x[k+1] = temp;
            // print_arr(x,n );
            res = 1;
            break;
        }
        if (!visited[temp]) {
            x[k+1] = temp;
            
            visited[temp] = true;
            // print_arr(x,n );
            TRY(k+1,n);
            // undo choice
            visited[temp] = false;
            x[k+1] = -1;
        }
    }
    if (res == 1) return;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        cin >> n >> m;
        x = new int[n+2];
        visited = new bool[n+1];
        memset(x, -1, sizeof(x[0]) * (n+2));

        for (int i = 0; i <= n; i++) {
            graph.push_back(vector<int>());
        }

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;

            graph[u].push_back(v);
            graph[v].push_back(u); 
        }

        for (int i = 1; i <= n; i++) {
            x[1] = i; visited[i] = true;
            TRY(1, n);
            if (res == 1) break;
            // visited all false
            memset(visited, false, sizeof(visited[0]) * (n+1));
        }
        if (res == 1) cout << "1"<<endl;
        else cout << "0"<<endl;
    }
    return 0;
}