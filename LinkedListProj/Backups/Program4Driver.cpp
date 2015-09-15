//Ken Schroeder
//CSS501
//November 15, 2014
//Program 4
//file: Program4Driver.cpp


#include "LinkedList.h"

#include <iostream>
#include <fstream>

using namespace std;

//file name
string const FILE_NAME = "input.txt";

int main(){
  LinkedList L;
  int num;

  //input and output streams
  ifstream infile;
  ofstream outfile;

  //open file
  infile.open(FILE_NAME.c_str());
  if (!infile){
    cout << "File could not be opened." << endl;
    return 1;
  }
  
  // insert contents of file into linked list
  while (infile >> num){
    L.insert(num);
  }
  
  //mergesort the linked list
  L.mergeSort();
  
  //open file to write to
  outfile.open("output.txt");

  //run through the linked list, writing to output file
  Node* engine = L.getHead();

  while (engine != NULL){
    outfile << engine->data << " ";
    engine = engine->next;
  }
  outfile.close();

  delete engine;


  return 0;
}
