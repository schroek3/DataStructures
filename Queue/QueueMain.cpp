//QueueMain
#include "Queue.h"

#include <iostream>

using namespace std;

int main(){
   Queue ken;
   ken.enqueue(3);
   ken.enqueue(7);
   ken.enqueue(4);
   ken.dequeue();
   cout << "Done!" << endl;
   ken.printList();
   
   
   return 0;
}

