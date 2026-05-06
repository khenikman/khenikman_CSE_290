#include <iostream>
#include <vector>

using namespace std;

// Number of vertices in the graph
#define V 5
vector<vector<int>> allPaths;

// Check if vertex v can be added at index 'pos' in the current path
bool isSafe(int v, bool graph[V][V], vector<int>& path, int pos) {
    // Check if this vertex is an adjacent neighbor of the previously added vertex
    if (graph[path[pos - 1]][v] == 0) return false;

    // Check if the vertex has already been included in the path
    for (int i = 0; i < pos; i++) {
        if (path[i] == v) return false;
    }
    return true;
}

// Recursive function to solve the Hamiltonian Path problem
void solveHamPath(bool graph[V][V], vector<int>& path, int pos) {
    // Base Case: All vertices are included in the path
    if (pos == V) { //if our path vector fills up with V elements we have a path
      allPaths.push_back(path);

      return;
    }

    // Try different vertices as the next candidate in the path (We are not full)
    for (int v = 0; v < V; v++) {
        //bool foundPath = false;
        if (isSafe(v, graph, path, pos)) { //can our next element added to the graph be v?
            path[pos] = v; // Choose

             solveHamPath(graph, path, pos + 1);
              //return true;
                 
             

             


            path[pos] = -1; // Backtrack: Remove choice and try next
        }
    }
            // if (pos+1 < V) {
            //     path.pop_back();
            //     path.pop_back();
            //     solveHamPath(graph, path, pos + 1);

            // }

    //return false;
}

// void findHamiltonianCycle() {

// }

int main() {
    // Adjacency Matrix representation of the graph
    bool graph[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    vector<int> path(V, -1);
    path[0] = 0; // Start at vertex 0

    solveHamPath(graph, path, 1);
    if (!allPaths.empty()) {  

      for (vector<int> v : allPaths) { 
        for (int vertex : v) {

        
        std::cout <<  vertex  << " "; //print path
      }
      std::cout << endl;
    }
    }
    else {
      cout << "No Hamiltonian Path exists." << endl;

    }

    return 0;
}
