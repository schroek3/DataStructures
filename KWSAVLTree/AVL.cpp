//Ken Schroeder
//January 31, 2015
//Implement an AVL tre
//File: AVL.cpp

#include "AVL.h"

//-------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------
AVL::AVL(){
  root = NULL;
}

//-------------------------------------------------------------------------
// Deconstructor
// ------------------------------------------------------------------------
AVL::~AVL(){
  if (root != NULL){
    clearTree(root);
  }
}

//-------------------------------------------------------------------------
// clearTree
// Removes pointers and deletes nodes
//-------------------------------------------------------------------------
void AVL::clearTree(AVLNode* n){
  if (n != NULL){
    n->parent = NULL;
    clearTree(n->left);
    clearTree(n->right);
    delete n; 
    n = NULL;
  }
}

//-------------------------------------------------------------------------
// insert
// creates a node and inserts into tree
// note that a number cannot be inserted twice
// balancing is done after node is inserted
// ------------------------------------------------------------------------
bool AVL::insert(int num){
  if (isInTree(num, root)){
    return false;
  }
    AVLNode* n = new AVLNode;
    n->data = num;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->balance = 0;
  
  if (root == NULL){
    root = n;
    size++;
  }
  else{
    addToTree(n, root);
  }
  
  rebalance(n);
  
  return true;
}

//-------------------------------------------------------------------------
// addToTree
// private helper for insert function
// find correct location in the tree, and then balance using setBalance()
// ------------------------------------------------------------------------
void AVL::addToTree(AVLNode* n, AVLNode* head){
  if (n->data < head->data){
    if (head->left == NULL){
      head->left = n;
      n->parent = head;
    }
    else{
      addToTree(n,head->left);
    }
  }
  else{
    if (head->right == NULL){
      head->right = n;
      n->parent = head;      
    }
    else{
      addToTree(n, head->right);
    }
  }
}

//-------------------------------------------------------------------------
// isInTree
// returns true if a number is already contained in a tree
// helper function for insert and removal functions
// ------------------------------------------------------------------------
bool AVL::isInTree(int num, AVLNode* head){
  if (head != NULL){
    if (head->data == num){
      return true;
    }
    else if (num < head->data){
      return isInTree(num, head->left);
    }
    else{
      return isInTree(num, head->right);
    }
  }
  return false;
}

//-------------------------------------------------------------------------
// rebalance
// determines if tree is unbalanced
// if tree is unbalanced, performs proper rotations
// ------------------------------------------------------------------------
void AVL::rebalance(AVLNode* n){
  setBalance(n);
  
  if (n->balance == -2){
    if(height(n->left->left) >= height(n->left->right)){
      n = rotateRight(n);
    }
    else{
      n = rotateLeftThenRight(n);
    }
  }
  else if (n->balance == 2){
    if (height(n->right->right) >= height(n->right->left)){
      n = rotateLeft(n);
    }
    else{
      n = rotateRightThenLeft(n);
    }
  }
  
  if (n->parent != NULL){
    rebalance(n->parent);
  }
  else{
    root = n;
  }
}
//-------------------------------------------------------------------------
// setBalance
// sets balance factor for node in tree
// balance factor = max height of right subtree - max height of left subtree
// ------------------------------------------------------------------------
void AVL::setBalance(AVLNode* n){
  n->balance = height(n->right) - height(n->left);
}

//-------------------------------------------------------------------------
// height
// returns maximum of height of left subtree and right subtree
// used to help determine if tree is unbalanced at any node
// ------------------------------------------------------------------------
int AVL::height(AVLNode* n){
  if (n == NULL){
    return -1;
  }
    return 1 + max(height(n->left), height(n->right));
}

//-------------------------------------------------------------------------
// rotateLeft
// performs left rotation on the node
// ------------------------------------------------------------------------
AVLNode* AVL::rotateLeft(AVLNode* n){
  AVLNode* y = n->right;              //y = x->right
  AVLNode* leftOfY = y->left;         //y's left subtree
  AVLNode* p = n->parent;             //x's parent
  
  n->right = leftOfY;
  if (leftOfY != NULL){
    leftOfY->parent = n;
  }

  y->parent = p;
  
  if (y->parent == NULL){
    root = y;
  }
  else if (n == p->left){
    p->left = y;
  }
  else{
    p->right = y;
  }
  
  y->left = n;
  n->parent = y;

  
  
  setBalance(n);
  setBalance(y);
  
  return y;
}
  
/* 
  AVLNode* b = n->right;
  b->parent = n->parent;
  n->right = b->left;
  
  if (n->right != NULL){
    n->right->parent = n;
  }
  
  b->left = n;
  n->parent = b;


  if (b->parent != NULL){
    if (b->parent->right == n){
      b->parent->right = b;
    }
    else{
      b->parent->left = b;
    }
  }
  
  setBalance(n);
  setBalance(b);
  
  return b;
}
  */
	
//-------------------------------------------------------------------------
// rotateRight
// performs left rotation on the node
// ------------------------------------------------------------------------
AVLNode* AVL::rotateRight(AVLNode* n){
  AVLNode* y = n->left;
  AVLNode* rightOfY = y->right;
  AVLNode* p = n->parent;
  
  n->left = rightOfY;
  if (rightOfY != NULL){
    rightOfY->parent = n;
  }

  y->parent = p;  
  if (y->parent == NULL){
    root = y;
  }
  else if(n == p->right){
    p->right = y;
  }
  else{
    p->left = y;
  }
  
  y->right = n;
  n->parent = y;

  
  setBalance(n);
  setBalance(y);
  
  return y;
}
  
  /*
AVLNode* AVL::rotateRight(AVLNode* n){
  AVLNode* b = n->left;
  b->parent = n->parent;
  n->left = b->right;
  
  if (n->left != NULL){
    n->left->parent = n;
  }
  
  b->right = n;
  n->parent = b;
  
  if(b->parent != NULL){
    if (b->parent->right == n){
      b->parent->right = b;
    }
    else{
      b->parent->left = b;
    }
  }

  setBalance(n);
  setBalance(b);

  return b;
}
*/

//-------------------------------------------------------------------------
// rotateLeftThenRight
// performs two rotations on a node
// used if parent node has a balance factor of -2 and child node has a 
//  -balance factor of 1
// ------------------------------------------------------------------------
AVLNode* AVL::rotateLeftThenRight(AVLNode* n){
  n->left = rotateLeft(n->left);
  return rotateRight(n);
}

//-------------------------------------------------------------------------
// rotateLeftThenRight
// performs two rotations on a node
// used if parent node has a balance factor of 2 and child node has a 
//  -balance factor of -1
// ------------------------------------------------------------------------
AVLNode* AVL::rotateRightThenLeft(AVLNode* n){
  n->right = rotateRight(n->right);
  return rotateLeft(n);
}

//-------------------------------------------------------------------------
// remove
// finds if a value num is in tree and removes node that contains it
// ------------------------------------------------------------------------
bool AVL::remove(int num){
  if(root == NULL){
    return false;
  }

 AVLNode* n = find(root, num);
 if (n == NULL){
   return false;
 }

 
 AVLNode* pre = findPredecessor(n);
 if (pre != NULL){
   n->data = pre->data;
   pre->data = n->data;
   AVLNode* p = pre->parent;
   deleteNode(pre);
   if (p != NULL){
     rebalance(p);
   }
 }
 else{
   AVLNode* p = n->parent;
   deleteNode(n);
   if (p != NULL){
     rebalance(p);
   }
 }
return true;
}
//-------------------------------------------------------------------------
// deleteNode
// attempts to remove a node and free memory
// ------------------------------------------------------------------------ 
void AVL::deleteNode(AVLNode* n){
  if (n != NULL){
    if (n->parent == NULL){
      root = NULL;
    }
    else if (n->left == NULL && n->right == NULL){
      if (n == n->parent->left){
	n->parent->left = NULL;
      }
      else{
	n->parent->right = NULL;
      }
    }
    else{
      if (n->left != NULL){
	if (n == n->parent->left){
	  n->parent->left = n->left;
	}
	else{
	  n->parent->right = n->left;
	}
	n->left->parent = n->parent;
      }
      else{
	if (n == n->parent->right){
	  n->parent->right = n->right;
	}
	else{
	  n->parent->left = n->right;
	}
	n->right->parent = n->parent;
      }
    }

    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    delete n;
    n = NULL;
  }
}

//-------------------------------------------------------------------------
// find
// returns node containing search value n, null if doesn't exist
// ------------------------------------------------------------------------
AVLNode* AVL::find(AVLNode* n, int num){
  if (!n){
    return NULL;
  }

  if (n->data == num){
    return n;
  }
  else if (num < n->data){
    return find(n->left, num);
  }
  else{
    return find(n->right,num);
  }
}

//-------------------------------------------------------------------------
// findPredecessor
// returns maximum of left subtree
// if left subtree doesn't exist, returns minimum of right subtree
// ------------------------------------------------------------------------
AVLNode* AVL::findPredecessor(AVLNode* n){
  if (n->left){
    return maximum(n->left);
  }
  else if (n->right){
    return minimum(n->right);
  }
  else{
    return NULL;
  }
}

//-------------------------------------------------------------------------
// minimum
// returns minimum value of a subtree
// ------------------------------------------------------------------------
AVLNode* AVL::minimum(AVLNode* n){
  while (n->left){
    n = n->left;
  }
  return n;
}

//-------------------------------------------------------------------------
// maximum
// returns maximum value of a subtree
// ------------------------------------------------------------------------
AVLNode* AVL::maximum(AVLNode* n){
  while (n->right){
    n = n->right;
  }
  return n;
}

//-------------------------------------------------------------------------
// testPrint
// public debug method to help test AVL tree
// prints out node linkage and balance in pre-order
// ------------------------------------------------------------------------
void AVL::testOrderPrint(){
  if (root){
    testOrderPrint(root);
  }
  cout << endl;
}

//-------------------------------------------------------------------------
// testPrint
// public debug method to help test AVL tree
// prints out node linkage and balance in pre-order
// ------------------------------------------------------------------------
void AVL::testOrderPrint(AVLNode* n){
  if (n){
    cout << "****Node " << n->data << "****" << endl;
    cout << "\tData: " << n->data << endl;
    if (n->left){
      cout << "\tLeft: " << n->left->data << endl;
    }
    else{
      cout << "\tLeft: NULL" << endl;
    }
    if (n->right){
      cout << "\tRight: " << n->right->data << endl;
    }
    else{
      cout << "\tRight: NULL" << endl;
    }
    
    if (n->parent){
      cout << "\tParent: " << n->parent->data << endl;
    }
    else{
      cout << "\tParent: ROOT" << endl;
    }
    cout << "\tBalance: " <<  n->balance << endl;  
    testOrderPrint(n->left);
    testOrderPrint(n->right);
  }
}

//-------------------------------------------------------------------------
// inOrderPrint
// public function of in-order print traversal
// ------------------------------------------------------------------------
void AVL::inOrderPrint(){
  cout << "In Order Print: ";
  inOrderPrint(root);
}

//-------------------------------------------------------------------------
// inOrderPrint
// private helper function of public in-order traversal
// ------------------------------------------------------------------------
void AVL::inOrderPrint(AVLNode* n){
  if (n != NULL){
    inOrderPrint(n->left);
    cout << n->data << " ";    
    inOrderPrint(n->right);
  }
}

//-------------------------------------------------------------------------
// preOrderPrint
// public function of pre-order print traversal
// ------------------------------------------------------------------------
void AVL::preOrderPrint(){
  cout << "Pre Order Print: ";
  preOrderPrint(root);
}

//-------------------------------------------------------------------------
// preOrderPrint
// private helper function of public pre-order traversal
// ------------------------------------------------------------------------
void AVL::preOrderPrint(AVLNode* n){
  if (n != NULL){
    cout << "Data: " <<  n->data << " ";
    
    preOrderPrint(n->left);
    preOrderPrint(n->right);
  }
}

//-------------------------------------------------------------------------
// inOrderPrint
// public function of post-order print traversal
// ------------------------------------------------------------------------
void AVL::postOrderPrint(){
  postOrderPrint(root);
}

//-------------------------------------------------------------------------
// postOrderPrint
// private helper function of public post-order traversal
// ------------------------------------------------------------------------
void AVL::postOrderPrint(AVLNode* n){
  if (n != NULL){
    postOrderPrint(n->left);
    postOrderPrint(n->right);
    cout << n->data << " " << endl;
  }
}



