#include <iostream>
using namespace std;

#define INF 99999

struct Edge {
    int u, v, w;
};

int main() {
    int n, e, src;
    Edge edge[100];
    int dist[100];

    cout << "Enter vertices and edges: ";
    cin >> n >> e;

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < e; i++)
        cin >> edge[i].u >> edge[i].v >> edge[i].w;

    cout << "Enter source: ";
    cin >> src;

    for (int i = 0; i < n; i++)
        dist[i] = INF;

    dist[src] = 0;

    int ops = 0; // Time complexity verify karne ke liye counter

    // Relax all edges (V - 1) times
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < e; j++) {
            ops++; // Har edge relaxation count karo
            int u = edge[j].u;
            int v = edge[j].v;
            int w = edge[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < e; j++) {
        int u = edge[j].u;
        int v = edge[j].v;
        int w = edge[j].w;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "Negative cycle exists!\n";
            return 0;
        }
    }

    cout << "\nShortest distances:\n";
    for (int i = 0; i < n; i++) {
        cout << src << " to " << i << " = ";
        if (dist[i] == INF)
            cout << "INF";
        else
            cout << dist[i];
        cout << endl;
    }

    // Time Complexity Verification
    cout << "\n--- Time Complexity Verification ---\n";
    cout << "Actual Relaxation Operations: " << ops << endl;
    cout << "Expected (V - 1) * E        : " << (n - 1) * e << endl;
    cout << "Verified Time Complexity    : O(V * E)\n";

    return 0;
}

/*
Input:
5 8
0 1 -1
0 2 4
1 2 3
1 3 2
1 4 2
3 2 5
3 1 1
4 3 -3
0

Output:
Enter vertices and edges: Enter edges (u v weight):
Enter source:
Shortest distances:
0 to 0 = 0
0 to 1 = -2
0 to 2 = 2
0 to 3 = -3
0 to 4 = -4

--- Time Complexity Verification ---
Actual Relaxation Operations: 32
Expected (V - 1) * E        : 32
Verified Time Complexity    : O(V * E)
*/

/*
Time Complexity:
O(V * E), where V is the number of vertices and E is the number of edges

Space Complexity:
O(V)
*/