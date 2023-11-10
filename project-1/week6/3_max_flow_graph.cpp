#include <bits/stdc++.h>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

typedef pair<int, int> ip;

class Graph
{
	int V;
	list<ip> *adj;
    // dynamically allocate everytime run BFS
    int *path_flow;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new list<ip>[V];
    }
    void addEdge(int u, int v, int w)
	{
		adj[u].push_back(make_pair(v, w));
	}
    void BFS(int s);
    int fordFulkerson(int s, int t);
};

void Graph::BFS(int start){
    queue<int> q;
    int nodesCount = V-1;
    vector<bool> visited(nodesCount, false);
    int nodesVisited=0;

    q.push(start);
    visited[start] = true;
    nodesVisited=1;
}
void bfs(vector<vector<pair<int, int>>>& graph, int source, int destination) {
    int V = graph.size();
    vector<bool> visited(V, false);
    queue<int> q; 
    unordered_map<int, int> parentMap;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (const auto& neighbor : graph[current]) {
            int nextVertex = neighbor.first;
            int weight = neighbor.second;

            if (!visited[nextVertex]) {
                q.push(nextVertex);
                visited[nextVertex] = true;
                parentMap[nextVertex] = current; // Store the parent of the neighbor
            }
        }
    }

    if (visited[destination]) {
        // Path exists, print it
        // printPath(parentMap, source, destination);
    } else {
        cout << "Path does not exist." << endl;
    }
}

int Graph::fordFulkerson(int s, int t)
{
    // find path from src to dest with BFS
    // while path exists
    //     find min flow in path
    //     update residual graph

    return 0;
}

int main(){
    int n, m;
	cin >> n >> m;
    int s,t;
    cin >> s >> t;

    Graph g(n + 1);
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g.addEdge(u, v, w);
	}

}