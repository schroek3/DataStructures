#include "KWSSet.h"	

//----------------------------------------------------------------------------
// constructor
KWSSet::KWSSet(){
	head = NULL;
	size = 0;
}

//----------------------------------------------------------------------------
// copy constructor
KWSSet::KWSSet(const KWSSet& k){
  size = k.size;
  if (k.head == NULL){
    head = NULL;
  }
  else{
    head = new Node;
    head->data = k.head->data;
    
    Node *current = head;
    
    for (Node* temp = k.head->next; temp != NULL; temp = temp->next){
      current-> next = new Node;
      current = current->next;
      current->data = temp->data;
    }
    current->next = NULL;
  }
}

//----------------------------------------------------------------------------
// deconstructor	
KWSSet::~KWSSet(){
  clearList();	
}

//----------------------------------------------------------------------------
// clearList
// removes nodes and deletes their pointers
void KWSSet::clearList(){
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
// inserts a node into the set
// will not insert if the value is already in the set
void KWSSet::insert(int n){
  if (find(n)){
    return;
  }
  Node* temp = new Node;
  Node* previous = NULL;
  Node* current = NULL;
  
  temp->data = n;
  
  if (head == NULL || head->data >= n){
    temp->next = head;
    head = temp;
  }
  else{
    previous = head;
    current = head->next;
    
    while(current != NULL && current->data < n){
      previous = current;
      current = current->next;
    }
    
    previous->next = temp;
    temp->next =current;
  }
  size++;
}

//----------------------------------------------------------------------------
// remove
// removes a value from the set
void KWSSet::remove(int n){  
  Node* previous = NULL;
  Node* current = head;

  if (!find(n)){
    return;
  }

  if (head->data == n){
    head = head->next;
  }
  else{
    while(current != NULL && current->data != n){
      previous = current;
      current = current->next;
    }
    previous->next = current->next;
    current->next = NULL;
    delete current;
    current = NULL;
  }
  size--;
}

//----------------------------------------------------------------------------
// find
// returns true in the value is in the set already, false otherwise

bool KWSSet::find(int n){
  if (head == NULL){
    return false;
  }

  Node* current = head;
  while (current != NULL){
    if (current->data == n){
      return true;  
    }
    current = current->next;
  }
  return false;
}

//----------------------------------------------------------------------------
// union
// returns the union of two sets
// for example, if set a = {1, 3, 5}, and set b = {2, 4, 5}:
//   -a becomes {1, 2, 3, 4, 5}
void KWSSet::unionSet(const KWSSet& k){
  if (k.head == NULL){
    return;
  }
  Node* engine = k.head;
  while (engine != NULL){
    insert(engine->data);
    engine = engine->next;
  }
}

//----------------------------------------------------------------------------
// intersection
// returns the intersection of two sets
// for example, if set a = {1, 3, 5}, and set b = {2, 4, 5}:
//   -a becomes {5}
// Might need to use S differently?
void KWSSet::intersection(KWSSet& k){
  KWSSet s = k;
  if (s.head == NULL){
    return;
  }

  Node* engine = head;
  while (engine != NULL){
    if (!s.find(engine->data)){
      remove(engine->data);
    }
    engine = engine->next;
  }
}

//----------------------------------------------------------------------------
// complement
// returns the items of one set not found in the other
// for example, if set a = {1, 3, 5}, and set b = {2, 4, 5}:
//   -a becomes {1,3}
void KWSSet::complement(KWSSet& k){
  KWSSet s = *this;
  Node* engine = s.head;
  while (engine != NULL){
    cout << "Searching for " << engine->data << endl;
    if (k.find(engine->data)){
      cout << "Found " << engine->data << endl;
      remove(engine->data);
    }
    engine = engine->next;
  }
}




//----------------------------------------------------------------------------
// isEmpty
// returns true if the set is empty, false otherwise
bool KWSSet::isEmpty(){
  return (head == NULL);
}

//----------------------------------------------------------------------------
// getLength
// returns size of set
int KWSSet::getLength(){
  return size;
}

//----------------------------------------------------------------------------
// operator<<
// Overloaded output operator
// Prints out all items in LinkedList
ostream& operator<<(ostream& output, const KWSSet& k){
  Node* engine = k.head;
  
  //cycle through LinkedList, printing data at each node
  while (engine != NULL){
    output << engine->data << " ";
    engine = engine->next;
  }
  return output;
}


