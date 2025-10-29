#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to;
    int weight;
};

void dijkstra(int V, vector<vector<Edge>>& graph, int src, vector<int>& dist) {
    dist.assign(V, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue; 

        for (auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int V, E;
    cout << "Enter total no. of intersections: ";
    cin >> V;
    cout << "Enter total number of roads ";
    cin >> E;

    vector<vector<Edge>> graph(V);

    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); 
    }

    int source;
    cout << "Enter ambulance start location: ";
    cin >> source;

    int numHospitals;
    cout << "Enter number of hospitals: ";
    cin >> numHospitals;

    vector<int> hospitals(numHospitals);
    cout << "Enter hospital nodes: ";
    for (int i = 0; i < numHospitals; i++)
        cin >> hospitals[i];

    vector<int> dist;
    dijkstra(V, graph, source, dist);

   
    int nearestHospital = -1;
    int minTime = INT_MAX;

    for (int h : hospitals) {
        if (dist[h] < minTime) {
            minTime = dist[h];
            nearestHospital = h;
        }
    }

    if (nearestHospital != -1)
        cout << "Nearest hospital is at node " << nearestHospital
             << " with travel time " << minTime << " minutes.\n";
    else
        cout << "No reachable hospital found.\n";

    return 0;
}
