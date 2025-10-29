#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Item {
    int weight;
    int utility;
};

int knapsack(int capacity, vector<Item>& items, vector<int>& chosenItems) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

  
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].utility + dp[i - 1][w - items[i - 1].weight],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int w = capacity;
    for (int i = n; i > 0 && dp[i][w] > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            chosenItems.push_back(i - 1);
            w -= items[i - 1].weight;
        }
    }

    return dp[n][capacity];
}

int main() {
    int n, capacity;

    cout << "Enter the number of items : ";
    cin >> n;

    cout << "Enter the truck capacity : ";
    cin >> capacity;

    vector<Item> items(n);

    cout << "Enter the weight and utility for each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " - Weight: ";
        cin >> items[i].weight;
        cout << "Item " << i + 1 << " - Utility: ";
        cin >> items[i].utility;
    }

    vector<int> chosenItems;
    int maxUtility = knapsack(capacity, items, chosenItems);

    cout << "max utility: " << maxUtility << endl;
    cout << "Items chosen :\n";

    for (int i = chosenItems.size() - 1; i >= 0; i--) {
        int idx = chosenItems[i];
        cout << "Item " << idx + 1 
             << " - Weight: " << items[idx].weight 
             << " Utility: " << items[idx].utility << endl;
    }

    return 0;
}
