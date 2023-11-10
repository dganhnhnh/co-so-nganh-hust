#include <bits/stdc++.h>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

void BFS(){

}

int fordFulkerson()
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

    // CTDL phù hợp để lưu đồ thị, chạy BFS và cộng trừ path flow 
    int rg[n+1][n+1];
    int u, v, w;
    // set all elements in residual graph to -1
    memset(rg, -1, sizeof(rg));
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        rg[u][v] = w;
    }
    // print residual graph
    for (int i = 1; i <= n; i++)
    {
        rg[i][i] = 0;
        for (int j = 1; j <= n; j++)
        {
            cout << rg[i][j] << " ";
        }
        cout << endl;
    }

}