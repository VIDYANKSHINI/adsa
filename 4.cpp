
#include <iostream>
using namespace std;

#define INF 99999

int main() {
    int n, cost[10][10], dist[10], visited[10] = {0};
    int src, minDist, u;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter cost matrix (0 for no edge):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];

            if (i != j && cost[i][j] == 0)
                cost[i][j] = INF;
        }
    }

    cout << "Enter source vertex: ";
    cin >> src;

    for (int i = 0; i < n; i++)
        dist[i] = cost[src][i];

    dist[src] = 0;
    visited[src] = 1;

    for (int count = 1; count < n; count++) {
        minDist = INF;
        u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && cost[u][v] != INF &&
                dist[u] != INF &&
                dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }

    cout << "\nShortest distances from source " << src << ":\n";

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
