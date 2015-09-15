//Ken Schroeder
//January 31, 2015
//Implement a Binary Search Tree
//File: BST.cpp

#include "BST.h"

//-------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------
BST::BST(){
  head = NULL;
  size = 0;
}

//-------------------------------------------------------------------------
// Deconstructor
// ------------------------------------------------------------------------
BST::~BST(){
  clearTree(head);
}

//-------------------------------------------------------------------------
// clearTree
// Removes pointers and deletes nodes
//-------------------------------------------------------------------------
void BST::clearTree(BSTNode* b){
  if (b != NULL){
    clearTree(b->left);
    clearTree(b->right);
    delete b;
    b = NULL;
  }
}

//-------------------------------------------------------------------------
// insert
// creates a node and inserts into tree
// note that a number cannot be inserted twice
// ------------------------------------------------------------------------
bool BST::insert(int n){
  if (isInTree(n)){
    return false;
  }
	
  if (head == NULL){
    BSTNode* root = new BSTNode;
    root->left = NULL;
    root->right = NULL;
    root->data = n;
    head = root;
    size++;
  }
  else{
    addToTree(n, head);
  }
  
  return true;
}

//-------------------------------------------------------------------------
// addToTree
// private helper for insert function
// ------------------------------------------------------------------------
void BST::addToTree(int n, BSTNode* root){
  if (n < root->data){
    if (root->left == NULL){
      BSTNode* add = new BSTNode;
      add->data = n;
      add->left = NULL;
      add->right = NULL;
      root->left = add;
      size++;
    }
    else{
      addToTree(n,root->left);
    }	
  }
  else{
    if (root->right == NULL){
      BSTNode* add = new BSTNode;
      add->data = n;
      add->right = NULL;
      add->left = NULL;
      root->right = add;
      size++;
    }
    else{
      addToTree(n,root->right);
    }
  }
}

//-------------------------------------------------------------------------
// remove
// finds if a value num is in tree and removes node that contains it
// ------------------------------------------------------------------------
bool BST::remove(int n){
  if (!isInTree(n)){
    return false;
  }
  size--;
   removeFromTree(n,head);
  return true;
}

//-------------------------------------------------------------------------
// removeFromTree
// attempts to remove a node and free memory
// ------------------------------------------------------------------------
void BST::removeFromTree(int n, BSTNode* root){
  BSTNode* current = root;
  BSTNode* parent = 0;
  while (current != 0){
    if (current->data == n){
      break;
    }
    else{
      parent = current;
      if (n < current->data){
	      current = current->left;
      }
      else{
         current = current->right;
      }
    }
  }

  //Node with no children
  if (current->left == NULL && current->right == NULL){
    if (parent->left = current){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
    delete current;
    return;
  }

  //Node with left child
  if (current->left == NULL){
    if (parent->left == current){
      parent->left = current->right;
    }
    else{
      parent->right = current->right;
    }
  }
  else{
    if (parent->left == current){
      parent->left = current->left;
    }
    else{
      parent->right = current->left;
    }
  }
}
  //still need two children, replace with smallest node in right subtree

	
//-------------------------------------------------------------------------
// isInTree
// returns true if a number is already contained in a tree
// helper function for insert and removal functions
// ------------------------------------------------------------------------
bool BST::isInTree(int n){
  return isInTree(n,head);
}

//-------------------------------------------------------------------------
// isInTree
// private function corresponding to public function
// returns true if a number is already contained in a tree
// helper function for insert and removal functions
// ------------------------------------------------------------------------
bool BST::isInTree(int n, BSTNode* root){
  if (root != NULL){ 
    if (root->data == n){
      return true;
    }
    else if (n < root->data){
      return isInTree(n,root->left);
    }
    else{
      return isInTree(n,root->right);
    }
  }
  return false;
}

//-------------------------------------------------------------------------
// getHeight
// public function to return height of tree
//-------------------------------------------------------------------------
int BST::getHeight(){
   return getHeight(head);
}

//-------------------------------------------------------------------------
// getHeight
// private function to return height of tree
//-------------------------------------------------------------------------
int BST::getHeight(BSTNode* root){
   int leftHeight = 0;
   int rightHeight = 0;
   if (root->left != NULL){
      leftHeight = getHeight(root->left);
   }
   if (root->right != NULL){
      rightHeight = getHeight(root->right);
   }
   if (leftHeight > rightHeight){
      return leftHeight + 1;
   }
   else{
      return rightHeight + 1;
   }
}

//-------------------------------------------------------------------------
// numberOfNodes
// returns number of nodes in tree
//-------------------------------------------------------------------------
int BST::numberOfNodes(){
   return numberOfNodes(head);
}

int BST::numberOfNodes(BSTNode* root){
   int nodes =0;
   if (root != NULL){
      nodes = 1 + numberOfNodes(root->left) + numberOfNodes(root->right);     
   }
   return nodes;
   
   /*
   if (root->left != NULL){
      nodes = numberOfNodes(root->left) + 1;
   }
   if (root->right != NULL){
      rightNodes = numberOfNodes(root->right) + 1;
   }
   
   return leftNodes + rightNodes + 1;
*/
}

//-------------------------------------------------------------------------
// inOrderPrint
// public function of in-order print traversal
// ------------------------------------------------------------------------
void BST::inOrderPrint(){
  cout << "In Order Print: ";
  inOrderPrint(head);
}

//-------------------------------------------------------------------------
// inOrderPrint
// private helper function of public in-order traversal
// ------------------------------------------------------------------------
void BST::inOrderPrint(BSTNode* b){
  if (b != NULL){
    inOrderPrint(b->left);
    cout << b->data << " ";
    inOrderPrint(b->right);
  }
}

//-------------------------------------------------------------------------
// preOrderPrint
// public function of pre-order print traversal
// ------------------------------------------------------------------------
void BST::preOrderPrint(){
  cout << "Pre Order Print: ";
  preOrderPrint(head);
}

//-------------------------------------------------------------------------
// preOrderPrint
// private helper function of public pre-order traversal
// ------------------------------------------------------------------------
void BST::preOrderPrint(BSTNode* b){
  if (b != NULL){
    cout << b->data << " ";
    preOrderPrint(b->left);
    preOrderPrint(b->right);
  }
}

//-------------------------------------------------------------------------
// postOrderPrint
// public function of post-order print traversal
// ------------------------------------------------------------------------
void BST::postOrderPrint(){
  cout << "Post Order Print: ";
  postOrderPrint(head);
}

//-------------------------------------------------------------------------
// postOrderPrint
// private helper function of public post-order traversal
// ------------------------------------------------------------------------
void BST::postOrderPrint(BSTNode* b){
  if (b!= NULL){
    inOrderPrint(b->left);
    inOrderPrint(b->right);
    cout << b->data << " ";
  }
}




