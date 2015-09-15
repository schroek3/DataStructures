//Queue.h

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

 struct Node{
    int data;
    Node* next;
  };

class Queue{
 private:
    void clearList();
    int size;
    Node* head;
 public:
    Queue();
    Queue(const Queue&);
    ~Queue();
    void enqueue(int);
    int dequeue();
    void isEmpty();    
    void getSize();
    void printList();
};
#endif
