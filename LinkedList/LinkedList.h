#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

using namespace std;
 struct Node{
    int data;
    Node* next;
  };

class LinkedList{
	friend ostream& operator<<(ostream&, const LinkedList&);
 public:
  LinkedList();
  LinkedList(const LinkedList& aList);
  ~LinkedList();
  void sortedInsert(int n);
  void insert(int n);
  //void remove(int n);
  //void retrieve(int index);
  int find(int n);
  void removeIndex (int index);
  void removeValue (int n);
  int getLength() const;
  bool isEmpty();
  void printList();
  void mergeSort();
  void sortedMergeLists(LinkedList A, LinkedList B);
  void mergeSortedLists(LinkedList A, LinkedList B);
 private:
 	void clearList();
 	Node* getHead() const;

  int size;
  Node* head;
};
#endif
