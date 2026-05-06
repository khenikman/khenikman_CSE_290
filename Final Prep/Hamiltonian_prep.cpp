#include <iostream>
#include <vector>
using namespace std;

#define V 5

vector<vector<int>> allPaths;

// Returns true if vertex v can be placed at path[pos]
bool isSafe(int v, bool graph[V][V], vector<int>& path, int pos) {

    // TODO:
    // 1. Check whether v is adjacent to the previous vertex in path.
    // 2. Check whether v is already inside the path.
    // 3. Return true only if both checks pass.
    if (graph[path[pos -1]][v] == 0) {
        return false;

    }
    for (int i=0; i < path.size(); i++) {
        if (path[i] == v) {
            return false;
        }
    }

    return true;

}

// Recursively builds all Hamiltonian paths
void solveHamPath(bool graph[V][V], vector<int>& path, int pos) {

    // TODO:
    // 1. Base case:
    //    If pos == V, save the path and return.
    if (pos == V) {
        allPaths.push_back(path);
        return;
    }

    // 2. Recursive case:
    //    Loop through every possible vertex v from 0 to V - 1.
    for (int i = 0; i < V; i++) {
        if (isSafe(i, graph, path, pos)) {

            path[pos] = i;

            solveHamPath(graph, path, pos+1);

            path[pos] = -1;
        }
    }

    // 3. For each v:
    //    Check if v is safe.

    // 4. If safe:
    //    Choose v by placing it into path[pos].

    // 5. Recurse to fill the next position.

    // 6. Backtrack by resetting path[pos].

}

int main() {

    bool graph[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    vector<int> path(V, -1);

    path[0] = 1;

    solveHamPath(graph, path, 1);

    if (allPaths.empty()) {
        cout << "No Hamiltonian Path exists." << endl;
    }
    else {
        for (vector<int> p : allPaths) {
            for (int vertex : p) {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }

    return 0;
}