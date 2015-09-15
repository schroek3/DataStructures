//Ken Schroeder
//CSS501
//November 10, 2014
//Program 4
//file: LinkedList.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

using namespace std;

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

//Struct Node
struct Node{
  int data;                   // int value stored a particular node in the list
  Node* next;                 // Node pointer to the next node in a linked list
};

class LinkedList{
 public:
  //Constructor
  LinkedList();
  //Copy Construtor
  LinkedList(const LinkedList& aList);
  //Destructor
  ~LinkedList();
  //insert an int into the linked list
  void insert(int n);
  //accessor methods
  int getLength();
  Node* getHead();
  //check if the list is empty
  bool isEmpty();
  //print out all the data contained in the linked list
  void printList();
  // void printList(ofstream&);
  //take the values in the list and merge sort them into ascending order
  void mergeSort();
 private:
  //clear list and erase all pointers
  void clearList();
  int size;                                     //size of list
  Node* head;                                   //pointer to first node in list
};
#endif
