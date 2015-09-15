//Ken Schroeder
//CSS501
//November 15, 2014
//Program 4
//file: LinkedList.cpp

#include "LinkedList.h"

//-----------------------------------------------------------------------------
// LinkedListClass: Data structure to hold a list of integers:
// includes the following features:
// --function to insert an integer into the linked list
// --accessor functions for list head and list size
// --ability to merge sort the list into sorted order, low to high
//
// Implementation and Assumptions:
// --only ints will be inserted into the linked list
// --the list contains a Node struct. The node struct contains an int data value
//   - and a pointer to the next node
// --values can only be accessed in order, that is, there is no direct access
//   - to the nth value of the linked list
// --there is no dummy head node, head points to the first node.
// --if the list is empty, head == NULL
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// constructor
LinkedList::LinkedList(){
  head = NULL;
  size = 0;
}

//----------------------------------------------------------------------------
// copy constructor
LinkedList::LinkedList(const LinkedList& aList){
  size = aList.size;
  if (aList.head == NULL){
    head = NULL;
  }
  else{
    head = new Node;    
    Node *current = head;
    
    for (Node* temp = aList.head->next; temp != NULL; temp = temp->next){
      current-> next = new Node;
      current = current->next;
      current->data = temp->data;
    }
    current->next = NULL;
  }
}

//----------------------------------------------------------------------------
// destructor
LinkedList::~LinkedList(){
  clearList();
}

//----------------------------------------------------------------------------
// clearList
// destructs Linked List, erasing nodes and removing links
void LinkedList::clearList(){
  Node* temp = head;
  
  while(temp != NULL){
    Node* eraser = temp;
    temp = temp->next;
    eraser->next = NULL;
    delete eraser;
    eraser = 0;
  }
}

//----------------------------------------------------------------------------
// insert
// inserts  a value n into the back of a linked list
void LinkedList::insert(int n){
  //create a new node to hold n
  Node* temp = new Node;
  temp->data = n;
  temp->next = NULL;
  
  Node* current = head;
  
  // if the list has no head, make a head
  if (current == NULL){
    temp->next = head;
    head = temp;
  }
  // scroll through list until the end, insert a new node with data = n
  else{
    while (current->next != NULL){
      current = current->next;
    }
    current->next = temp;
  }
  
  //increase the size of the linked list
  size++;
}

//----------------------------------------------------------------------------
// getLength
// return the size of the array
int LinkedList::getLength(){
  return size;
}

//----------------------------------------------------------------------------
// getHead
// return a pointer to the list head
Node* LinkedList::getHead(){
  return head;
}

//----------------------------------------------------------------------------
// isEmpty
// return true if the list is empty
bool LinkedList::isEmpty(){
  return (size == 0);
}

//----------------------------------------------------------------------------
// printList
// cycle through the list and print the data at each node
void LinkedList::printList(){
  Node* current = head;
  //until reaching the end of the list (or if the list is empty) scroll
  // - through the list and print out the data at each node
  while(current != NULL){
    cout << current->data << " ";
    current = current->next;
  }
}

//----------------------------------------------------------------------------
// mergeSort
// interate through the list and merge increasingly large sorted sublists
// terminates when only one merge is done in an iteration
// Example: suppose you have the list with data 8-7-6-5-4-3-2-1
// -- after 1 iteration, the list will be 4 sorted lists of size 2
// -- 7-8-5-6-3-4-1-2. Merges will equal 4 and so the list will go on.
// -- after 2 iterations, the list will be 2 sorted lists of size 4
// -- 5-6-7-8-1-2-3-4. Merges will equal 2 and so the list will go on
// -- after 3 iterations, the list will be 1 sorted list of size 8
// -- 1-2-3-4-5-6-7-8. Merges will equal 1 and the function will terminate.
void LinkedList::mergeSort(){
  int merges = 0; 
  // variable k = size of sublists
  int k = 1; 
  //temporary linked list to hold sorted values
  LinkedList T;
  //pointers for the sublists
  Node* p = 0;
  Node* q = 0;
  
  while (merges != 1){
    //reset merges, pSize, qSize to 0.
    merges = 0;
    int pSize = 0;
    int qSize = 0;
    //move p pointer to head of list, set q, T.head = NULL;
    p = head;
    q = 0;
    T.head = NULL;
    //move until p reaches the end of the list
    while (p != 0){
      //increment merges
      merges ++;
      //move q to where p is
      q = p;
      //step q along the list k times
      for (int i = 0; i < k; i++){
	//stop stepping if q = NULL, we've reached the end of the list
	if (q != NULL){
	  q = q->next;
	  //increment the size of q everytime you move q
	  pSize++;
	}
      }
      //set qSize = k
      qSize = k;
      
      // if either list is empty, add remaining values in other list to T
      while (pSize > 0 || (qSize > 0 && q != 0)){
	//if p is empty or null, insert data from q
	if (pSize == 0 || p == 0){
	  while (qSize > 0 && q != 0){
	    T.insert(q->data);
	    q = q->next;
	    qSize--;
	  }
	}
	//if q is empty or null, insert data from p
	else if (qSize == 0 || q == 0){
	  while (pSize > 0){
	    T.insert(p->data);
	    p = p->next;
	    pSize--;
	  }
	}
	// if both lists have data, add smaller of the two values to T
	// -advance along the list
	else{
	  if (p->data < q->data){
	    T.insert(p->data);
	    pSize--;
	    p = p->next;
	  }
	  else{
	    T.insert(q->data);
	    qSize--;
	    q = q->next;
	  }
	}
      }
      //set p to where the q marker was, if q had reached the end of the list
      // -the program will terminate
      p = q;
      q = 0;
    }
    //double k
    k *= 2;
    //delete current list, set list = to temporary list T
    clearList();
    head = T.head;
  }
  head = T.head;
  T.head = 0;
}

