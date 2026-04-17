// Create Node class - node contain the distance (initialized to infinity) also should contain Node *predV.  5
// First  create a graph class, this contains vertices and edges. You can use the <vector < Node> >  adjacencyList. Include size for number of vertices . Feel to try different data structures 5
// Create an add edge member function: edge(int i, int j) 5
// Implement the djkstras Shortest path algorithm. bool dijkstra()  10pts

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Vertex {

    private:

    //int initialDistance;
    //Node *predV;

    public:
    int edgeWeight;// does this make sense
    Vertex *predV; //predecessor on the shortest path
    int distance = 	INT_MAX;
    int id;
    //int initialDistance = INT_MAX;
    Vertex(int vertexID = -1, int weight) : predV(nullptr), edgeWeight(weight), id(vertexID) {}


};

class Graph {

    public:

    vector<vector<Vertex>> adjacencyList; //Stores the connected vertex and weight of the edge
    int size;

    Graph(int graphSize) {
        size = graphSize;
        adjacencyList.resize(graphSize);

    }



    void addEdge(int u, int v, int edgeWeight) {
            adjacencyList[u].push_back(Vertex(v, edgeWeight)); // each adjacent element to u stores the vertex of the connecting edge and the weight between them
            cout << "Edge added succesfully: Vertex behind exists" << endl;
        
    }

    bool dijkstra(int startPosition) {
        
        vector<Vertex> distanceFromClosestEdges[]; //holds the vectors for the shortest path

        int currentPosition = startPosition;

        // queue<Vertex> unvisitedQueue; //FIFO Priority Queue

        // for (Vertex &vector: adjacencyList[currentPosition]) { //push in adjacent vectors

        //     unvisitedQueue.push(vector);
        // }

        distanceFromClosestEdges.push_back(adjacencyList[startPosition]);        

    for (const Vertex& neighbor : adjacencyList[currentPosition]) {
    int nextVertex = neighbor.id;
    int weight = neighbor.edgeWeight;

    int alternativePathDistance = vertices[currentPosition].distance + weight;

    if (alternativePathDistance < vertices[nextVertex].distance) {
        vertices[nextVertex].distance = alternativePathDistance;
        vertices[nextVertex].predV = &vertices[currentPosition];
    }
}









            for (Vertex *vertex : *adjacencyList[currentPosition]) {
                vertex->predV = nullptr;
            }

            

        }

        vertex->distance = 0;
        unvisitedQueue.pop();



        while(!unvisitedQueue.empty()) {
            int currentNode = unvisitedQueue.front();
            for (int adjacentNode = 0; adjacentNode < adjacencyList[currentNode].size(); adjacentNode++) {
        }

        

 


// Start
// DijkstraShortestPath(startV) {
//    for each vertex currentV in graph {
//       currentV⇢distance = Infinity
//       currentV⇢predV = 0
//       Enqueue currentV in unvisitedQueue
//    }

//    // startV has a distance of 0 from itself
//    startV⇢distance = 0

//    while (unvisitedQueue is not empty) {
//       // Visit vertex with minimum distance from startV
//       currentV = DequeueMin unvisitedQueue

//       for each vertex adjV adjacent to currentV {
//          edgeWeight = weight of edge from currentV to adjV
//          alternativePathDistance = currentV⇢distance + edgeWeight
          
//          // If shorter path from startV to adjV is found,
//          // update adjV's distance and predecessor
//          if (alternativePathDistance < adjV⇢distance) {
//             adjV⇢distance = alternativePathDistance
//             adjV⇢predV = currentV
//          }
//       }
//    }
// }

        return true;
    }

}
};



int main() 
{

    Graph g(4);
    g.addEdge(0, 1, 40); //adds the edge between two vertices and the edge weight of 40 is assigned
    g.addEdge(0, 2, 20);
    g.addEdge(1, 2, 50);
    g.addEdge(2, 3, 10);

    //int u = 0, v = 3;
    //bool result = g.isReachable(u, v);
    //cout << boolalpha << result;

    return 0;
}