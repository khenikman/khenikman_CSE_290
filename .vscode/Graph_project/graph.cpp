#include <vector>
#include <iostream>
#include <stack>
using namespace std;

class Graph {
    public:

    int numVerticies;

    vector<vector<int>> graph;

    Graph(int numVert) : numVerticies(numVert), graph(numVert) {}

    void addEdge(int u, int v) {
        //Assert statement to check if u and v are in the graph
        if (u >= numVerticies || v >= numVerticies) {
            cout << "u or v are not in the graph" << endl;
            return;
        }
        graph[u].push_back(v);
    }

    // void depthFirstSearch(int startNode) {
    //     stack<int> trackedNodes;
    //     vector<bool> visitedNodes[numVerticies];
    //     int vertex = graph[startNode].front[];

    // }

    void dfs(vector<bool>& visited, int u) {
        //stack<bool> trackedNodes;
        visited[u] = true;
        cout << u << endl;
        for(int v : graph[u]) {
            if (!visited[v]) {
                dfs(visited,v);
            }
        }

    }

    void addBidirectionalEdge(int u,int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
};

int main() {
    Graph g(10);
    g.addEdge(0,3);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(5,3);
    g.addEdge(0,2);
    g.addEdge(5,2);
    vector<bool> visited(6);
    //visited[0] = true;
    g.dfs(visited, 0);

}