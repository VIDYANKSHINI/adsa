
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n = 5;

    // Adjacency List
    vector<int> adj[5];

    // Adjacency Matrix
    int mat[5][5] = {0};

    // Edges
    int edges[][2] = {
        {0,1}, {0,2}, {1,3}, {2,3}, {3,4}
    };
    int e = 5;

    for(int i = 0; i < e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);

        mat[u][v] = 1;
        mat[v][u] = 1;
    }

    // Display Adjacency Matrix
    cout << "Adjacency Matrix:\n";

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    // BFS
    cout << "\nBFS: ";

    bool visited[5] = {false};
    queue<int> q;

    q.push(0);
    visited[0] = true;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for(int x : adj[node]) {
            if(!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }

    // DFS (Iterative)
    cout << "\nDFS: ";

    bool vis[5] = {false};
    vector<int> st;

    st.push_back(0);

    while(!st.empty()) {
        int node = st.back();
        st.pop_back();

        if(!vis[node]) {
            cout << node << " ";
            vis[node] = true;

            for(int x : adj[node]) {
                if(!vis[x])
                    st.push_back(x);
            }
        }
    }

    return 0;
}

/*
Input:
No input

Output:
Adjacency Matrix:
0 1 1 0 0
1 0 0 1 0
1 0 0 1 0
0 1 1 0 1
0 0 0 1 0

BFS: 0 1 2 3 4
DFS: 0 2 3 4 1
*/

/*
Time Complexity:
BFS: O(V + E)
DFS: O(V + E)

Space Complexity:
BFS/DFS: O(V + E) for adjacency list, including O(V) for visited and auxiliary structures
Adjacency matrix: O(V^2)
*/
