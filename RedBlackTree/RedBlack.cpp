//Ken Schroeder
//January 28, 2015
//CSS502
//Implement a red black tre
//File: Red-Black.cpp


#include "RedBlack.h"

//-------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------
RedBlack::RedBlack(){
  root = NULL;
  size = 0;
}

//-------------------------------------------------------------------------
// Deconstructor
// ------------------------------------------------------------------------
RedBlack::~RedBlack(){
  clearTree(root);
}

//-------------------------------------------------------------------------
// clearTree
// Removes pointers and deletes nodes
//-------------------------------------------------------------------------
void RedBlack::clearTree(RedBlackNode* r){
  if (r != NULL){
    r->parent = NULL;
    clearTree(r->left);
    clearTree(r->right);
    delete r;
    r = NULL;
  }
}

//-------------------------------------------------------------------------
// insert
// creates a node and inserts into red-black tree
// note that a number cannot be inserted twice
// nodes are red at time of insertion
// ------------------------------------------------------------------------
bool RedBlack::insert(int n){
  if (isInTree(n,root)){
    return false;
  }
  
  RedBlackNode* node = new RedBlackNode;
  node->red = true;
  node->data = n;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  
  if (root == NULL){
    root = node;
    node->red = false;
    size++;
    
  }
  else{
    addToTree(node, root);
  }
  return true;
}

//-------------------------------------------------------------------------
// addToTree
// private helper for insert function
// find correct location in the tree, and then recolor using insertCase1()
// ------------------------------------------------------------------------
void RedBlack::addToTree(RedBlackNode* node, RedBlackNode* head){
  if (node->data < head->data){
    if (head->left == NULL){    
      node->parent = head;
      head->left = node;
      size++;
      insertCase1(node);
    }
    else{     
      addToTree(node,head->left);
    }
  }
  else{
    if (head->right == NULL){
      node->parent = head;
      head->right = node;
      size++;
      insertCase1(node);
    }
    else{
      addToTree(node,head->right);
    }
  }
}

//-------------------------------------------------------------------------
// insertCase1
// current node n is at the root of the tree, repaint black
// ------------------------------------------------------------------------
void RedBlack::insertCase1(RedBlackNode* n){
  if (n->parent == NULL){
    n->red = false;
    root = n;
  }
  else{
    insertCase2(n);
  }
}

//-------------------------------------------------------------------------
// insertCase2
// current node's parent is black
// ------------------------------------------------------------------------
void RedBlack::insertCase2(RedBlackNode* n){
  if (!n->parent->red){
    return;
  }
  else{
    insertCase3(n);
  }
}

//-------------------------------------------------------------------------
// insertCase3
// both parent and uncle are red
// paint uncle and parent black, grandparent red
// ------------------------------------------------------------------------

void RedBlack::insertCase3(RedBlackNode* n){
  RedBlackNode* u = uncle(n);
  if ((u != NULL) && u->red){
    n->parent->red = false;
    u->red = false;
    RedBlackNode* g = grandparent(n);
    g->red = true;
    insertCase1(g);
  }
  else{
    insertCase4(n);
  }
}

//-------------------------------------------------------------------------
// insertCase4
// parent is red but uncle is black. 
// two cases: 
// 	n is right child and parent is left child (rotate left on parent)
// 	n is left child and parent is right child (rotate right on parent)
// ------------------------------------------------------------------------
void RedBlack::insertCase4(RedBlackNode* n){
  RedBlackNode* g = grandparent(n);
  
  if (n == n->parent->right && n->parent == g->left){
    rotateLeft(n->parent);
    n = n->left;
  }
  else if(n == n->parent->left && n->parent == g->right){
    rotateRight(n->parent);
    n = n->right;
  }  
  insertCase5(n);
}
//-------------------------------------------------------------------------
// insertCase5
// parent is red, uncle is black
// two cases:
// 	node is left child and parent is left child (rotate right on grandparent)
// 	node is right child and parent is right child (rotate left on grandparent)
// ------------------------------------------------------------------------
void RedBlack::insertCase5(RedBlackNode* n){
  RedBlackNode* g = grandparent(n);
  n->parent->red = false;
  g->red = true;
  
  if(n == n->parent->left){
    rotateRight(g);
  }
  else{
    rotateLeft(g);
  }
}

//-------------------------------------------------------------------------
// rotateLeft
// performs left rotation on the node
// ------------------------------------------------------------------------
void RedBlack::rotateLeft(RedBlackNode* n){
  RedBlackNode* y = n->right;              //y = x->right
  RedBlackNode* leftOfY = y->left;         //y's left subtree
  RedBlackNode* p = n->parent;             //x's parent
  
  n->right = leftOfY;
  if (leftOfY != NULL){
    leftOfY->parent = n;
  }
  
  if (n->parent == NULL){
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
  y->parent = p;
}

//-------------------------------------------------------------------------
// rotateRight
// performs left rotation on the node
// ------------------------------------------------------------------------
void RedBlack::rotateRight(RedBlackNode* n){
  RedBlackNode* y = n->left;
  RedBlackNode* rightOfY = y->right;
  RedBlackNode* p = n->parent;
  
  n->left = rightOfY;
  if (rightOfY != NULL){
    rightOfY->parent = n;
  }
  
  if (n->parent == NULL){
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
  y->parent = p;
}

//-------------------------------------------------------------------------
// isInTree
// returns true if a number is already contained in a tree
// helper function for insert and removal functions
// ------------------------------------------------------------------------
bool RedBlack::isInTree(int n, RedBlackNode* head){
  if (head != NULL){
    if (head->data == n){
      cout << n << " is already in the tree! " << endl;
      return true;
    }
    else if (head-> data > n){
      return isInTree(n, head->left);
    }
    else{
      return isInTree(n, head->right);
    }
  }
  return false;
}

//-------------------------------------------------------------------------
// grandparent
// returns node->parent->parent, null if doesn't exist
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::grandparent(RedBlackNode* leaf){
  if (leaf != NULL && leaf->parent != NULL && leaf->parent->parent != NULL){
    return leaf->parent->parent;
  }
  else{
    return NULL;
  }
}

//-------------------------------------------------------------------------
// uncle
// returns parent's sibling node (same parent), null if doesn't exist
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::uncle(RedBlackNode* leaf){
  RedBlackNode* g = grandparent(leaf);
  if (g != NULL){
    if (leaf->parent == g->left){
      return g->right;
    }
    else{
      return g->left;
    }
  }
	else{
	  return NULL;
	}
}

//-------------------------------------------------------------------------
// sibling
// returns node with same parent as current node, null if doesn't exist
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::sibling(RedBlackNode* r){
  if (r == r->parent->left){
    return r->parent->right;
  }
  else{
    return r->parent->left;
  }
}

//-------------------------------------------------------------------------
// findPredecessor
// returns maximum of left subtree
// if left subtree doesn't exist, returns minimum of right subtree
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::findPredecessor(RedBlackNode* r){
  if (r->left != NULL){
    return maximum(r->left);
  }
  else if (r->right != NULL){
    return minimum(r->right);
  }
  else{
    return NULL;
  }
}

//-------------------------------------------------------------------------
// minimum
// returns minimum value of a subtree
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::minimum(RedBlackNode* r){
  while(r->left != NULL){
    r = r->left;
  }
  return r;
}

//-------------------------------------------------------------------------
// maximum
// returns maximum value of a subtree
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::maximum(RedBlackNode* r){
  while (r->right != NULL){
    r = r->right;
  }
  return r;
}

//-------------------------------------------------------------------------
// find
// returns node containing search value n, null if doesn't exist
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::find(RedBlackNode* r, int n){
  if (r == NULL){
    return NULL;
  }
  if (r->data == n){
    return r;
  }
  else if (r->data > n){
    return find(r->left,n);
  }
  else{
    return find(r->right, n);
  }
}

//-------------------------------------------------------------------------
// search
// public function to return if a number is part of tree
// ------------------------------------------------------------------------

bool RedBlack::search(int n){
  return privateSearch(root,n);
}

//-------------------------------------------------------------------------
// privateSearch
// helper function for search
// ------------------------------------------------------------------------
bool RedBlack::privateSearch(RedBlackNode* r, int n){
  if (r == NULL){
    return false;
  }
  
  if (r->data == n){
    return true;
  }
  else if(r-> data > n){
    return privateSearch(r->left,n);
  }
  else{
    return privateSearch(r->right,n);
  }
}

//-------------------------------------------------------------------------
// remove
// finds if a value num is in tree and removes node that contains it
// ------------------------------------------------------------------------
void RedBlack::remove(int num){
  RedBlackNode* node= find(root,num);
  if (node != NULL){
    RedBlackNode* pre = findPredecessor(node);
    if (pre != NULL){
      node->data = pre->data;
      pre->data = node->data;
      deleteNode(pre);
    }
    else{
      deleteNode(node);
    }
  }
}

//-------------------------------------------------------------------------
// deleteNode
// attempts to remove a node
// ------------------------------------------------------------------------
void RedBlack::deleteNode(RedBlackNode* node){
  RedBlackNode* child = (node->right == NULL ? node->left : node->right);
  
  if (child != NULL){
    if (node == node->parent->right){
      node->parent->right = child;
    }
    else{
      node->parent->left = child;
    }
    child->parent = node->parent;
  }
  
  if (!node->red){
    if (child != NULL && child->red){
      child->red = false;
    }
    else{
      deleteCase1(node);
    }
  }
  
  freeNode(node);
}

//-------------------------------------------------------------------------
// deleteCase1
// node is new root
// ------------------------------------------------------------------------
void RedBlack::deleteCase1(RedBlackNode* node){
  if (node->parent != NULL){
    deleteCase2(node);
  }
}

//-------------------------------------------------------------------------
// deleteCase2
// sibling is red
// reverse colors of p and s and rotate on parent
// rotate left if n is left child, right otherwise
// ------------------------------------------------------------------------
void RedBlack::deleteCase2(RedBlackNode* node){
  RedBlackNode* s = sibling(node);
  
  if (s != 0 && s->red){
    node->parent->red = true;
    s->red = false;
    if (node == node->parent->left){
      rotateLeft(node->parent);
    }
    else{
      rotateRight(node->parent);
    }
  }
  
  deleteCase3(node);
}

//-------------------------------------------------------------------------
// deleteCase3
// parent, sibling, and siblings children are black or null
// repaint s red, rebalance on parent
// ------------------------------------------------------------------------
void RedBlack::deleteCase3(RedBlackNode* node){
  RedBlackNode* s = sibling(node);
  
  if (s != 0 && !node->parent->red && !s->red &&
      (s->left == 0 || !s->left->red) &&
      (s->right == 0 || !s->right->red)){
    
    s->red = true;
    deleteCase1(node->parent);
  }
  else{
    deleteCase4(node);
  }
}

//-------------------------------------------------------------------------
// deleteCase4
// sibling and siblings children are black, parent is red
// exchange colors of parent and sibling
// ------------------------------------------------------------------------
void RedBlack::deleteCase4(RedBlackNode* node){
  RedBlackNode* s = sibling(node);
  
  if (s != 0 && node->parent->red && !s->red &&
      (s->left == 0 || !s->left->red) &&
      (s->right == 0 || s->right->red)){
    s->red = true;
    node->parent->red = false;
  }
  else{
    deleteCase5(node);
  }
}

//-------------------------------------------------------------------------
// deleteCase5
// sibling is black, siblings left child is red, right child black
// n is left child of parent
// rotate right at s, exchange colors of s and parent
// ------------------------------------------------------------------------
void RedBlack::deleteCase5(RedBlackNode* node){
  RedBlackNode* s = sibling(node);
  
  if (s != 0 && !s->red){
    if ((node == node->parent->left) &&
	(s->right == 0 || !s->right->red) &&
	(s->left->red)){
      s->red = true;
      s->left->red = false;
      rotateRight(s);
    }
    else if ((node == node->parent->right) &&
	     (s == 0 || !s->left->red) &&
	     (s->red)){
      s->red = true;
      s->right->red = false;
      rotateLeft(s);
    }
  }  
  deleteCase6(node);
}

//-------------------------------------------------------------------------
// deleteCase6
// two cases:
// 	sibling is black, siblings right child is red, n is left child
// 		rotate left at p
// 	sibling is black, siblings left child is red, n is right child
// 		rotate right at p
// ------------------------------------------------------------------------
void RedBlack::deleteCase6(RedBlackNode* node){
  RedBlackNode* s = sibling(node);
  s->red = node->parent->red;
  node->parent->red = false;
  
  if (node == node->parent->left){
    if (s->right != NULL){
      s->right->red= false;
    }
    rotateLeft(node->parent);
  }
  else{
    if (s->left != NULL){
      s->left ->red = false;
    }
    rotateRight(node->parent);
  }
}

//-------------------------------------------------------------------------
// inOrderPrint
// public function of in-order print traversal
// ------------------------------------------------------------------------
void RedBlack::inOrderPrint(){
  cout << "In Order Print: ";
  inOrderPrint(root);
}

//-------------------------------------------------------------------------
// inOrderPrint
// private helper function of public in-order traversal
// ------------------------------------------------------------------------
void RedBlack::inOrderPrint(RedBlackNode* n){
  if (n != NULL){
    inOrderPrint(n->left);
    cout << n->data;
    if (!n->red){
      cout << "*";
    }
    cout << " ";
    
    inOrderPrint(n->right);
  }
}

//-------------------------------------------------------------------------
// preOrderPrint
// public function of pre-order print traversal
// ------------------------------------------------------------------------
void RedBlack::preOrderPrint(){
  cout << "Pre Order Print: ";
  preOrderPrint(root);
}

//-------------------------------------------------------------------------
// preOrderPrint
// private helper function of public pre-order traversal
// ------------------------------------------------------------------------
void RedBlack::preOrderPrint(RedBlackNode* n){
  if (n != NULL){
    cout << "Data: " <<  n->data << endl;
    
    preOrderPrint(n->left);
    preOrderPrint(n->right);
  }
}

//-------------------------------------------------------------------------
// inOrderPrint
// public function of post-order print traversal
// ------------------------------------------------------------------------
void RedBlack::postOrderPrint(){
  postOrderPrint(root);
}

//-------------------------------------------------------------------------
// postOrderPrint
// private helper function of public post-order traversal
// ------------------------------------------------------------------------
void RedBlack::postOrderPrint(RedBlackNode* n){
  if (n != NULL){
    postOrderPrint(n->left);
    postOrderPrint(n->right);
    cout << n->data << " " << endl;
  }
}
//-------------------------------------------------------------------------
// freeNode
// free memory associated with a node
// ------------------------------------------------------------------------
void RedBlack::freeNode(RedBlackNode* node){
  if (node == NULL){
    return;
  }
  if (node->parent != NULL){
    if (node == node->parent->left){
      node->parent->left = NULL;
    }
    else if (node == node->parent->right){
      node->parent->right = NULL;
    }
  }
  else{
    root = NULL;
  }

  node->parent = NULL;
  node->right = NULL;
  node->left = NULL;
  
  delete node;
  node = NULL;
  
}

//-------------------------------------------------------------------------
// testPrint
// public debug method to help test red-black tree
// prints out node linkage and colors
// ------------------------------------------------------------------------
void RedBlack::testPrint(){
  testPrint(root);
}

//-------------------------------------------------------------------------
// testPrint
// private debug method to help test red-black tree
// prints out node linkage and colors in pre-order traversal
// ------------------------------------------------------------------------
void RedBlack::testPrint(RedBlackNode* n){
  if (n != NULL){
    cout << "Data: " <<  n->data << endl;
    cout << "Color: ";
    (n->red == 1) ? cout << "Red": cout << "Black";
    cout << endl;
    if (n->left != NULL){
      cout << "\tLeft Data: " << n->left->data << endl;
    }
    else{
      cout << "\tLeft Data: NULL" << endl;
    }
    if (n ->right != NULL){
      cout << "\tRight Data: " << n->right->data << endl;
    }
    else{
      cout << "\tRight Data: NULL" << endl;
    }
    if (n->parent != 0){
      cout << "\tParent " << n->parent->data << endl;
    }
    else{
      cout << "\tParent = NULL " << endl;
    }
    
    testPrint(n->left);
    testPrint(n->right);
  }
}

