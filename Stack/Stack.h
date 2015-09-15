#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

struct StackNode{
   StackNode* next;
   int data;
};

class Stack{
   friend ostream& operator<<(ostream&, const Stack& s);
   
   private:
      StackNode* top;
      int size;
      void clearList();
      void copyList(const Stack&);
   public:
      Stack();
      Stack(const Stack&);
      ~Stack();
      bool push(int);
      int pop();
      int peek();   
      int getSize();
      bool isEmpty();
      Stack& operator=(const Stack&);
      bool operator==(const Stack&);
};
#endif
