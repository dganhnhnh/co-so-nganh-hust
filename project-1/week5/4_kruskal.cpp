#include <bits/stdc++.h>
using namespace std;

class DSU
{
    int *p;
    int *r;

public:
    DSU(int V)
    {
        p = new int[V];
        r = new int[V];

        for (int i = 0; i < V; i++)
        {
            p[i] = -1;
            r[i] = 1;
        }
    }

    int find(int i)
    {
        if (p[i] == -1) return i;
        return p[i] = find(p[i]);
    }

    void unite(int u, int v)
    {
        int p_u = find(u);
        int p_v = find(v);

        if (p_u != p_v)
        {
            if (r[p_u] < r[p_v])        p[p_u] = p_v;
            else if (r[p_u] > r[p_v])   p[p_v] = p_u;
            else
            {
                p[p_v] = p_u;
                r[p_u] += 1;
            }
        }
    }
};

class Graph
{
    vector<vector<int>> edges;
    int V;

public:
    Graph(int V) { this->V = V; }

    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, u, v});
    }

    void mst()
    {
        sort(edges.begin(), edges.end());

        DSU s(V);
        int ans = 0;
        for (auto edge : edges)
        {
            int w = edge[0];
            int u = edge[1];
            int v = edge[2];

            if (s.find(u) != s.find(v))
            {
                s.unite(u, v);
                ans += w;
            }
        }
        cout << ans;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    g.mst();

    return 0;
}