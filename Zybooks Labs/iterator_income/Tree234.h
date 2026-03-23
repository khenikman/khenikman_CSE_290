#ifndef TREE234_H
#define TREE234_H

#include <iostream>
#include <stack>
#include <string>
#include "Node234.h"

template<typename IteratorType>
class Tree234 {
protected:
   Node234* root;
   
   // Allocates a node given one key and two optional children.
   virtual Node234* AllocNode(int key, Node234* child0 = nullptr,
      Node234* child1 = nullptr) {
      return new Node234(key, child0, child1);
   }
   
   // Allocates a node given three keys and four children.
   virtual Node234* AllocNode(int key0, int key1, int key2, Node234* child0,
      Node234* child1, Node234* child2, Node234* child3) {
      return new Node234(key0, key1, key2, child0, child1, child2, child3);
   }
   
   // Recursively deletes the node's children, then deletes the node itself.
   void DeleteTree(Node234* node) {
      if (node != nullptr) {
         // Delete all child subtrees first
         for (int i = 0; i <= node->GetKeyCount(); i++) {
            DeleteTree(node->GetChild(i));
         }
         
         // Delete the node itself
         delete node;
      }
   }
        
   // Fuses a parent node and two children into one node. 
   // Precondition: leftNode and rightNode must have one key each.
   Node234* Fuse(Node234* parent, Node234* leftNode, Node234* rightNode) {
      if (parent == root && parent->GetKeyCount() == 1) {
         return FuseRoot();
      }

      int leftNodeIndex = parent->GetChildIndex(leftNode);
      int middleKey = parent->GetKey(leftNodeIndex);
      Node234* fusedNode = AllocNode(
         // Keys:
         leftNode->GetKey(0), middleKey, rightNode->GetKey(0),

         // Children:
         leftNode->GetChild(0), leftNode->GetChild(1),
         rightNode->GetChild(0), rightNode->GetChild(1)
      );
      delete leftNode;
      delete rightNode;
      int keyIndex = parent->GetKeyIndex(middleKey);
      parent->RemoveKey(keyIndex);
      parent->SetChild(keyIndex, fusedNode);
      return fusedNode;
   }

   // Fuses the tree's root node with the root's two children. 
   // Precondition: Each of the three nodes must have one key each.
   Node234* FuseRoot() {
      Node234* oldChild0 = root->GetChild(0);
      Node234* oldChild1 = root->GetChild(1);
      root->SetKey(1, root->GetKey(0));
      root->SetKey(0, oldChild0->GetKey(0));
      root->SetKey(2, oldChild1->GetKey(0));
      root->SetKeyCount(3);
      root->SetChild(0, oldChild0->GetChild(0));
      root->SetChild(1, oldChild0->GetChild(1));
      root->SetChild(2, oldChild1->GetChild(0));
      root->SetChild(3, oldChild1->GetChild(1));
      delete oldChild0;
      delete oldChild1;
      return root;
   }
   
   int GetHeight(Node234* node) const {
      if (node->GetChild(0) == nullptr) {
         return 0;
      }
      return 1 + GetHeight(node->GetChild(0));
   }

   // Searches for, and returns, the minimum key in a subtree. The node
   // argument must be non-null.
   int GetMinKey(Node234* node) const {
      Node234* current = node;
      while (current->GetChild(0)) {
         current = current->GetChild(0);
      }
      return current->GetKey(0);
   }
   
   // Finds and replaces one key with another. The replacement key must
   // be known to be a key that can be used as a replacement without violating
   // any of the 2-3-4 tree rules.
   bool KeySwap(Node234* node, int existingKey, int replacementKey) {
      if (node == nullptr) {
         return false;
      }

      int keyIndex = node->GetKeyIndex(existingKey);
      if (keyIndex == -1) {
         Node234* next = node->NextNode(existingKey);
         return KeySwap(next, existingKey, replacementKey);
      }

      node->SetKey(keyIndex, replacementKey);
      return true;
   }
   
   // Rotates or fuses to add 1 or 2 additional keys to a node with 1 key.
   Node234* Merge(Node234* node, Node234* nodeParent) {
      // Get pointers to node's siblings
      int nodeIndex = nodeParent->GetChildIndex(node);
      Node234* leftSibling = nodeParent->GetChild(nodeIndex - 1);
      Node234* rightSibling = nodeParent->GetChild(nodeIndex + 1);
    
      // Check siblings for a key that can be transferred
      if (leftSibling && leftSibling->GetKeyCount() >= 2) {
         RotateRight(leftSibling, nodeParent);
      }
      else if (rightSibling && rightSibling->GetKeyCount() >= 2) {
         RotateLeft(rightSibling, nodeParent);
      }
      else { // fuse
         if (leftSibling == nullptr) {
            node = Fuse(nodeParent, node, rightSibling);
         }
         else {
            node = Fuse(nodeParent, leftSibling, node);
         }
      }

      return node;
   }
   
   // Prints all keys in the tree rooted at node in ascending order.
   void PrintRecursive(Node234* node, std::ostream& output,
      std::string separator, bool& printedFirst) const {
      
      if (nullptr == node) {
         return;
      }
      
      for (int i = 0; i < node->GetKeyCount(); i++) {
         // First print the child subtree to the left of the key
         PrintRecursive(node->GetChild(i), output, separator, printedFirst);
         
         // If the first key was already printed the print the separator
         if (printedFirst) {
            output << separator;
         }
         else {
            printedFirst = true;
         }
         
         // Print the key at index i
         output << node->GetKey(i);
      }
      
      // Print the final subtree to the right of the node's last key
      PrintRecursive(node->GetChild(node->GetKeyCount()), output, separator,
         printedFirst);
   }
   
   void RotateLeft(Node234* node, Node234* nodeParent) {
      // Get the node's left sibling
      int nodeIndex = nodeParent->GetChildIndex(node);
      Node234* leftSibling = nodeParent->GetChild(nodeIndex - 1);

      // Append the key to the left sibling
      leftSibling->InsertKeyWithChildren(nodeParent->GetKey(nodeIndex - 1),
         leftSibling->GetChild(leftSibling->GetKeyCount()), node->GetChild(0));

      // Replace the parent's key that was appended to the left sibling
      nodeParent->SetKey(nodeIndex - 1, node->GetKey(0));

      // Remove key 0 and child 0 from node
      node->RemoveKey(0);
   }
    
   void RotateRight(Node234* node, Node234* nodeParent) {
      // Get the node's right sibling
      int nodeIndex = nodeParent->GetChildIndex(node);
      Node234* rightSibling = nodeParent->GetChild(nodeIndex + 1);
      
      // Get the child from the node that will move to the sibling
      Node234* nodeRightmostChild = node->GetChild(node->GetKeyCount());
        
      // Get the key from the parent that move into the right sibling
      int keyForRightSibling = nodeParent->GetKey(nodeIndex);
      
      // Insert new key and child into right sibling
      rightSibling->InsertKeyWithChildren(keyForRightSibling,
         nodeRightmostChild, rightSibling->GetChild(0));
      
      // Replace the parent's key that moved to the right sibling
      nodeParent->SetKey(nodeIndex, node->GetKey(node->GetKeyCount() - 1));
      
      // Remove node's rightmost key and child
      node->SetChild(node->GetKeyCount(), nullptr);
      node->SetKeyCount(node->GetKeyCount() - 1);
   }
   
   // Searches this tree for the specified key. If found, the node containing
   // the key is returned. Otherwise null is returned.
   Node234* Search(int key) const {
      return SearchRecursive(key, root);
   }
   
   // Recursive helper function for search.
   Node234* SearchRecursive(int key, Node234* node) const {
      if (node == nullptr) {
         return nullptr;
      }
            
      // Check if the node contains the key
      if (node->HasKey(key)) {
         return node;
      }
        
      // Recursively search the appropriate subtree
      return SearchRecursive(key, node->NextNode(key));
   }
   
   // Splits a full node, moving the middle key up into the parent node.
   // Precondition: nodeParent has one or two keys.
   Node234* Split(Node234* node, Node234* nodeParent) {
      Node234* splitLeft = AllocNode(node->GetKey(0), node->GetChild(0),
         node->GetChild(1));
      Node234* splitRight = AllocNode(node->GetKey(2), node->GetChild(2),
         node->GetChild(3));
      
      if (nodeParent) {
         // Split non-root node
         nodeParent->InsertKeyWithChildren(node->GetKey(1), splitLeft,
            splitRight);
         delete node;
      }
      else {
         // Split root node
         nodeParent = AllocNode(node->GetKey(1), splitLeft, splitRight);
         delete root;
         root = nodeParent;
      }
        
      return nodeParent;
   }

public:
   // Initializes the tree by assigning the root node pointer with nullptr.
   Tree234() {
      root = nullptr;
   }
   
   virtual ~Tree234() {
      DeleteTree(root);
   }
   
   // Returns true if this tree contains the key, false otherwise.
   bool ContainsKey(int key) const {
      return SearchRecursive(key, root) != nullptr;
   }
   
   // Inserts a new key into this tree, provided the tree doesn't already
   // contain the same key. Returns true if the key was inserted successfully,
   // false if the key already exists and so was not inserted.
   bool Insert(int key) {
      return Insert(key, root, nullptr);
   }

   // Inserts a new key into this tree, provided the tree doesn't already
   // contain the same key. Returns true if the key was inserted successfully,
   // false if the key already exists and so was not inserted.
   bool Insert(int key, Node234* node, Node234* nodeParent) {
      // Special case for empty tree
      if (root == nullptr) {
         root = AllocNode(key);
         return true;
      }

      // Check for duplicate key
      if (node->HasKey(key)) {
         // Duplicate keys are not allowed
         return false;
      }

      // Preemptively split full nodes
      if (node->GetKeyCount() == 3) {
         node = Split(node, nodeParent);
      }

      // If node is not a leaf, recursively insert into child subtree
      if (!node->IsLeaf()) {
         return Insert(key, node->NextNode(key), node);
      }
        
      // key can be inserted into leaf node
      node->InsertKeyWithChildren(key, nullptr, nullptr);
      return true;
   }
   
   // Returns the height of this tree.
   int GetHeight() {
      return GetHeight(root);
   }
   
   // Returns the number of keys in this tree.
   int GetLength() const {
      int count = 0;
      std::stack<Node234*> nodes;
      nodes.push(root);
      
      while (!nodes.empty()) {
         Node234* node = nodes.top();
         nodes.pop();
         if (node) {
            // Add the number of keys in the node to the count
            count = count + node->GetKeyCount();
                
            // Push children
            for (int i = 0; i <= node->GetKeyCount(); i++) {
               nodes.push(node->GetChild(i));
            }
         }
      }
      return count;
   }
   
   void PrintKeys(std::ostream& output, std::string separator = ",") const {
      bool printedFirst = false;
      PrintRecursive(root, output, separator, printedFirst);
   }

   // Finds and removes the specified key from this tree.
   bool Remove(int key) {
      // Special case for tree with 1 key
      if (root->IsLeaf() && root->GetKeyCount() == 1) {
         if (root->GetKey(0) == key) {
            delete root;
            root = nullptr;
            return true;
         }
         return false;
      }

      Node234* currentParent = nullptr;
      Node234* current = root;
      while (current) {
         // Merge any non-root node with 1 key
         if (current->GetKeyCount() == 1 && current != root) {
            current = Merge(current, currentParent);
         }

         // Check if current node contains key
         int keyIndex = current->GetKeyIndex(key);
         if (keyIndex != -1) {
            if (current->IsLeaf()) {
               current->RemoveKey(keyIndex);
               return true;
            }

            // The node contains the key and is not a leaf, so the key is
            // replaced with the successor
            Node234* tmpChild = current->GetChild(keyIndex + 1);
            int tmpKey = GetMinKey(tmpChild);
            Remove(tmpKey);
            KeySwap(root, key, tmpKey);
            return true;
         }

         // Current node does not contain key, so continue down tree
         currentParent = current;
         current = current->NextNode(key);
      }

      // key not found
      return false;
   }
   
   // Added to support range-based for loops. IteratorType is a template type
   // for the iterator, and will be Tree234Iterator when grading submitted code.
   virtual IteratorType begin() const {
      return IteratorType(root);
   }
      
   virtual IteratorType end() const {
      return IteratorType(nullptr);
   }
};

#endif
