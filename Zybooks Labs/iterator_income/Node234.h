#ifndef NODE234_H
#define NODE234_H

// Node234 class - represents a node in a 2-3-4 tree
class Node234 {
protected:
   int keys[3];
   int keyCount;
   Node234* children[4];

public:
   // Constructs a Node234 object from a key and two optional child pointers.
   Node234(int key0, Node234* child0 = nullptr, Node234* child1 = nullptr) {
      keys[0] = key0;
      keys[1] = 0;
      keys[2] = 0;
      keyCount = 1;
      children[0] = child0;
      children[1] = child1;
      children[2] = nullptr;
      children[3] = nullptr;
   }
   
   // Constructs a node with three keys and four children.
   Node234(int key0, int key1, int key2, Node234* child0, Node234* child1,
      Node234* child2, Node234* child3) {
      
      keys[0] = key0;
      keys[1] = key1;
      keys[2] = key2;
      keyCount = 3;
      children[0] = child0;
      children[1] = child1;
      children[2] = child2;
      children[3] = child3;
   }
   
   virtual ~Node234() {
   }
    
   // If childIndex is >= 0 and <= keyCount then the child at childIndex is
   // returned. Otherwise nullptr is returned.
   virtual Node234* GetChild(int childIndex) {
      if (childIndex >= 0 && childIndex <= keyCount) {
         return children[childIndex];
      }
      return nullptr;
   }

   // Returns 0, 1, 2, or 3 if the child argument is this node's child 0,
   // child 1, child 2, or child 3, respectively.
   // Returns -1 if the child argument is not a child of this node.
   virtual int GetChildIndex(Node234* child) {
      for (int i = 0; i < 4; i++) {
         if (children[i] == child) {
            return i;
         }
      }
      return -1;
   }

   // Returns the key at keyIndex.
   virtual int GetKey(int keyIndex) {
      return keys[keyIndex];
   }
   
   // Returns the number of keys in this node, which will be 1, 2, or 3.
   virtual int GetKeyCount() {
      return keyCount;
   }

   // Returns the index of the key within this node, or -1 if this node does
   // not contain the key.
   virtual int GetKeyIndex(int key) {
      for (int i = 0; i < keyCount; i++) {
         if (keys[i] == key) {
            return i;
         }
      }
      return -1;
   }
   
   // Returns true if this node has the specified key, false otherwise.
   virtual bool HasKey(int key) {
      return (key == keys[0] || (keyCount > 1 && key == keys[1]) ||
         (keyCount > 2 && key == keys[2]));
   }
   
   // Inserts a new key into the proper location in this node, and assigns the
   // children on either side of the inserted key.
   // Precondition: This node's key count is <= 2.
   virtual void InsertKeyWithChildren(int key, Node234* leftChild,
      Node234* rightChild) {
      if (key < keys[0]) {
         keys[2] = keys[1];
         keys[1] = keys[0];
         keys[0] = key;
         children[3] = children[2];
         children[2] = children[1];
         children[1] = rightChild;
         children[0] = leftChild;
      }
      else if (keyCount == 1 || key < keys[1]) {
         keys[2] = keys[1];
         keys[1] = key;
         children[3] = children[2];
         children[2] = rightChild;
         children[1] = leftChild;
      }
      else {
         keys[2] = key;
         children[3] = rightChild;
         children[2] = leftChild;
      }
      keyCount++;
   }

   // Returns true if this node is a leaf, false otherwise.
   virtual bool IsLeaf() {
      return children[0] == nullptr;
   }

   // Returns the child of this node that must be visited next in the
   // traversal to find the specified key
   virtual Node234* NextNode(int key) {
      int i;
      for (i = 0; i < keyCount; i++) {
         if (key < keys[i]) {
            return children[i];
         }
      }
      return children[i];
   }

   // Removes key 0, 1, or 2 from this node, if keyIndex is 0, 1, or 2,
   // respectively. Other keys and children are shifted as needed.
   virtual void RemoveKey(int keyIndex) {
      if (keyIndex == 0) {
         keys[0] = keys[1];
         keys[1] = keys[2];
         children[0] = children[1];
         children[1] = children[2];
         children[2] = children[3];
         children[3] = nullptr;
         keyCount--;
      }
      else if (keyIndex == 1) {
         keys[1] = keys[2];
         children[2] = children[3];
         children[3] = nullptr;
         keyCount--;
      }
      else if (keyIndex == 2) {
         children[3] = nullptr;
         keyCount--;
      }
   }

   // Sets a child by index.
   virtual void SetChild(int childIndex, Node234* child) {
      children[childIndex] = child;
   }

   // Sets a key by index.
   virtual void SetKey(int keyIndex, int keyValue) {
      keys[keyIndex] = keyValue;
   }
   
   // Sets this node's key count.
   virtual void SetKeyCount(int newKeyCount) {
      keyCount = newKeyCount;
   }
};

#endif