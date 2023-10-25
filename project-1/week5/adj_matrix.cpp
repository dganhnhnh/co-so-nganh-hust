#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//   global var for adj matrix 

int main() {
    int n, m;
    cin >> n >> m;

    // Create an n x n adjacency matrix initialized with zeros
    int adj[n][n];
    memset(adj, 0, sizeof(adj[0][0]) * n * n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        // Assuming nodes are 0-indexed, mark the edge between u and v
        adj[u-1][v-1] = 1;
        adj[v-1][u-1] = 1; // For an undirected graph, you can add this line
    }

    // Now, the adj contains the graph representation

    // You can print the adjacency matrix for verification
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
