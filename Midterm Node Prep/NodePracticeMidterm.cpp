#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int val) : data(val),next(nullptr) {}
};

void printList(Node* head) {
    Node* current = head;

    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }

    cout << "nullptr" << endl;
}

bool deleteData(Node*& head,int val) {
    Node* referenceHead = head;
    if (referenceHead == nullptr) { //not real head
        return false;
    }

    if (referenceHead->data == val) {
        head = head->next; //removed value at the start of the list
        return true;
    }

    while (referenceHead->next != nullptr) {
        if (referenceHead->next->data == val) {
            referenceHead->next = referenceHead->next->next; //remove any value after the first that matches the key
            return true;
        }
        referenceHead = referenceHead->next;
    }

    return false;
}

Node* insertAfterSmallerValue(Node*& head, int newData) {
    Node* insertedNode = new Node(newData);
    Node* referenceHead = head;

    if (head == nullptr) {
        return nullptr;
    }
    if (head->data > insertedNode->data) {//smallest to largest
        
        insertedNode->next = head;
        head = insertedNode;
        return insertedNode;
    }
    while (referenceHead->next != nullptr && referenceHead->next->data < insertedNode->data) {
        referenceHead = referenceHead->next;
    }
    if (referenceHead->next == nullptr)  {
        referenceHead->next = insertedNode;
            return insertedNode;
    }
    else {
        insertedNode->next = referenceHead->next;
        referenceHead->next = insertedNode;
            return insertedNode;
    }


}

void insertHead(Node*& head, int newData) {
    Node* newNode = new Node(newData);
    newNode->next = head;
    head = newNode;
}

int main() {
    Node *head = nullptr;
    insertHead(head, 15);
    insertHead(head, 10);
    insertHead(head, 3);
    insertAfterSmallerValue(head, 5);
    insertAfterSmallerValue(head, 8);
    insertAfterSmallerValue(head, 7);
    //deleteData(head, 15);
    printList(head);
};