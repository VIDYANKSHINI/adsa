
#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
    int weight, profit;
    double ratio;
};

Item a[20];
int n, capacity, best = 0;

bool cmp(Item x, Item y) {
    return x.ratio > y.ratio;
}

double bound(int i, int weight, int profit) {
    if (weight >= capacity)
        return profit;

    double result = profit;

    for (int j = i; j < n; j++) {
        if (weight + a[j].weight <= capacity) {
            weight += a[j].weight;
            result += a[j].profit;
        }
        else {
            result += (capacity - weight) * a[j].ratio;
            break;
        }
    }

    return result;
}

void solve(int i, int weight, int profit) {
    if (weight <= capacity)
        best = max(best, profit);

    if (i == n || bound(i, weight, profit) <= best)
        return;

    if (weight + a[i].weight <= capacity)
        solve(i + 1, weight + a[i].weight,
              profit + a[i].profit);

    solve(i + 1, weight, profit);
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

    solve(0, 0, 0);

    cout << "Maximum profit: " << best << endl;

    return 0;
}
