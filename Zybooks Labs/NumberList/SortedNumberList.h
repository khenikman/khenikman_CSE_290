#ifndef SORTEDNUMBERLIST_H
#define SORTEDNUMBERLIST_H
#include "NumberList.h"

class SortedNumberList : public NumberList {
private:
   // Optional: Add any desired private functions here

public:
   SortedNumberList() {
      head = nullptr;
      tail = nullptr;
   }

   // Inserts the number into the list in the correct position such that the
   // list remains sorted in ascending order.
   void Insert(double number) {
      // TODO: Type your code here
      //listhead = head;
      //SortedNumberList = 
      NumberListNode* newNode = new NumberListNode(number);
      if (head == nullptr) {
        newNode -> SetData(number);
        newNode -> SetNext(head);
        head = newNode;
        tail = newNode;
        return;
      }
      else if(head->GetData() > number) {
        newNode -> SetData(number);
        newNode -> SetNext(head);
        head = newNode;
        return;
      }
    else {
        NumberListNode* current = head;
        while (current->GetNext() != nullptr &&
           current->GetNext()->GetData() < number) {
        current = current->GetNext();
        }
        if (current->GetNext() == nullptr) {
            tail = current;

        }

        newNode -> SetData(number);
        newNode -> SetNext(current->GetNext()); //node ahead to before
        current -> SetNext(newNode); //node before to value of new node
        
    }
}
   
   // Removes the node with the specified number value from the list. Returns
   // true if the node is found and removed, false otherwise.
bool Remove(double number) {
    if (head == nullptr) return false;

    // Case 1: removing head
    if (head->GetData() == number) { //head is not null with have elements
        NumberListNode* toDelete = head;
        head = head->GetNext(); //iterate the head to the next node

        if (head != nullptr) { //if the head has data we are only removing the head node
            head->SetPrevious(nullptr); // keep doubly-links consistent
        } else { //if the next element is null then the list is empty tail is null
            tail = nullptr; // list became empty
        }

        delete toDelete; //we have deleted the node we can remove it from memory
        return true; 
    }

    // Case 2: find node, tracking prev manually (works even if prev pointers are wrong)
    NumberListNode* prev = head;
    NumberListNode* cur  = head->GetNext();

    while (cur != nullptr && cur->GetData() != number) {
        prev = cur; //update node positions
        cur = cur->GetNext();
    }

    if (cur == nullptr) return false; // not found

    // Unlink cur
    NumberListNode* next = cur->GetNext();
    prev->SetNext(next);

    if (next != nullptr) {
        next->SetPrevious(prev); // fix backward link for future operations
    } else {
        tail = prev; // removed the tail
    }

    delete cur;
    return true;
}

      

};

#endif