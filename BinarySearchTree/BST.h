//Ken Schroeder
//January 31, 2015
//Implement a Binary Search Tree
//File: BST.h
//*http://cslibrary.stanford.edu/110/BinaryTrees.pdf

//Posible that remove doesn't work correctly?
//Jive titles with AVL Tree

#ifndef BST_H
#define BST_H

#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// Binary Search Tree (BST)
// includes the following features:
// --insert
// --remove
// --tree traversals (in order, pre order, post order)
// --search (returns a bool)
// --count
// --tree height
//
// implementation and assumptions:
// --only numbers will be attempted to be inserted into the BST
// --all numbers in BST are unique, that is, a number cannot
//   -be inserted twice
//
// future considerations
// --make it a template
// --print out the tree
// --maxDepth()
// --size()
//-------------------------------------------------------------------------

struct BSTNode{
   BSTNode* left;
   BSTNode* right;
   int data;
};

class BST{
 private:
  //member variables
  BSTNode* head;
  int size;
	//deconstructor
  void clearTree(BSTNode* b);
	//insert
  void addToTree(int, BSTNode*);
	//remove
  void removeFromTree(int, BSTNode*);
	//tree traversals
  void inOrderPrint(BSTNode*);
  void preOrderPrint(BSTNode*);
  void postOrderPrint(BSTNode*);
	//find
  bool isInTree(int, BSTNode*);
	//accessors
  int getHeight(BSTNode*);
  int numberOfNodes(BSTNode*);
  //int getHeight() const;
  //int numberOfNodes();
  
 public:
  BST();
  //BST(const BST&);
  ~BST();
  bool insert(int);
  bool remove(int);
  bool isInTree(int);
  int getSize();
  int getHeight();
  int numberOfNodes();
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
};
#endif
