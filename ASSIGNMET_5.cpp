#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    double cost;
};

int main() {
    int stages;
    cout << "Enter total no. of stages: ";
    cin >> stages;

    vector<int> nodes_in_stage(stages);
    cout << "Enter no. of node in each stage (" << stages << " values): ";
    for (int i = 0; i < stages; i++) cin >> nodes_in_stage[i];

    int total_nodes = accumulate(nodes_in_stage.begin(), nodes_in_stage.end(), 0);
    int edges;
    cout << "Enter no. of edges: ";
    cin >> edges;

    cout << "Enter each edge as: u v cost\n";
    vector<Edge> edgeList(edges);
    vector<vector<pair<int, double>>> adj(total_nodes);

    for (int i = 0; i < edges; i++) {
        int u, v;
        double c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        edgeList[i] = {u, v, c};
    }

    vector<double> cost(total_nodes, 1e9);
    vector<int> nextNode(total_nodes, -1);
    cost[total_nodes - 1] = 0; 

   
    for (int i = total_nodes - 2; i >= 0; i--) {
        for (auto &edge : adj[i]) {
            int v = edge.first;
            double w = edge.second;
            if (w + cost[v] < cost[i]) {
                cost[i] = w + cost[v];
                nextNode[i] = v;
            }
        }
    }

    cout << "Best costs from Stage-0 nodes:\n";
    int node_index = 0;
    for (int i = 0; i < nodes_in_stage[0]; i++) {
        cout << "Node " << node_index++ << ": cost = " << cost[i] << "\n";
    }

    cout << "Enter a source node id: ";
    int src;
    cin >> src;

    if (src != -1) {
        cout << "Path from " << src << " : ";
        int cur = src;
        double totalCost = 0;
        while (cur != -1) {
            cout << cur;
            if (nextNode[cur] != -1) cout << " -> ";
            if (nextNode[cur] != -1)
                totalCost += find_if(adj[cur].begin(), adj[cur].end(),
                                     [&](auto &p) { return p.first == nextNode[cur]; })
                                 ->second;
            cur = nextNode[cur];
        }
        cout << "\nTotal route cost : " << totalCost << "\n";
    }

 
    cout << "Enter number of live updates to edge costs (0 to finish): ";
    int updates;
    cin >> updates;

    while (updates--) {
        int u, v;
        double mult;
        cout << "Enter edge update (u v multiplier): ";
        cin >> u >> v >> mult;

        for (auto &edge : adj[u]) {
            if (edge.first == v)
                edge.second *= mult;
        }
    }


    fill(cost.begin(), cost.end(), 1e9);
    fill(nextNode.begin(), nextNode.end(), -1);
    cost[total_nodes - 1] = 0;

    for (int i = total_nodes - 2; i >= 0; i--) {
        for (auto &edge : adj[i]) {
            int v = edge.first;
            double w = edge.second;
            if (w + cost[v] < cost[i]) {
                cost[i] = w + cost[v];
                nextNode[i] = v;
            }
        }
    }

    cout << "After update best cost from 0th node:\n";
    node_index = 0;
    for (int i = 0; i < nodes_in_stage[0]; i++) {
        cout << "Node " << node_index++ << ": cost = " << cost[i] << "\n";
    }

    return 0;
}
