
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

int n, cost[10][10], best = INT_MAX;
vector<int> ans;

struct Node {
    int city, level, total, visited;
    vector<int> path;

    bool operator>(const Node& x) const {
        return total > x.total;
    }
};

void solve() {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, 1, 0, 1, {0}});

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.total >= best) continue;

        if (cur.level == n) {
            if (cost[cur.city][0] != 0) {
                int t = cur.total + cost[cur.city][0];

                if (t < best) {
                    best = t;
                    ans = cur.path;
                    ans.push_back(0);
                }
            }
            continue;
        }

        for (int i = 0; i < n; i++) {
            if (!(cur.visited & (1 << i)) && cost[cur.city][i] != 0) {
                Node next = cur;
                next.city = i;
                next.level++;
                next.total += cost[cur.city][i];
                next.visited |= (1 << i);
                next.path.push_back(i);

                if (next.total < best)
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

    if (best == INT_MAX)
        cout << "No tour exists";
    else {
        cout << "Minimum cost: " << best << endl;
        cout << "Path: ";
        for (int x : ans)
            cout << x << " ";
    }

    return 0;
}

/*
Input:
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

Output:
Enter number of cities: Enter cost matrix (0 for no edge):
Minimum cost: 80
Path: 0 1 3 2 0
*/
