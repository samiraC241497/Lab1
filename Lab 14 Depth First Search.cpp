#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;

    int graph[100][100] = {0};

    cout << "Enter edges (u v):\n";
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    bool visited[100] = {false};

    cout << "DFS traversal: ";
    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        cout << node << " ";

        for(int i = 0; i < n; i++) {
            if(graph[node][i] == 1 && !visited[i]) {
                dfs(i);
            }
        }
    };

    dfs(start);

    return 0;
}

