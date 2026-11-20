
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    int weight, profit;
    double ratio;
};

// Sort according to profit/weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

// 1. Fractional Knapsack using Greedy
double fractionalKnapsack(Item items[], int n, int capacity) {
    sort(items, items + n, compare);

    double totalProfit = 0;

    for (int i = 0; i < n; i++) {
        if (capacity == 0)
            break;

        if (items[i].weight <= capacity) {
            totalProfit += items[i].profit;
            capacity -= items[i].weight;
        }
        else {
            totalProfit += items[i].ratio * capacity;
            capacity = 0;
        }
    }

    return totalProfit;
}

// 2. 0/1 Knapsack using Greedy
// Only for demonstrating Greedy failure
int greedy01(Item items[], int n, int capacity) {
    sort(items, items + n, compare);

    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= capacity) {
            totalProfit += items[i].profit;
            capacity -= items[i].weight;
        }
    }

    return totalProfit;
}

// 3. 0/1 Knapsack using Dynamic Programming
int knapsackDP(Item items[], int n, int capacity) {
    int dp[101][101] = {0};

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {

            if (items[i-1].weight <= w) {
                dp[i][w] = max(
                    items[i-1].profit +
                    dp[i-1][w - items[i-1].weight],

                    dp[i-1][w]
                );
            }
            else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    Item items[100];

    cout << "\nEnter weights and profits:\n";

    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].profit;

        items[i].ratio =
            (double)items[i].profit / items[i].weight;
    }

    Item fractionalItems[100];
    Item greedyItems[100];

    for (int i = 0; i < n; i++) {
        fractionalItems[i] = items[i];
        greedyItems[i] = items[i];
    }

    // Fractional Knapsack
    double fractional =
        fractionalKnapsack(fractionalItems, n, capacity);

    // Greedy 0/1 (comparison only)
    int greedy =
        greedy01(greedyItems, n, capacity);

    // 0/1 Knapsack using DP
    int dp =
        knapsackDP(items, n, capacity);

    cout << fixed << setprecision(2);

    cout << "\nFractional Knapsack (Greedy):\n";
    cout << "Maximum Profit = " << fractional << endl;

    cout << "\n0/1 Knapsack (Greedy - Comparison):\n";
    cout << "Maximum Profit = " << greedy << endl;

    cout << "\n0/1 Knapsack (Dynamic Programming):\n";
    cout << "Maximum Profit = " << dp << endl;

    return 0;
}

/*
Input:
3
50
10 60
20 100
30 120

Output:
Enter number of items: Enter knapsack capacity:
Enter weights and profits:
Item 1: Item 2: Item 3:
Fractional Knapsack (Greedy):
Maximum Profit = 240.00

0/1 Knapsack (Greedy - Comparison):
Maximum Profit = 220

0/1 Knapsack (Dynamic Programming):
Maximum Profit = 220
*/

/*
Time Complexity:
Fractional Knapsack: O(n log n) due to sorting
Greedy 0/1 demonstration: O(n log n) due to sorting
0/1 Knapsack using DP: O(n * W)

Space Complexity:
Fractional/Greedy Knapsack: O(n)
0/1 Knapsack using DP: O(n * W)
*/
