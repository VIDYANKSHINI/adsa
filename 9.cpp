
#include <iostream>
using namespace std;

int board[20][20], n;

bool safe(int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    for (int i = row-1, j   = col-1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row-1, j = col+1; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

bool solve(int row) {
    if (row == n)
        return true;

    for (int col = 0; col < n; col++) {
        if (safe(row, col)) {
            board[row][col] = 1;

            if (solve(row + 1))
                return true;

            board[row][col] = 0;
        }
    }

    return false;
}

int main() {
    cout << "Enter N: ";
    cin >> n;

    if (n < 1 || n > 20) {
        cout << "Invalid N";
        return 0;
    }

    if (solve(0)) {
        cout << "\nSolution:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }
    else {
        cout << "No solution exists";
    }

    return 0;
}

/*
Input:
4

Output:
Enter N:
Solution:
0 1 0 0
0 0 0 1
1 0 0 0
0 0 1 0
*/

/*
Time Complexity:
Worst case: O(N!)

Space Complexity:
O(N^2) for the board, or O(N) if only the recursion stack and one-dimensional board state are considered
*/
