#include <iostream>
#include <vector>

using namespace std;

/**
 * Helper function to perform DFS and detect cycle in an undirected graph.
 * @param v Current vertex
 * @param visited Vector to track visited vertices
 * @param parent Parent vertex of current vertex
 * @param adj Adjacency list of the graph
 * @return true if a cycle is detected, false otherwise
 */
bool dfs(int v, vector<bool>& visited, int parent, const vector<vector<int>>& adj) {
    visited[v] = true;
    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            // Recur for unvisited neighbor
            if (dfs(neighbor, visited, v, adj)) {
                return true;
            }
        } else if (neighbor != parent) {
            // If visited and not parent, cycle detected
            return true;
        }
    }
    return false;
}

/**
 * Detects if the undirected graph contains a cycle.
 * @param adj Adjacency list representation of the graph
 * @param n Number of vertices
 * @return true if the graph contains a cycle, false otherwise
 */
bool isCyclic(const vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    // Check all components (for disconnected graphs)
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfs(i, visited, -1, adj)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // Add edge to adjacency list (undirected)
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (isCyclic(adj, n)) {
        cout << "Graph contains cycle" << endl;
    } else {
        cout << "Graph does not contain cycle" << endl;
    }

    return 0;
}
