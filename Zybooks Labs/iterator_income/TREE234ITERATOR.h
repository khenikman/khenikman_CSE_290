#ifndef TREE234ITERATOR_H
#define TREE234ITERATOR_H

#include "Node234.h"
#include <stack>

class Tree234Iterator {
private:
   struct Frame {
      Node234* node;
      int keyIndex;
   };

   Node234* currentNode;
   int keyIndex;
   std::stack<Frame> pending;

public:
   Tree234Iterator(Node234* root) {
      if (root == nullptr) {
         currentNode = nullptr;
         keyIndex = -1;
      }
      else {
         currentNode = root;

         // Walk to the minimum key, storing the next key to visit
         // in each ancestor along the way.
         while (currentNode->GetChild(0) != nullptr) {
            pending.push({currentNode, 0});
            currentNode = currentNode->GetChild(0);
         }

         keyIndex = 0;
      }
   }

   Tree234Iterator(const Tree234Iterator& toCopy) {
      currentNode = toCopy.currentNode;
      keyIndex = toCopy.keyIndex;
      pending = toCopy.pending;
   }

   Tree234Iterator& operator=(const Tree234Iterator& other) {
      currentNode = other.currentNode;
      keyIndex = other.keyIndex;
      pending = other.pending;
      return *this;
   }

   bool operator==(const Tree234Iterator& other) const {
      return currentNode == other.currentNode && keyIndex == other.keyIndex;
   }

   bool operator!=(const Tree234Iterator& other) const {
      return !(*this == other);
   }

   int operator*() const {
      return currentNode->GetKey(keyIndex);
   }

   Tree234Iterator& operator++() {
      if (currentNode == nullptr) {
         return *this;
      }

      // Case 1: go into the subtree to the right of the current key.
      Node234* rightSubtree = currentNode->GetChild(keyIndex + 1);
      if (rightSubtree != nullptr) {
         // After that subtree is exhausted, the next key in this node
         // (if one exists) must be visited.
         if (keyIndex + 1 < currentNode->GetKeyCount()) {
            pending.push({currentNode, keyIndex + 1});
         }

         currentNode = rightSubtree;

         // Walk to the leftmost key in that subtree, storing ancestor
         // keys that must be visited later.
         while (currentNode->GetChild(0) != nullptr) {
            pending.push({currentNode, 0});
            currentNode = currentNode->GetChild(0);
         }

         keyIndex = 0;
         return *this;
      }

      // Case 2: no right subtree, but another key exists in this node.
      if (keyIndex + 1 < currentNode->GetKeyCount()) {
         keyIndex++;
         return *this;
      }

      // Case 3: use the stored collection instead of re-visiting ancestors.
      if (!pending.empty()) {
         Frame next = pending.top();
         pending.pop();
         currentNode = next.node;
         keyIndex = next.keyIndex;
         return *this;
      }

      // No more keys remain.
      currentNode = nullptr;
      keyIndex = -1;
      return *this;
   }
};

#endif