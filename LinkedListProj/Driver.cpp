#include "LinkedList.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

string const FILE_NAME = "input.txt";

int main(){
  LinkedList ken;
  int num;
  
  ifstream infile("100000.txt");
  //  infile.open(FILE_NAME);
  if (!infile){
    cout << "File could not be opened." << endl;
    return 1;
  }
  
  while (infile >> num){
    ken.insert(num);
  }
   
  cout << "Pre merge sort\n--------------------\n"; 
  //  cout << endl << setw(10) << left << "Ken: ";
 // ken.printList();
  ken.mergeSort();
  cout << "After merge sort\n---------------------\n";
  ken.printList();
  cout << endl << endl;

  return 0;
}
