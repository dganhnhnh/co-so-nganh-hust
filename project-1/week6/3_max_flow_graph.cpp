#include <bits/stdc++.h>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

typedef pair<int, int> ip;
unordered_map<int, int> parentMap;

class Graph
{
	int V;
	list<ip> *adj;
    // dynamically allocate everytime run BFS
    // unordered_map<int, int> parentMap;

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
    int fordFulkerson(int s, int t,unordered_map<int, int>& parentMap);
    bool bfs(int source, int destination, unordered_map<int, int>& parentMap);
};


void printPath(const unordered_map<int, int>& parentMap, int source, int destination) {
    vector<int> path;
    int current = destination;

    // Reconstruct the path from destination to source
    while (current != source) {
        path.push_back(current);
        current = parentMap.at(current);
    }

    // Add the source vertex to the path
    path.push_back(source);

    // Print the path in reverse order
    cout << "Path from " << source << " to " << destination << ": ";
    for (int i = path.size() - 1; i > 0; --i) {
        cout << path[i] << " -> ";
    }
    cout << path[0] << endl;
}

void printParentMap(const unordered_map<int, int>& parentMap) {
    cout << "Parent Map: " << endl;
    for (const auto& pair : parentMap) {
        cout << pair.first << " -> " << pair.second << endl;
    }
}

//  BUG vong lap vo han

bool Graph::bfs(int source, int destination,unordered_map<int, int>& parentMap) {
    vector<bool> visited(V, false);
    queue<int> q; 

    q.push(source);
    visited[source] = true;
    printParentMap(parentMap);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        list<pair<int, int>>::iterator i;
        for (i = adj[current].begin(); i != adj[current].end(); ++i)
        {
            int nextVertex = (*i).first;
            if (!visited[nextVertex]) {
                q.push(nextVertex);
                visited[nextVertex] = true;
                parentMap[nextVertex] = current; 
            }
        }
    }

    printParentMap(parentMap);

    if (visited[destination]) {
        // Path exists, print it
        printPath(parentMap, source, destination);
        return true;
    } else {
        return false;
    }
}

int Graph::fordFulkerson(int s, int t,unordered_map<int, int>& parentMap)
{
    while (bfs(s, t, parentMap))
    {
        int maxFlow = 0;
        // find min flow in path
        int minFlow = INT_MAX;
        // cout<< "iterate "<<endl;
        for (int v = t; v != s; v = parentMap[v])
        {
            int u = parentMap[v];
            for (const auto& neighbor : adj[u]) {
                if (neighbor.first == v) {
                    minFlow = min(minFlow, neighbor.second);
                    break;
                }
            }
        }
        // update residual graph
        for (int v = t; v != s; v = parentMap[v])
        {
            int u = parentMap[v];
            for (auto& neighbor : adj[u]) {
                if (neighbor.first == v) {
                    neighbor.second -= minFlow;
                    break;
                }
            }
            bool found = false;
            for (auto& neighbor : adj[v]) {
                if (neighbor.first == u) {
                    neighbor.second += minFlow;
                    found = true;
                    break;
                }
            }
            if (!found) {
                adj[v].push_back(make_pair(u, minFlow));
            }
        }
        
    }

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

    g.fordFulkerson(s, t, parentMap);

}