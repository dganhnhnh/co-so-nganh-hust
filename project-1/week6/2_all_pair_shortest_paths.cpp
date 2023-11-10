#include <bits/stdc++.h>
using namespace std;

#define INF 9999

typedef pair<int, int> ip;

class Graph
{
	int V;
	list<pair<int, int>> *adj;

public:
	int **distMatrix;

	Graph(int V)
	{
		this->V = V;
		adj = new list<ip>[V];

		distMatrix = new int *[V];
		for (int i = 0; i <= V; ++i) {
			distMatrix[i] = new int[V];
			for (int j = 0; j <= V; ++j)
			{
				distMatrix[i][j] = INF;
			}
		}
	}
	void addEdge(int u, int v, int w)
	{
		adj[u].push_back(make_pair(v, w));
	}
	void shortestPath(int s);
};

void Graph::shortestPath(int src)
{
	priority_queue<ip, vector<ip>, greater<ip>> pq;

	vector<int> dist(V, INF);

	pq.push(make_pair(1, src));
	dist[src] = 0;

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		list<pair<int, int>>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			int v = (*i).first;
			int weight = (*i).second;

			if (dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
	for (int i = 0; i < V; i++)
	{
		if (dist[i] < distMatrix[src][i])
			distMatrix[src][i] = dist[i];
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	Graph g(n + 1);
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g.addEdge(u, v, w);
	}

	for (int i = 1; i <= n; i++)
	{
		g.shortestPath(i);
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; ++j)
		{
			cout << g.distMatrix[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
