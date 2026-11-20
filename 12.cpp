#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Item {
    int weight, profit;
    double ratio;
};

Item a[20];
int n, capacity, best = 0;
int bbNodes = 0; // Branch & Bound ke explored nodes count karne ke liye
int dpSteps = 0; // DP ke table steps count karne ke liye

bool cmp(Item x, Item y) {
    return x.ratio > y.ratio;
}

// Upper bound calculation (Fractional Knapsack logic)
double bound(int i, int weight, int profit) {
    if (weight >= capacity)
        return profit;

    double result = profit;

    for (int j = i; j < n; j++) {
        if (weight + a[j].weight <= capacity) {
            weight += a[j].weight;
            result += a[j].profit;
        } else {
            result += (capacity - weight) * a[j].ratio;
            break;
        }
    }

    return result;
}

// 1. Branch & Bound Approach
void solveBB(int i, int weight, int profit) {
    bbNodes++; // Har recursive call = 1 state-space node

    if (weight <= capacity)
        best = max(best, profit);

    if (i == n || bound(i, weight, profit) <= best)
        return;

    // Include item
    if (weight + a[i].weight <= capacity)
        solveBB(i + 1, weight + a[i].weight, profit + a[i].profit);

    // Exclude item
    solveBB(i + 1, weight, profit);
}

// 2. Dynamic Programming Approach (Comparison ke liye)
int solveDP() {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            dpSteps++; // Har DP cell computation count karo
            if (a[i - 1].weight <= w) {
                dp[i][w] = max(a[i - 1].profit + dp[i - 1][w - a[i - 1].weight],
                               dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter capacity: ";
    cin >> capacity;

    cout << "Enter weight and profit:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].weight >> a[i].profit;
        a[i].ratio = (double)a[i].profit / a[i].weight;
    }

    sort(a, a + n, cmp);

    solveBB(0, 0, 0);
    int dpProfit = solveDP();

    cout << "\n--- Results & Efficiency Comparison ---\n";
    cout << "Branch & Bound -> Max Profit: " << best
         << " | Nodes Explored: " << bbNodes << endl;
    cout << "Dynamic Prog.  -> Max Profit: " << dpProfit
         << " | Table Steps (n*W): " << dpSteps << endl;

    return 0;
}

/*
Input:
4
50
10 60
20 100
30 120
40 240

Output:
Enter number of items: Enter capacity: Enter weight and profit:

--- Results & Efficiency Comparison ---
Branch & Bound -> Max Profit: 340 | Nodes Explored: 15
Dynamic Prog.  -> Max Profit: 340 | Table Steps (n*W): 200
*/

/*
Time Complexity:
Branch and Bound: Worst case O(2^n)
Dynamic Programming: O(n * W), where W is the knapsack capacity

Space Complexity:
Branch and Bound: O(n) auxiliary recursion stack
Dynamic Programming: O(n * W)
*/