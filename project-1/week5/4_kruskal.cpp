#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    Edge(int uu, int vv, int w) : u(uu), v(vv), weight(w) {}
};

struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int kruskalMST(int N, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdges);
    DisjointSet ds(N);
    int minimumSpanningTreeWeight = 0;
    
    for (const Edge& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;

        if (ds.find(u) != ds.find(v)) {
            ds.unionSets(u, v);
            minimumSpanningTreeWeight += weight;
        }
    }

    return minimumSpanningTreeWeight;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges;
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v, w));
    }

    int result = kruskalMST(N, edges);
    cout << result << endl;

    return 0;
}
