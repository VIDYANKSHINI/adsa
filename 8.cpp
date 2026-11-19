
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

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < e; j++) {
            int u = edge[j].u;
            int v = edge[j].v;
            int w = edge[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (int j = 0; j < e; j++) {
        int u = edge[j].u;
        int v = edge[j].v;
        int w = edge[j].w;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "Negative cycle exists!";
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

    return 0;
}
