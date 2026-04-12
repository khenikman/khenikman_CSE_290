using namespace std;
#include <iostream>
#include <vector>

class CellNode {

   public : 

       int state; //state of the cellnode

       CellNode *left; //pointer to the left cell node

       CellNode *right; //pointer to the right cell node

       CellNode(int initialState = 0) : state(initialState), left(nullptr), right(nullptr) {} //initial state of all nodes is 0

int applyRule(int left, int self, int right) { //ruleset given by Michael Lewis
    if (left == 1 && self == 1 && right == 1) return 1; // 111
    if (left == 1 && self == 1 && right == 0) return 1; // 110
    if (left == 1 && self == 0 && right == 1) return 1; // 101
    if (left == 1 && self == 0 && right == 0) return 1; // 100
    if (left == 0 && self == 1 && right == 1) return 1; // 011
    if (left == 0 && self == 1 && right == 0) return 0; // 010
    if (left == 0 && self == 0 && right == 1) return 1; // 001
    return 0; // 000
}

void printGraph(vector<CellNode*> nodes) { //prints a generation of cell nodes
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->state == 1) {
            cout << "*";
        }
        else { cout << " "; }
    }
}

};

int main() {

    int size = 16; //Number of cellular nodes connected to each other
    int generations = 10; //Number of generations of cellular nodes
    vector<CellNode*> nodes(size); //create a list to hold nodes

    for (int i = 0; i < size; i++) { //Set the initial nodes of each node to 0
        nodes[i] = new CellNode(0); 
    }
    nodes[size / 2]->state = 1; //Sets the size/2 node roughly the middle node to a 1 so we can observe generational cellular behavior

    for (int i = 0; i < size; i++) { //Doubly links each cellular node
        nodes[i]->left = nodes[((i - 1 + size) % size)]; //sets the pointer to the left node
        nodes[i]->right = nodes[(i+1) % size]; //sets the pointer to the right node
    }

    vector<int> nextState(size); //vector of the states for the 
    nodes[0]->printGraph(nodes);
    cout << endl;
    
    for (int j = 0; j < generations; j++) {
        //nodes[j]->printGraph(nodes);
        for(int i = 0; i < size; i++) {

            nextState[i] = nodes[i]->applyRule(nodes[i]->left->state, nodes[i]->state, nodes[i]->right->state);

            
        }
        
        for (int i = 0; i < size; i++) { //goes through the current generation and updates all cellular node states to the next state
            nodes[i]->state = nextState[i];
        }

        nodes[0]->printGraph(nodes); //prints the new generation
        cout << endl;

    }

    
    return 0;
}