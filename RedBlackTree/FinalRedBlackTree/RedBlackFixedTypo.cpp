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
void RedBlack::clearTree(RedBlackNode* subRoot){
  if (subRoot != NULL){
    subRoot->parent = NULL;
    clearTree(subRoot->left);
    clearTree(subRoot->right);
    delete subRoot;
    subRoot = NULL;
  }
}

//-------------------------------------------------------------------------
// insert
// creates a node and inserts into red-black tree
// note that a number cannot be inserted twice
// nodes are red at time of insertion
// ------------------------------------------------------------------------
bool RedBlack::insert(int num){
  if (isInTree(num,root)){
    return false;
  }
  
  RedBlackNode* newNode = new RedBlackNode;
  newNode->red = true;
  newNode->data = num;
  if (root == NULL){
		setAsRoot(newNode);
  }
  else{
    addToTree(newNode, root);
  }
  return true;
}

//-------------------------------------------------------------------------
// setAsRoot
// takes a node and sets it to the root node
// root node is always black
// ------------------------------------------------------------------------
void RedBlack::setAsRoot(RedBlackNode* newRootNode){
	root = newRootNode;
	newRootNode->red = false;
}

//-------------------------------------------------------------------------
// addToTree
// private helper for insert function
// find correct location in the tree, and then recolor using insertCase1()
// ------------------------------------------------------------------------
void RedBlack::addToTree(RedBlackNode* newNode, RedBlackNode* head){
  if (newNode->data < head->data){
    if (head->left == NULL){  
			insertChildNode(newNode, head);
    }
    else{     
      addToTree(newNode,head->left);
    }
  }
  else{
    if (head->right == NULL){
			insertChildNode(newNode, head);
		}
    else{
      addToTree(newNode,head->right);
    }
  }
}

//-------------------------------------------------------------------------
// insertChildNode
// links parent node and child node
//--------------------------------------------------------------------------
void RedBlack::insertChildNode(RedBlackNode* newNode, RedBlackNode* parentNode){
  newNode->parent = parentNode;
	if (newNode->data < parentNode->data){
		parentNode->left = newNode;
	}
	else{
		parentNode->right = newNode;
	}
	insertCase1(newNode);
}

//-------------------------------------------------------------------------
// insertCase1
// current node n is at the root of the tree, repaint black
// ------------------------------------------------------------------------
void RedBlack::insertCase1(RedBlackNode* insertedNode){
  if (insertedNode->parent == NULL){
    setAsRoot(insertedNode);
  }
  else{
    insertCase2(insertedNode);
  }
}

//-------------------------------------------------------------------------
// insertCase2
// current node's parent is black
// ------------------------------------------------------------------------
void RedBlack::insertCase2(RedBlackNode* insertedNode){
  if (!insertedNode->parent->red){
    return;
  }
  else{
    insertCase3(insertedNode);
  }
}

//-------------------------------------------------------------------------
// insertCase3
// both parent and uncle are red
// paint uncle and parent black, grandparent red
// ------------------------------------------------------------------------

void RedBlack::insertCase3(RedBlackNode* insertedNode){
  RedBlackNode* nodeUncle = uncle(insertedNode);
  if ((nodeUncle != NULL) && nodeUncle->red){
    insertedNode->parent->red = false;
    nodeUncle->red = false;
    RedBlackNode* nodeGrandparent = grandparent(insertedNode);
    nodeGrandparent->red = true;
    insertCase1(nodeGrandparent);
  }
  else{
    insertCase4(insertedNode);
  }
}

//-------------------------------------------------------------------------
// insertCase4
// parent is red but uncle is black. 
// two cases: 
// 	n is right child and parent is left child (rotate left on parent)
// 	n is left child and parent is right child (rotate right on parent)
// ------------------------------------------------------------------------
void RedBlack::insertCase4(RedBlackNode* insertedNode){
  RedBlackNode* nodeGrandparent = grandparent(insertedNode);
  
  if (insertedNode == insertedNode->parent->right && insertedNode->parent == nodeGrandparent->left){
    rotateLeft(insertedNode->parent);
    insertedNode = insertedNode->left;
  }
  else if(insertedNode == insertedNode->parent->left && insertedNode->parent == nodeGrandparent->right){
    rotateRight(insertedNode->parent);
    insertedNode = insertedNode->right;
  }  
  insertCase5(insertedNode);
}
//-------------------------------------------------------------------------
// insertCase5
// parent is red, uncle is black
// two cases:
// 	node is left child and parent is left child (rotate right on grandparent)
// 	node is right child and parent is right child (rotate left on grandparent)
// ------------------------------------------------------------------------
void RedBlack::insertCase5(RedBlackNode* insertedNode){
  RedBlackNode* nodeGrandparent = grandparent(insertedNode);
  insertedNode->parent->red = false;
  nodeGrandparent->red = true;
  
  if(insertedNode == nodeGrandparent->parent->left){
    rotateRight(nodeGrandparent);
  }
  else{
    rotateLeft(nodeGrandparent);
  }
}

//-------------------------------------------------------------------------
// rotateLeft
// performs left rotation on the node
// ------------------------------------------------------------------------
void RedBlack::rotateLeft(RedBlackNode* rotationNode){
	RedBlackNode* rightChild = rotationNode->right;
	replaceNode(rotationNode, rightChild);
	rotationNode->right = rightChild->left;
	if (rightChild->left != NULL){
		rightChild->left->parent = rotationNode;
	}
	rightChild->left = rotationNode;
	rotationNode->parent = rightChild;
}
	

//-------------------------------------------------------------------------
// rotateRight
// performs right rotation on the node
// ------------------------------------------------------------------------
void RedBlack::rotateRight(RedBlackNode* rotationNode){
	RedBlackNode* leftChild = rotationNode->left;
	replaceNode(rotationNode, leftChild);
	rotationNode->left = leftChild->right;
	if (leftChild->right != NULL){
		leftChild->right->parent = rotationNode;
	}
	leftChild->right = rotationNode;
	rotationNode->parent = leftChild;
}
	
//-------------------------------------------------------------------------
// replaceNode
// swap node places in the tree
//-------------------------------------------------------------------------
void RedBlack::replaceNode(RedBlackNode* oldNode, RedBlackNode* newNode){
	if (oldNode->parent == NULL){
		setAsRoot(newNode);
	}
	else{
		if (oldNode == oldNode->parent->left){
			oldNode->parent->left = newNode;
		}
		else{
			oldNode->parent->right = newNode;
		}
	}
	if (newNode != NULL){
		newNode->parent = oldNode->parent;
	}
}

//-------------------------------------------------------------------------
// isInTree
// returns true if a number is already contained in a tree
// helper function for insert and removal functions
// ------------------------------------------------------------------------
bool RedBlack::isInTree(int num, RedBlackNode* searchHead){
  if (searchHead != NULL){
    if (searchHead->data == num){
      return true;
    }
    else if (searchHead-> data > num){
      return isInTree(num, searchHead->left);
    }
    else{
      return isInTree(num, searchHead->right);
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
  RedBlackNode* grandparentNode = grandparent(leaf);
  if (grandparentNode != NULL){
    if (leaf->parent == grandparentNode->left){
      return grandparentNode->right;
    }
    else{
      return grandparentNode->left;
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
RedBlackNode* RedBlack::sibling(RedBlackNode* siblingNode){
  if (siblingNode == siblingNode->parent->left){
    return siblingNode->parent->right;
  }
  else{
    return siblingNode->parent->left;
  }
}

//-------------------------------------------------------------------------
// findPredecessor
// returns maximum of left subtree
// if left subtree doesn't exist, returns minimum of right subtree
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::findPredecessor(RedBlackNode* headNode){
  if (headNode->left != NULL){
    return maximum(headNode->left);
  }
  else if (headNode->right != NULL){
    return minimum(headNode->right);
  }
  else{
    return NULL;
  }
}

//-------------------------------------------------------------------------
// minimum
// returns minimum value of a subtree
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::minimum(RedBlackNode* headNode){
  while(headNode->left != NULL){
    headNode = headNode->left;
  }
  return headNode;
}

//-------------------------------------------------------------------------
// maximum
// returns maximum value of a subtree
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::maximum(RedBlackNode* headNode){
  while (headNode->right != NULL){
    headNode = headNode->right;
  }
  return headNode;
}

//-------------------------------------------------------------------------
// find
// returns node containing search value n, null if doesn't exist
// ------------------------------------------------------------------------
RedBlackNode* RedBlack::find(RedBlackNode* searchHead, int num){
  if (searchHead == NULL){
    return NULL;
  }
  if (searchHead->data == num){
    return searchHead;
  }
  else if (searchHead->data > num){
    return find(searchHead->left,num);
  }
  else{
    return find(searchHead->right, num);
  }
}

//-------------------------------------------------------------------------
// search
// public function to return if a number is part of tree
// ------------------------------------------------------------------------
bool RedBlack::search(int num){
  return privateSearch(root,num);
}

//-------------------------------------------------------------------------
// privateSearch
// helper function for search
// ------------------------------------------------------------------------
bool RedBlack::privateSearch(RedBlackNode* searchHead, int num){
  if (searchHead == NULL){
    return false;
  }
  
  if (searchHead->data == num){
    return true;
  }
  else if(searchHead-> data > num){
    return privateSearch(searchHead->left,num);
  }
  else{
    return privateSearch(searchHead->right,num);
  }
}

//-------------------------------------------------------------------------
// remove
// finds if a value num is in tree and removes node that contains it
// ------------------------------------------------------------------------
void RedBlack::remove(int num){
  RedBlackNode* removalNode= find(root,num);
  if (removalNode != NULL){
    RedBlackNode* predecessorNode = findPredecessor(removalNode);
    if (predecessorNode != NULL){
      removalNode->data = predecessorNode->data;
      predecessorNode->data = removalNode->data;
      deleteNode(predecessorNode);
    }
    else{
      deleteNode(predecessorNode);
    }
  }
}

//-------------------------------------------------------------------------
// deleteNode
// attempts to remove a node
// ------------------------------------------------------------------------
void RedBlack::deleteNode(RedBlackNode* nodeToDelete){
  RedBlackNode* child = (nodeToDelete->right == NULL ? nodeToDelete->left : nodeToDelete->right);
  
  linkChild(nodeToDelete,child);  
  
  if (!nodeToDelete->red){
    if (child != NULL && child->red){
      child->red = false;
    }
    else{
      deleteCase1(nodeToDelete);
    }
  }
  
  freeNode(nodeToDelete);
}

//-------------------------------------------------------------------------
// linkChild
// link child with the node that will be deleted's parent
//-------------------------------------------------------------------------
void RedBlack::linkChild(RedBlackNode* nodeToDelete, RedBlackNode* child){
  if (child != NULL){  
	  if (nodeToDelete == nodeToDelete->parent->right){
      nodeToDelete->parent->right = child;
    }
    else{
      nodeToDelete->parent->left = child;
    }
    child->parent = nodeToDelete->parent;
  }
}
  
//-------------------------------------------------------------------------
// deleteCase1
// node is new root
// ------------------------------------------------------------------------
void RedBlack::deleteCase1(RedBlackNode* nodeToDelete){
  if (nodeToDelete->parent != NULL){
    deleteCase2(nodeToDelete);
  }
}

//-------------------------------------------------------------------------
// deleteCase2
// sibling is red
// reverse colors of p and s and rotate on parent
// rotate left if n is left child, right otherwise
// ------------------------------------------------------------------------
void RedBlack::deleteCase2(RedBlackNode* nodeToDelete){
  RedBlackNode* nodeSib = sibling(nodeToDelete);
  
  if (nodeSib != 0 && nodeSib->red){
    nodeToDelete->parent->red = true;
    nodeSib->red = false;
    if (nodeToDelete == nodeToDelete->parent->left){
      rotateLeft(nodeToDelete->parent);
    }
    else{
      rotateRight(nodeToDelete->parent);
    }
  }
  
  deleteCase3(nodeToDelete);
}

//-------------------------------------------------------------------------
// deleteCase3
// parent, sibling, and siblings children are black or null
// repaint s red, rebalance on parent
// ------------------------------------------------------------------------
void RedBlack::deleteCase3(RedBlackNode* nodeToDelete){
  RedBlackNode* nodeSib = sibling(nodeToDelete);
  
  if (nodeSib != 0 && !nodeToDelete->parent->red && !nodeSib->red &&
      (nodeSib->left == 0 || !nodeSib->left->red) &&
      (nodeSib->right == 0 || !nodeSib->right->red)){
    
    nodeSib->red = true;
    deleteCase1(nodeToDelete->parent);
  }
  else{
    deleteCase4(nodeToDelete);
  }
}

//-------------------------------------------------------------------------
// deleteCase4
// sibling and siblings children are black, parent is red
// exchange colors of parent and sibling
// ------------------------------------------------------------------------
void RedBlack::deleteCase4(RedBlackNode* nodeToDelete){
  RedBlackNode* nodeSib = sibling(nodeToDelete);
  
  if (nodeSib != 0 && nodeToDelete->parent->red && !nodeSib->red &&
      (nodeSib->left == 0 || !nodeSib->left->red) &&
      (nodeSib->right == 0 || nodeSib->right->red)){
    nodeSib->red = true;
    nodeToDelete->parent->red = false;
  }
  else{
    deleteCase5(nodeToDelete);
  }
}

//-------------------------------------------------------------------------
// deleteCase5
// sibling is black, siblings left child is red, right child black
// n is left child of parent
// rotate right at s, exchange colors of s and parent
// ------------------------------------------------------------------------
void RedBlack::deleteCase5(RedBlackNode* nodeToDelete){
  RedBlackNode* nodeSib = sibling(nodeToDelete);
  
  if (nodeSib != 0 && !nodeSib->red){
	deleteCase5Helper(nodeToDelete,nodeSib);
  }  
  deleteCase6(nodeToDelete);
}

//-------------------------------------------------------------------------
// deleteCase5Helper
// recolor and rotate for deleteCase5
//-------------------------------------------------------------------------
void RedBlack::deleteCase5Helper(RedBlackNode* nodeToDelete, RedBlackNode* nodeSib){
  if ((nodeToDelete == nodeToDelete->parent->left) &&
	(nodeSib->right == 0 || !nodeSib->right->red) &&
	(nodeSib->left->red)){
      nodeSib->red = true;
      nodeSib->left->red = false;
      rotateRight(nodeSib);
    }
    else if ((nodeToDelete == nodeToDelete->parent->right) &&
	     (nodeSib == 0 || !nodeSib->left->red) &&
	     (nodeSib->red)){
      nodeSib->red = true;
      nodeSib->right->red = false;
      rotateLeft(nodeSib);
    }
}
//-------------------------------------------------------------------------
// deleteCase6
// two cases:
// 	sibling is black, siblings right child is red, n is left child
// 		rotate left at p
// 	sibling is black, siblings left child is red, n is right child
// 		rotate right at p
// ------------------------------------------------------------------------
void RedBlack::deleteCase6(RedBlackNode* nodeToDelete){
  RedBlackNode* siblingNode = sibling(nodeToDelete);
  siblingNode->red = nodeToDelete->parent->red;
  nodeToDelete->parent->red = false;
  }

//-------------------------------------------------------------------------
// deleteCase6Helper
// Performs recoloring and rotations required by deletion case 6
//-------------------------------------------------------------------------
void RedBlack::deleteCase6Helper(RedBlackNode* nodeToDelete, RedBlackNode* siblingNode){
	if (nodeToDelete == nodeToDelete->parent->left){
	  if (siblingNode->right != NULL){
      siblingNode->right->red= false;
    }
      rotateLeft(nodeToDelete->parent);
  }
  else{
    if (siblingNode->left != NULL){
      siblingNode->left ->red = false;
    }
    rotateRight(nodeToDelete->parent);
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
void RedBlack::inOrderPrint(RedBlackNode* nodeToPrint){
  if (nodeToPrint != NULL){
    inOrderPrint(nodeToPrint->left);
    cout << nodeToPrint->data;
    if (!nodeToPrint->red){
      cout << "*";
    }
    cout << " ";
    
    inOrderPrint(nodeToPrint->right);
  }
}

//--------------------------------------------------odeToPrint-----------------------
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
void RedBlack::preOrderPrint(RedBlackNode* nodeToPrint){
  if (nodeToPrint != NULL){
    cout << "Data: " <<  nodeToPrint->data << endl;
    
    preOrderPrint(nodeToPrint->left);
    preOrderPrint(nodeToPrint->right);
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
void RedBlack::postOrderPrint(RedBlackNode* nodeToPrint){
  if (nodeToPrint != NULL){
    postOrderPrint(nodeToPrint->left);
    postOrderPrint(nodeToPrint->right);
    cout << nodeToPrint->data << " " << endl;
  }
}
//-------------------------------------------------------------------------
// freeNode
// free memory associated with a node
// ------------------------------------------------------------------------
void RedBlack::freeNode(RedBlackNode* removalNode){
  if (removalNode == NULL){
    return;
  }
  if (removalNode->parent != NULL){
    if (removalNode == removalNode->parent->left){
      removalNode->parent->left = NULL;
    }
    else if (removalNode == removalNode->parent->right){
      removalNode->parent->right = NULL;
    }
  }
  else{
    root = NULL;
  }

	removeNode(removalNode);
  
}

//--------------------------------------------------------------------------
// removeNode
// clears links and frees memory for removal node
//-------------------------------------------------------------------------
void RedBlack::removeNode(RedBlackNode* removalNode){
	removalNode->parent = NULL;
	removalNode->left = NULL;
	removalNode->right = NULL;
	
	delete removalNode;
	removalNode = NULL;
}
