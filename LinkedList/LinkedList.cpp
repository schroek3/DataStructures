#include "LinkedList.h"

LinkedList::LinkedList(){
  head = NULL;
  size = 0;
}

LinkedList::LinkedList(const LinkedList& aList){
  size = aList.size;
  if (aList.head == NULL){
    head = NULL;
  }
  else{
    head = new Node;
    // head->data = aList.head->data;
    
    Node *current = head;
    
    for (Node* temp = aList.head->next; temp != NULL; temp = temp->next){
      current-> next = new Node;
      current = current->next;
      current->data = temp->data;
    }
    current->next = NULL;
  }
}

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

void LinkedList::sortedInsert(int n){
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

void LinkedList::insert(int n){
  Node* temp = new Node;
  temp->data = n;
  Node* current = head;

  if (current == NULL){
    temp->next = head;
    head = temp;
  }
  else{
    while (current->next != NULL){
      current = current->next;
    }
    current->next = temp;
  }
  size++;
}

int LinkedList::find(int n){
 int pos = 0;  

 if (head == NULL){
   return -1;
 }
 else{
   Node* current = head;
   
   while(current != NULL && current->data != n){
     pos++;
     current = current->next;
   }
   return pos;
 }
}

void LinkedList::removeIndex(int index){
  Node* previous = head;
  Node* current = head->next;

  if (index == 0){
    head = head->next;
  }
  else if (index > size){
    return;
  }
  else{
    for (int i = 1; i < index; i++){
      previous = current;
      current = current->next;
    }
    previous->next = current->next;
    current->next = NULL;
  }
  delete current;
  current = NULL;
}

void LinkedList::removeValue(int n){  
  Node* previous = NULL;
  Node* current = head;

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
 
}
  

int LinkedList::getLength() const{
  return size;
}

bool LinkedList::isEmpty(){
  return (size == 0);
}

void LinkedList::printList(){
  Node* current = head;
  while(current != NULL){
    cout << current->data << " ";
    current = current->next;
  }
}

void LinkedList::sortedMergeLists(LinkedList A, LinkedList B){
  head = NULL;
  size = 0;
  
  Node* aEngine = A.head;
  Node* bEngine = B.head;

  while(aEngine != NULL){
    /*    Node* temp = new Node;
    temp->data = aEngine->data;
    temp->next = aEngine->next;
    */   
    sortedInsert(aEngine->data);
    aEngine = aEngine->next;  
  }
  while(bEngine != NULL){
    /*    Node* temp = new Node;
    temp->data = bEngine->data;
    temp->next = bEngine->next;
    */
    sortedInsert(bEngine->data);
    bEngine = bEngine->next;
  }

}

/*

void LinkedList::sortUnsortedLists(LinkedList &A, LinkedList &B){
  //sort without sorted insert
  head = NULL;
  size = 0;

  Node* temp = new Node;
  Node* previous = NULL;
  Node* current = NULL;
  
  Node* aEngine = A.head;
  Node* bEngine = B.head;
  cout << aEngine->data;
  cout << bEngine->data;
  
  while(aEngine != NULL && bEngine != NULL){
    current = head;
    current->next = NULL;
    previous = NULL;
    if (aEngine->data < bEngine->data){
      cout << "What! " << aEngine->data << "<" << bEngine->data << "?";
      temp->data = aEngine->data;
      if (head == NULL || head->data > temp->data){
	temp->next = head;
	head = temp;
      }else{
	previous = head;
	cout << "Head data: " << head->data << endl;
	current = head->next;
	if (current = NULL){
	  cout << "current == NULL" << endl;
	}
	while (current != NULL && current->data < temp->data){
	  cout << "moving";
	  previous = current;
	  current = current->next;
	}
	previous->next = temp;
	temp->next = current;
      }
      size++;
      aEngine = aEngine->next;
    }
    else{
      temp->data = bEngine->data;
      if (head == NULL || head->data > temp->data){
	temp->next = head;
	head = temp;
      }
      else{
	previous = head;
	current = head->next;
	while (current != NULL && current->data < temp->data){
	  previous = current;
	  current = current->next;
	}
	previous->next = temp;
	temp->next = current;
      }
      size++;
      bEngine = bEngine->next;
    }
  }
}
*/
 
void LinkedList::mergeSortedLists(LinkedList A, LinkedList B){
  head = NULL;
  size = 0;

  Node* aEngine = A.head;
  Node* bEngine = B.head;

  Node* current = NULL;

  while (aEngine != NULL && bEngine != NULL){
    Node* temp = new Node;
    current = head;
    if (aEngine->data < bEngine->data){
      temp->data = aEngine->data;
      aEngine = aEngine->next;
      if (head == NULL){
	temp->next = NULL;
	head = temp;
      }
      else{
	while(current->next != NULL){
	  current = current->next;
	}
	current->next = temp;
      }
    }
    else{
      temp->data = bEngine->data;     
      bEngine = bEngine->next;
      if (head == NULL){
	temp->next = NULL;
	head = temp;
      }
      else{
	while(current->next != NULL){
	  current = current->next;
	}
	current->next = temp;
      }
    }
  }
  current = current->next;
  if (aEngine == NULL){
    while (bEngine != NULL){
      Node* temp = new Node;
      temp-> data = bEngine->data;
      bEngine = bEngine->next;
      current->next = temp;
      current = current->next;
    }
  }  
  else{
    while (aEngine != NULL){
      Node* temp = new Node;
      temp->data = aEngine->data;
      aEngine = aEngine->next;
      current->next = temp;
      current = current->next;
    }
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

//----------------------------------------------------------------------------
// operator<<
// Overloaded output operator
// Prints out all items in LinkedList
ostream& operator<<(ostream& output, const LinkedList& L){
  Node* engine = L.head;
  
  //cycle through LinkedList, printing data at each node
  while (engine != NULL){
    output << engine->data << endl;
    engine = engine->next;
  }
  return output;
}
	
