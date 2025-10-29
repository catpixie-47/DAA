#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

struct Order {
    int orderID;
    int timestamp;
    string customer;
};

void merge(vector<Order>& orders, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Order> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = orders[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = orders[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].timestamp <= R[j].timestamp)
            orders[k++] = L[i++];
        else
            orders[k++] = R[j++];
    }

    while (i < n1)
        orders[k++] = L[i++];
    while (j < n2)
        orders[k++] = R[j++];
}

void mergeSort(vector<Order>& orders, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(orders, left, mid);
        mergeSort(orders, mid + 1, right);
        merge(orders, left, mid, right);
    }
}

int main() {
    vector<Order> orders = {
        {101, 982634, "vaishnavi"},
        {102, 725722, "raj"},
        {103, 927365, "gauri"},
        {104, 273627, "abhishek"},
        {105, 362526, "siya"}
    };

    auto start = high_resolution_clock::now();
    mergeSort(orders, 0, orders.size() - 1);
    auto end = high_resolution_clock::now();

    duration<double> time_taken = end - start;

    cout << "Orders sorted by timestamp successfully!" << endl;
    cout << "Time taken: " << time_taken.count() << " seconds\n" << endl;

    cout << "Sorted order list:" << endl;
    for (auto& o : orders) {
        cout << "order id: " << o.orderID 
             << " | Timestamp: " << o.timestamp 
             << " | customer: " << o.customer << endl;
    }

    cout << "\ntime complexity analysis:" << endl;
    cout << "TC for merge sort: O(n log n)" << endl;

    return 0;
}
