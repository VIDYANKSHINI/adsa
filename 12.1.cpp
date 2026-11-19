#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Item {
    int weight, profit;
    double ratio;
};

Item items[100];
int n, capacity, best = 0;
int bbNodes = 0; // Branch & Bound ke explored nodes count karne ke liye
int dpSteps = 0; // DP ke table steps count karne ke liye

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Upper bound calculation (Fractional Knapsack logic)
double bound(int i, int weight, int profit) {
    if (weight >= capacity)
        return profit;

    double totalProfit = profit;

    for (int j = i; j < n; j++) {
        if (weight + items[j].weight <= capacity) {
            weight += items[j].weight;
            totalProfit += items[j].profit;
        } else {
            totalProfit += (capacity - weight) * items[j].ratio;
            break;
        }
    }

    return totalProfit;
}

// 1. Branch & Bound Approach
void solveBB(int i, int weight, int profit) {
    bbNodes++; // Har recursive call = 1 state-space node

    if (weight <= capacity)
        best = max(best, profit);

    if (i == n || bound(i, weight, profit) <= best)
        return;

    // Include item
    if (weight + items[i].weight <= capacity)
        solveBB(i + 1, weight + items[i].weight, profit + items[i].profit);

    // Exclude item
    solveBB(i + 1, weight, profit);
}

// 2. Dynamic Programming Approach (Comparison ke liye)
int knapsackDP() {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            dpSteps++; // Har DP cell computation count karo
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(items[i - 1].profit + dp[i - 1][w - items[i - 1].weight],
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
        cin >> items[i].weight >> items[i].profit;
        items[i].ratio = (double)items[i].profit / items[i].weight;
    }

    sort(items, items + n, compare);

    solveBB(0, 0, 0);
    int dp = knapsackDP();

    cout << "\n--- Results & Efficiency Comparison ---\n";
    cout << "Branch & Bound -> Max Profit: " << best
         << " | Nodes Explored: " << bbNodes << endl;
    cout << "Dynamic Prog.  -> Max Profit: " << dp
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
Branch & Bound -> Max Profit: 300 | Nodes Explored: 5
Dynamic Prog.  -> Max Profit: 300 | Table Steps (n*W): 200
*/