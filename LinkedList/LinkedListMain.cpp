#include "LinkedList.h"

#include <iostream>

using namespace std;

int main(){
  cout << "Hello, world" << endl;
  LinkedList ken;
  cout << ken.isEmpty() <<endl;
  ken.sortedInsert(7);
  ken.sortedInsert(7);
  ken.sortedInsert(5);
  ken.sortedInsert(12);
  ken.sortedInsert(9);
  ken.sortedInsert(21);
  ken.sortedInsert(3);
  ken.sortedInsert(19);
  cout << ken.isEmpty() << endl;
  ken.printList();
  //int pos = ken.find(12);
  // cout << "12 is found at position: " << pos << endl;
  // ken.removeIndex(pos);
  //  ken.removeValue(3);
  // ken.removeValue(7);
  cout << endl;
  LinkedList hannah;
  LinkedList tasha;
  hannah.sortedInsert(13);
  hannah.sortedInsert(21);
  hannah.sortedInsert(1);
  hannah.sortedInsert(14);
  hannah.sortedInsert(27);
  hannah.sortedInsert(214);
  hannah.printList();
  cout << endl;
  tasha.mergeSortedLists(ken,hannah);
  cout << "Ken: ";
  ken.printList();
  cout << endl << "Hannah: ";
  hannah.printList();
  cout << tasha << endl;
  tasha.printList();
 
  return 0;
}
