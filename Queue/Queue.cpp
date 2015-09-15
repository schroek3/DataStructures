//Queue.cpp

#include "Queue.h"

Queue::Queue(){
  head = NULL;
  size = 0;
}

Queue::Queue(const Queue& q){
  size = q.size;
  if (q.head == NULL){
    head = NULL;
  }
  else{
    head = new Node;
    // head->data = aList.head->data;
    
    Node *current = head;
    
    for (Node* temp = q.head->next; temp != NULL; temp = temp->next){
      current-> next = new Node;
      current = current->next;
      current->data = temp->data;
    }
    current->next = NULL;
  }
}

Queue::~Queue(){
  clearList();
}

//----------------------------------------------------------------------------
// clearList
// destructs Linked List, erasing nodes and removing links
void Queue::clearList(){
  Node* temp = head;
  
  while(temp != NULL){
    Node* eraser = temp;
    temp = temp->next;
    eraser->next = NULL;
    delete eraser;
    eraser = 0;
  }
}

void Queue::enqueue(int n){
  Node* temp = new Node;
  temp->data = n;
  temp->next = 0;
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

int Queue::dequeue(){
   Node* temp = head;
   head = head->next;
   temp->next = 0;
   size--;
   int data = temp->data;
   
   delete temp;
   temp = 0;
   
   return data;
}

void Queue::printList(){
   Node* temp = head;
   while (temp != NULL){
      cout << temp->data << " ";
      temp = temp->next;
   }
   delete temp;
}



