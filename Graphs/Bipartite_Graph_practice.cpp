#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Vertex
{
    public:
    int index;
    bool color;

    
    Vertex(int id, bool colored) {
        index = id;
        color = colored;
    }
};


class Graph {
private:
    // adjacency list goes here
    vector<vector<int>> adjacencyList;
    // color vector goes here
    vector<Vertex> vertices;

    int size;


    // true = white
    // false = black

    // size variable goes here

public:
    // Constructor
    Graph(int vertices) {
        // store size
        size = vertices;
        adjacencyList.resize(size);
        //vertices.resize(size);

        // resize adjacency list

        // resize color list
    }

    // Add edge between source and destination
    void addEdges(int source, int destination) {
        // add destination to source's list
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source);
        // add source to destination's list
        // because this is an undirected graph
    }

    // Add color to a vertex
    void addColor(int vertex, bool c) {
        // set color at vertex
        vertices.push_back(Vertex(vertex,c));
    }

    // DFS function
    bool DFS(int source) {
        // create visited vector
        vector<bool> visitedList(size,false);

        // create stack
        stack<int> stack;
        // push source into stack
        stack.push(source);

        // while stack is not empty
        while (!stack.empty()) {

            // get top of stack
            int index = stack.top();
            // pop stack
            stack.pop();
            // if current vertex is not visited
            if (!visitedList[index]) {

                // mark current as visited
                visitedList[index] = true;
                // loop through neighbors
                for (int i = 0; i < adjacencyList[index].size(); i++) {

                    // get neighbor
                    
                    // if current and neighbor have same color
                    if (vertices[index].color == vertices[adjacencyList[index][i]].color) {
                        return false;
                    }

                    // if neighbor is not visited
                    if (!visitedList[adjacencyList[index][i]]) {
                        // push neighbor
                        stack.push(adjacencyList[index][i]);
                        //visitedList[adjacencyList[index][i]] == true;
                    }

                }
            }
        }

        // after DFS, check if entire graph was visited
        for (int i = 0; i < visitedList.size(); i++) {
            if (!visitedList[i]) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    cout << boolalpha;

    // Create first graph object: bipartite graph
    Graph g(4);

    // Add edges for bipartite graph
    g.addEdges(0,1);
    g.addEdges(1,2);
    g.addEdges(2,3);

    // Add colors
    g.addColor(0,true);
    g.addColor(1,false);
    g.addColor(2, true);
    g.addColor(3, false);

    cout << g.DFS(0) << endl;

    // Create second graph object: not bipartite graph
    Graph h(4);

    // Add edges for non-bipartite graph
    h.addEdges(1,3);
    h.addEdges(2,3);
    h.addEdges(0,3);
    h.addEdges(0,2);

    // Add colors
    h.addColor(0, true);
    h.addColor(1, true);
    h.addColor(2, true);
    h.addColor(3, true);


    cout << h.DFS(0) << endl;

    return 0;
}