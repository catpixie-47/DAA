#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    double weight;
    double utility;
    bool divisible;
    double ratio; 
};


bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {
    int n;
    double W;
    cout << "Enter max boat capacity in kg: ";
    cin >> W;

    cout << "Enter no. of relief items: ";
    cin >> n;
    cout << endl;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter details for items " << i + 1 << ":\n";
        cout << "Weight (kg): ";
        cin >> items[i].weight;
        cout << "Utility value: ";
        cin >> items[i].utility;
        cout << "Divisible? (1 for yes, 0 for no): ";
        cin >> items[i].divisible;
        items[i].ratio = items[i].utility / items[i].weight;
        cout << endl;
    }

   
    sort(items.begin(), items.end(), compare);

    cout << fixed << setprecision(2);
    cout << "Items sorted by utility/weight ratio (descending):\n";
    cout << left << setw(10) << "Weight" 
         << setw(10) << "Utility" 
         << setw(15) << "Divisible" 
         << setw(15) << "Utility/Weight" << endl;

    for (auto &i : items) {
        cout << left << setw(10) << i.weight
             << setw(10) << i.utility
             << setw(15) << (i.divisible ? "Yes" : "No")
             << setw(15) << i.ratio << endl;
    }
    cout << endl;

    double totalUtility = 0.0, currentWeight = 0.0;

    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= W) {
            
            currentWeight += items[i].weight;
            totalUtility += items[i].utility;
        } else {
           
            if (items[i].divisible) {
                double remain = W - currentWeight;
                totalUtility += items[i].utility * (remain / items[i].weight);
                currentWeight += remain;
            }
            break; 
        }
    }

    cout << "Maximum utility value the boat can carry: " << totalUtility << endl;

    return 0;
}
