#ifndef KWSSET_H
#define KWSSET_H

#include <iostream>

using namespace std;

struct Node{
	int data;
	Node* next;
};

//-----------------------------------------------------------------------------
// KWSSet class: Data structure to hold a set of integers:
// includes the following features:
// --function to insert or remove an integer from the set
// --function to determine if a value is in the set
// --accessor functions for set size
// --ability to print contents of the set
//
// Implementation and Assumptions:
// --only ints will be inserted into the set
// --the list contains a Node struct. The node struct contains an int data value
//   - and a pointer to the next node
// --values can only be accessed in order, that is, there is no direct access
//   - to the nth value of the set
// --there is no dummy head node, head points to the first node.
// --if the set is empty, head == NULL
// Future Considerations:
// --Union, Intersection, Complement
//----------------------------------------------------------------------------

class KWSSet{
	friend ostream& operator<<(ostream&, const KWSSet&);
  public:
  	KWSSet();
  	KWSSet(const KWSSet& kset);
  	~KWSSet();

  	void insert(int);
  	void remove(int);
  	bool find(int);
  	bool isEmpty();
  	int getLength();
  	
    void unionSet(const KWSSet&);
    void intersection(KWSSet&);
    void complement (KWSSet&);
  private:
  	void clearList();
    int size;
    Node* head;
};
#endif
