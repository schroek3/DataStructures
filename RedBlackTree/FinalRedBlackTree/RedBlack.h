//Ken Schroeder
//January 28, 2015
//CSS502
//Implement a Red Black Tree
//File: RedBlack.h

#ifndef RedBlack_h
#define RedBlack_h

#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// RedBlack Tree
// includes the following features:
// --insert
// --remove
// --tree traversals (in order, pre order, post order)
// --search (returns a bool)
//
// implementation and assumptions:
// --only numbers will be attempted to be inserted into RedBlack Tree
// --all numbers in red-black tree are unique, that is, a number cannot
//   -be inserted twice
//-------------------------------------------------------------------------


//Red-Black Tree Node Struct
struct RedBlackNode{
  int data;
  bool red;   //True if red, false if black
  RedBlackNode* left;
  RedBlackNode* right;
  RedBlackNode* parent;
};

class RedBlack{
 private:
  RedBlackNode* root;
  
  void clearTree(RedBlackNode* r);
  
	//insertion functions
  void addToTree(RedBlackNode*, RedBlackNode*);
  bool isInTree(int,RedBlackNode*);
  
	void setAsRoot(RedBlackNode*);
	void insertChildNode(RedBlackNode*, RedBlackNode*);
  void insertCase1(RedBlackNode*);
  void insertCase2(RedBlackNode*);
  void insertCase3(RedBlackNode*);
  void insertCase4(RedBlackNode*);
  void insertCase5(RedBlackNode*);
  
	//deletion functions
	void linkChild(RedBlackNode*, RedBlackNode*);
  void deleteNode(RedBlackNode*);
  void deleteCase1(RedBlackNode*);
  void deleteCase2(RedBlackNode*);
  void deleteCase3(RedBlackNode*);
  void deleteCase4(RedBlackNode*);
  void deleteCase5(RedBlackNode*);
	void deleteCase5Helper(RedBlackNode*, RedBlackNode*);
  void deleteCase6(RedBlackNode*);
	void deleteCase6Helper(RedBlackNode*, RedBlackNode*);
  
	//rotations
  void rotateLeft(RedBlackNode*);
  void rotateRight(RedBlackNode*);
	void replaceNode(RedBlackNode*, RedBlackNode*);
  
	//family members
  RedBlackNode* grandparent(RedBlackNode*);
  RedBlackNode* uncle(RedBlackNode*);
  RedBlackNode* sibling(RedBlackNode*);
  
	//print traversals
  void inOrderPrint(RedBlackNode*);
  void preOrderPrint(RedBlackNode*);
  void postOrderPrint(RedBlackNode*);
  void testPrint(RedBlackNode*);
  
	//search helpers
  RedBlackNode* find(RedBlackNode*, int);    
  bool privateSearch(RedBlackNode*, int); 
  
	//predecessors
  RedBlackNode* findPredecessor(RedBlackNode*);
  RedBlackNode* minimum(RedBlackNode*);
  RedBlackNode* maximum(RedBlackNode*);
  
	//free node
  void freeNode(RedBlackNode*);
	void removeNode(RedBlackNode*);
  
 public:
  RedBlack();
  ~RedBlack();
  bool insert(int);
  void remove(int);
  
  bool search(int);                            
  
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
  void testPrint();
};
#endif
