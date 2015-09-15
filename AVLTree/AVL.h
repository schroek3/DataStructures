//Ken Schroeder
//January 31, 2015
//Implement an AVL Tree
//File: AVL.h

#ifndef AVL_h
#define AVL_h

#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// AVL Tree
// includes the following features:
// --insert
// --remove
// --tree traversals (in order, pre order, post order)
// --search (returns a bool)
//
// implementation and assumptions:
// --only numbers will be attempted to be inserted into AVL Tree
// --all numbers in AVL tree are unique, that is, a number cannot
//   -be inserted twice
//
// future considerations
// --make it a template
// --print out the tree
//-------------------------------------------------------------------------


//template <class T>

struct AVLNode{
  int data;
  //T data;
  int balance;
  AVLNode* left;
  AVLNode* right;
  AVLNode* parent;
};

//template <class T>
class AVL{
  public: 
    AVL();
    ~AVL();
    //bool insert(T data);
    //void delete(const T key);
    bool insert(int data);
    bool remove(int data);
    bool search(int data);
    void printTree();
    void testOrderPrint();
		void preOrderPrint();
		void inOrderPrint();
		void postOrderPrint();
  private:
//    AVLNode<T>* root;
		//Member Variables
    int size; 
    AVLNode* root;
		
		//rotations
    AVLNode* rotateLeft (AVLNode*);
    AVLNode* rotateRight (AVLNode*);
    AVLNode* rotateLeftThenRight(AVLNode*);
    AVLNode* rotateRightThenLeft(AVLNode*);
		
		//balancing functions
    void rebalance(AVLNode*);
    int height (AVLNode*);
    void setBalance(AVLNode*);
    void printBalance(AVLNode*);
		
		//removal functions
    AVLNode* findPredecessor(AVLNode*);
    AVLNode* minimum(AVLNode*);
    AVLNode* maximum(AVLNode*);
    void deleteNode(AVLNode* n);
    void clearNode(AVLNode*);
		AVLNode* find(AVLNode*, int);
		
		//search/insertion functions
    bool isInTree(int, AVLNode*);
    void addToTree(AVLNode*, AVLNode*);
    
		//print functions
		void testOrderPrint(AVLNode*);
	  void preOrderPrint(AVLNode*);
		void inOrderPrint(AVLNode*);
		void postOrderPrint(AVLNode*);
		
		//Deconstructor helper
		void clearTree(AVLNode*);
};
#endif
