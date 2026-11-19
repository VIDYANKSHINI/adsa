
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

int n, cost[10][10];
int bestCost = INT_MAX;
vector<int> bestPath;

struct Node {
    int city, level, total;
    int visited;
    vector<int> path;

    bool operator>(const Node& other) const {
        return total > other.total;
    }
};

void solve() {
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    Node start;
    start.city = 0;
    start.level = 1;
    start.total = 0;
    start.visited = 1;
    start.path.push_back(0);

    pq.push(start);

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.total >= bestCost)
            continue;

        if (cur.level == n) {
            if (cost[cur.city][0] != 0) {
                int ans = cur.total + cost[cur.city][0];

                if (ans < bestCost) {
                    bestCost = ans;
                    bestPath = cur.path;
                    bestPath.push_back(0);
                }
            }
            continue;
        }

        for (int i = 0; i < n; i++) {
            if (!(cur.visited & (1 << i)) &&
                cost[cur.city][i] != 0) {

                Node next;
                next.city = i;
                next.level = cur.level + 1;
                next.total = cur.total + cost[cur.city][i];
                next.visited = cur.visited | (1 << i);
                next.path = cur.path;
                next.path.push_back(i);

                if (next.total < bestCost)
                    pq.push(next);
            }
        }
    }
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    if (n < 2 || n > 10) {
        cout << "Invalid number of cities";
        return 0;
    }

    cout << "Enter cost matrix (0 for no edge):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    solve();

    if (bestCost == INT_MAX) {
        cout << "No tour exists";
    }
    else {
        cout << "Minimum cost: " << bestCost << endl;
        cout << "Path: ";

        for (int city : bestPath)
            cout << city << " ";

        cout << endl;
    }

    return 0;
}
