#include <random>
#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Vertex {
    public:
    int index;
    string color;

    Vertex() {
        index = -1;
        color = "";
    }

    Vertex (int pos, string colored) {
        index = pos;
        color = colored;
    }
};

class Graph {

    public:

    vector <Vertex> vertices;
    vector<vector<int>> edgeList;

    Graph(int size) {
        
        edgeList.resize(size, vector<int> (size));
        srand(time(0));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int random = rand() % 2;
                //cout << random;
                edgeList[i][j] = random; // 1 edge exists, 0 it doesnt

            }    

        }
        vertices.resize(size);
        for (int i = 0; i < vertices.size(); i++) {
            int random = rand() % 2;

            if (random == 1) {
                vertices[i] = Vertex(i , "white");
            }
            if (random == 0) {
                vertices[i] = Vertex(i , "black");
            }
        }
    }

    Graph(string testcase) {
    vector<vector<int>> edgeListTest;

    if (testcase == "1") {
    edgeListTest = {
        {0,1,1},
        {1,0,1},
        {1,1,0}
    };

    vertices.resize(3);

    vertices[0] = Vertex(0, "black");
    vertices[1] = Vertex(1, "white");
    vertices[2] = Vertex(2, "black");
    }

    if (testcase == "2") {
    edgeListTest = {{0,1,0,0},{1,0,1,0},{0,1,0,1},{0,0,1,0}};
    vertices.resize(4);

            
    vertices[0] = Vertex(0 , "black");
    vertices[1] = Vertex(1 , "white");
    vertices[2] = Vertex(2 , "black");
    vertices[3] = Vertex(3 , "white");
    }

    if (testcase == "3") {
        edgeListTest = {
            {0,1,1,1,1},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0}
        };

        vertices.resize(5);

        vertices[0] = Vertex(0, "black");
        vertices[1] = Vertex(1, "white");
        vertices[2] = Vertex(2, "white");
        vertices[3] = Vertex(3, "white");
        vertices[4] = Vertex(4, "white");
    }

    edgeList = edgeListTest;


}


    void printGraph() {
        for (int i = 0; i < edgeList.size(); i++) {
            for (int j = 0; j < edgeList[i].size(); j++) {
                cout << edgeList[i][j] << " ";
            }
            cout << endl;
        }
    }

    // void bfs(int start) {
    //     //bfs goes layer by layer
    //     //queue in start position
    //     vector<bool> visited(edgeList.size(), false);
    //     queue<int> q;
    //     q.push(start);

    //     //check if our queue is empty
    //     if (!q.empty()) {
    //         int index = q.front();
    //         q.pop();

    //         for (int i = 0; i < edgeList[index].size(); i++) {
    //             if (edgeList[index][i] == 1) {

    //             }
    //         }
    //     }
        
    //     //if not pop start element

    //     //check its adjacencyList
    // }

   bool DFS(int start) {
   //Create new, empty stack named vertexStack
    stack<int> vertexStack;
   //Create new, empty set named visitedSet
    vector<bool> visited(edgeList.size(), false);
   //Push startVertex to vertexStack
    vertexStack.push(start);
    //visited[i] = true;

   while (!vertexStack.empty()) {
      int currentVertex = vertexStack.top();
      vertexStack.pop();

      if (!visited[currentVertex]) {
        visited[currentVertex] = true;
        for (int i = 0; i < edgeList[currentVertex].size(); i++) {
            if (edgeList[currentVertex][i] == 1) {

                if (vertices[i].color == vertices[currentVertex].color) {
                    return false;
                }

                if (visited[i] != true) {
                    vertexStack.push(i);
                }

            }
            
        }
        }
   }
   return true;
} 

};

int main () {

    //Random Test Case
    Graph g(5);
    g.printGraph();
    cout << boolalpha << g.DFS(0) << endl;
    

    
    //TEST CASES
    Graph h("1");
    h.printGraph();
    cout << boolalpha << h.DFS(0) << endl;

    Graph f("2");
    f.printGraph();
    cout << boolalpha << f.DFS(0) << endl;

    Graph i("3");
    i.printGraph();
    cout << boolalpha << i.DFS(0) << endl;

    return 0;
};