#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>
#include <string>
using namespace std;

class Vertex {

    public:
    int edgeWeight;// used by the add edge method to create weights between edges
    Vertex *predV; // predecessor on the shortest path
    int distance = 	INT_MAX; // distance on this path is assigned to infinity initially
    int id; // positional identifier for vertex

    Vertex(int weight = 0, int vertexID = -1) : predV(nullptr), edgeWeight(weight), id(vertexID) {}


};

class Graph {

    public:

    vector<vector<Vertex>> adjacencyList; // Stores the adjacent vertexes of each vertex
    vector<Vertex> vertices; // Creates a seperate vector of all vertexes
    int size; // Quantity of vertexes in graph

    Graph(int graphSize) {
        size = graphSize;
        adjacencyList.resize(graphSize);
        vertices.resize(graphSize);

        for (int i = 0; i < graphSize; i++) { //fills the vector of vertexes with initial weights of 0 and an id 
            vertices[i] = Vertex(0, i);
        }
    }



    void addEdge(int u, int v, int edgeWeight) {
            adjacencyList[u].push_back(Vertex(edgeWeight, v)); // each adjacent element to u stores the vertex of the connecting edge and the weight between them
            cout << "Edge added succesfully!" << endl;
        
    }

    bool dijkstra(int startPosition) {
        
        int currentPosition = startPosition;
        
        using PQEntry = pair<int, int>;

        priority_queue<PQEntry, vector<PQEntry>, greater<PQEntry>> unvisitedQueue; // priority queue that stores the pair: {distance, vertexIndex} and puts the shortest distance on top

        for (int i = 0; i < size; i++) { // for different start positions resetting the path is necessary per call b/c we use the same graph
            vertices[i].distance = INT_MAX;
            vertices[i].predV = nullptr;
        }

        vertices[startPosition].distance = 0; // set start index to zero distance

        unvisitedQueue.push({vertices[startPosition].distance, vertices[startPosition].id}); //push start vertex



    while(!unvisitedQueue.empty()) {
        int currentDistance = unvisitedQueue.top().first; // grabs the vertex distance of the closest vertex
        int currentVertex = unvisitedQueue.top().second; // grabs the vertex ID of the closest vertex
        unvisitedQueue.pop(); // Pops the top element
        
    
        if (currentDistance > vertices[currentVertex].distance) { // meaning we do not care about this current vertex if it was not selected in the shortest path
            continue;
        }

        for (const Vertex& neighbor : adjacencyList[currentVertex]) { // goes through the adjacency list of the current vertex
            int nextVertex = neighbor.id; //grabs adjacent vertexes id
            int weight = neighbor.edgeWeight; //the weights between them

            int alternativePathDistance = vertices[currentVertex].distance + weight; // cumulative total of dijkstra's shortest path

            if (alternativePathDistance < vertices[nextVertex].distance) { // if this path is more ideal add this next vertex to the queue
                vertices[nextVertex].distance = alternativePathDistance;
                vertices[nextVertex].predV = &vertices[currentVertex];
                unvisitedQueue.push({vertices[nextVertex].distance, vertices[nextVertex].id});
            }
        }
    }




        return true;
    }

    void printdijkstra(int startPosition, int target) {
        dijkstra(startPosition); //creates the path
        vector<Vertex*> dijkstraList;
        //cout << "(" << startPosition << ")";
        int currentPosition = target;
        dijkstraList.push_back(&vertices[target]);

        while (vertices[currentPosition].predV != nullptr) {
            

            dijkstraList.push_back(vertices[currentPosition].predV);
            currentPosition = vertices[currentPosition].predV->id;

            if (currentPosition == startPosition) {
                break;
            }
        }

        for (int i = dijkstraList.size()-1 ; i >= 0 ; i--) {
            cout << "(" << dijkstraList[i]->id << ")";
            if (i-1 >= 0) {
            //cout << "---" << dijkstraList[i-1]->edgeWeight << "---";
            cout << " -> ";
            }
        }
        cout << " Dijkstra Path Length: " << dijkstraList[0]->distance << endl;

    }
};





int main() 
{

    Graph g(6);
    g.addEdge(0, 1, 40); //adds the edge between two vertices and the edge weight of 40 is assigned
    g.addEdge(0, 2, 20);
    g.addEdge(1, 2, 50);
    g.addEdge(2, 4, 15);
    g.addEdge(2, 5, 22);
    g.addEdge(1, 3, 16);
    g.addEdge(3, 5, 23);
    g.addEdge(3, 4, 43);
    g.addEdge(4, 5, 12);

    g.printdijkstra(0,3);
    g.printdijkstra(0,5);
    g.printdijkstra(1,4);
    g.printdijkstra(2,5);

    //int u = 0, v = 3;
    //bool result = g.isReachable(u, v);
    //cout << boolalpha << result;

    return 0;
}