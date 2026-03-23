#include <iostream>

// Step 1: Define the Node Structure
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Step 2: Implement the LinkedList Class
class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        //deallocates the nodes
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }


    void insertFront(int value) {
        // TODO: insert a new node with value at the front of the list
        Node* newNode = new Node(value);
        //Node* refNode = head;

        newNode->next = head;
        head = newNode;
            
        
    }

    void insertBack(int value) {
        // TODO: insert a new node with value at the end of the list
        Node* newNode = new Node(value);
        Node* refNode = head;
        if (refNode == nullptr) {
            head = newNode;
        }
        else {
            while (refNode->next != nullptr) {
                refNode = refNode->next;
            }
            refNode->next = newNode;
        }
    }

void printList() const {
    Node* refNode = head;
    while (refNode != nullptr) {
        std::cout << refNode->data;
        if (refNode->next != nullptr) {
            std::cout << " ";
        }
        refNode = refNode->next;
    }
    std::cout << std::endl;
}

    
};

int main() {
    LinkedList list;
    list.insertFront(10);
    list.insertFront(20);
    list.insertFront(30);
    list.insertBack(40);
    list.insertBack(50);
    list.printList();
    return 0;
}
