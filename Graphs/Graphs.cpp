#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {

    public:

    vector<vector<int>> adjacencyList;
    int size;

    Graph(int graphSize) {
        size = graphSize;
        adjacencyList.resize(graphSize);

    }

    


    void addEdge(int u , int v) {
        adjacencyList[u].push_back(v);
    }

    void bfs(int start) {
        vector<bool> visited(size, false);
        queue<int> q;
        visited[start] = true; // root node the tree
        q.push(start); // push root node to the top of the queue FIFO struct
        cout << start << " ";
        while(!q.empty()) {
            int currentNode = q.front();
            q.pop();
            

            for (int adjacentNode = 0; adjacentNode < adjacencyList[currentNode].size(); adjacentNode++) {
                //cout << adjacencyList[currentNode][adjacentNode];
                //cout << adjacentNode;
                if (!visited[adjacencyList[currentNode][adjacentNode]]) {
                    visited[adjacencyList[currentNode][adjacentNode]] = true;
                    q.push(adjacencyList[currentNode][adjacentNode]);
                    cout << adjacencyList[currentNode][adjacentNode] << " ";
                }
            }
        }
    }

    bool isReachable(int start, int target) {

        if (start == target) {
            return true;
        }

        vector<bool> visited(size, false);
        queue<int> q;
        visited[start] = true; // root node the tree
        q.push(start); // push root node to the top of the queue FIFO struct
        //cout << start << " ";

        while(!q.empty()) {
            int currentNode = q.front();
            q.pop();
            

            for (int adjacentNode = 0; adjacentNode < adjacencyList[currentNode].size(); adjacentNode++) {
                //cout << adjacencyList[currentNode][adjacentNode];
                //cout << adjacentNode;
                if (!visited[adjacencyList[currentNode][adjacentNode]]) {
                    if (adjacencyList[currentNode][adjacentNode] == target) {
                        return true;
                    }

                    visited[adjacencyList[currentNode][adjacentNode]] = true;
                    q.push(adjacencyList[currentNode][adjacentNode]);
                    //cout << adjacencyList[currentNode][adjacentNode] << " ";
                }
            }
        }

        return false;
    }



};

int main() 
{

    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    int u = 0, v = 3;
    bool result = g.isReachable(u, v);
    cout << boolalpha << result;

    return 0;
}