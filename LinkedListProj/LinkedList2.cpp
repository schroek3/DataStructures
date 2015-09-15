#include "LinkedList2.h"

LinkedList2::LinkedList2(){
  head = NULL;
  size = 0;
}

LinkedList2::LinkedList2(const LinkedList2& aList){
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

LinkedList2::~LinkedList2(){
  Node* temp = head;
  
  while (temp != NULL){
    Node* eraser = temp;
    temp = temp->next;
    eraser->next = NULL;
    delete eraser;
  }
}

void LinkedList2::sortedInsert(int n){
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

void LinkedList2::insert(int n){
  Node* temp = new Node;
  temp->data = n;
  temp->next = NULL;

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

int LinkedList2::find(int n){
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

void LinkedList2::removeIndex(int index){
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

void LinkedList2::removeValue(int n){  
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
  

int LinkedList2::getLength(){
  return size;
}

Node* LinkedList2::getHead(){
  return head;
}

bool LinkedList2::isEmpty(){
  return (size == 0);
}

void LinkedList2::printList(){
  Node* current = head;
  while(current != NULL){
    cout << current->data << " ";
    current = current->next;
  }
}



void LinkedList2::divideList(Node* source, Node** start, 
			     Node** end){

  Node* fast;
  Node* slow;
  
  if (source == NULL || source->next == NULL){
    *start = source;
    *end = NULL;
  }
  else{
    slow = source;
    fast = source->next;
    
    while(fast != NULL){
      fast = fast->next;
      if (fast != NULL){
	slow = slow->next;
	fast = fast->next;
      }
    }
    *start = source;
    *end = slow->next;
    slow->next = NULL;
  }
}

void LinkedList2::mergeSort(Node** headRef){
  //  LinkedList2 T;
  printList();
  cout << endl;
  Node* newHead = *headRef;
  Node* a;
  Node* b;

  if ((newHead == NULL) || (newHead->next == NULL)){
    return;
  }

  divideList(newHead, &a, &b);

  mergeSort(&a);
  mergeSort(&b);

  *headRef =  merge(a,b);
}

Node* LinkedList2::merge(Node* a, Node* b){
  Node* result = NULL;
  if (a == NULL){
    return b;
  }
  else if (b == NULL){
    return a;
  }
  
  if (a->data <= b->data){
    result = a;
    result->next = merge(a->next, b);
  }
  else{
    result = b;
    result->next = merge(a, b->next);
  }
  return result;
}

/* struct Node* result = NULL;
 
  struct Node** lastPtrRef = &result;
  while(1){
    if (a == NULL){
      *lastPtrRef = b;
      break;
    }
    else if (b == NULL){
      *lastPtrRef = a;
      break;
    }
    if (a->data <= b->data){
      result = a;
      result->next = b;
    }
    else{
      result = b;
      b->next = a;
    }
    
  }
    return result;
}
  */

