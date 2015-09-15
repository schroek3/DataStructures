#include "Stack.h"

Stack::Stack(){
   size = 0;
   top = NULL;
}      

Stack::Stack(const Stack& s){
   copyList(s);
}

Stack::~Stack(){
   clearList();
}

bool Stack::push(int n){
	StackNode* pusher = new StackNode;
	
	pusher->data = n;
	pusher->next = top;
	
	
	top = pusher;	
	size++;
}

int Stack::pop(){
	size --;
	int returnVal = top->data;
	StackNode* popper = new StackNode;
	popper = top;
	top = top->next;
	popper->next = NULL;
	delete popper;
	popper = 0;
}

int Stack::peek(){
	return top->data;
}

int Stack::getSize(){
	return size;
}

bool Stack::isEmpty(){
   return size == 0;
}

Stack& Stack::operator=(const Stack& s){
   if (this == &s){
      return *this;
   }
	copyList(s);
	return *this;
}
  

bool Stack::operator==(const Stack& s){
	return false;
}

      
void Stack::copyList(const Stack& s){
	clearList();

	size = s.size;

	if (s.top == NULL){
		top = NULL;
	}
	else{
		top = new StackNode;
		top->data = s.top->data;
	
		StackNode* current = top;
	
		for (StackNode* temp = s.top->next; temp != NULL; temp = temp->next){
			current = new StackNode;
			current = current->next;
			current->data = temp->data;
			current->next = NULL;
		}
		current->next = NULL;
	}
}      
      
void Stack::clearList(){
   StackNode* temp = top;
   
   while (temp != NULL){
      StackNode* eraser = temp;
      temp = temp->next;
      eraser->next = NULL;
      delete eraser;
      eraser = 0;
   }
}

ostream& operator<<(ostream& output, const Stack& s){
   StackNode* engine = s.top;
   
   while (engine != NULL){
      output << engine->data << " ";
      engine = engine->next;
   }
   
   cout << endl;
   return output;
}
   

