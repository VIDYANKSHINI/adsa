
#include <iostream>
using namespace std;

#define INF 99999

int main() {
    int n, a[10][10];

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter cost matrix (99999 for INF):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][k] != INF && a[k][j] != INF &&
                    a[i][k] + a[k][j] < a[i][j]) {
                    a[i][j] = a[i][k] + a[k][j];
                }
            }
        }
    }

    cout << "\nShortest distance matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == INF)
                cout << "INF ";
            else
                cout << a[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
Input:
4
0 5 99999 10
99999 0 3 99999
99999 99999 0 1
99999 99999 99999 0

Output:
Enter number of vertices: Enter cost matrix (99999 for INF):
Shortest distance matrix:
0 5 8 9
INF 0 3 4
INF INF 0 1
INF INF INF 0
*/

/*
Time Complexity:
O(V^3), where V is the number of vertices

Space Complexity:
O(V^2) for the distance matrix
*/
