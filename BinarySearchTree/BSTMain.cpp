//Ken Schroeder
//January 31, 2015
//Binary Search Tree, unsorted
//File: BSTMain.cpp

#include <iostream>
#include <fstream>

#include "BST.h"


using namespace std;

int main(){
   BST ken;
   ifstream infile;
   int num;

   infile.open("numbers.txt");
   if (!infile){
     cout << "File could not be opened." << endl;
     return 1;
   }

   while (infile >> num){
     ken.insert(num);
   }

   ken.inOrderPrint();
   cout << endl;
   ken.preOrderPrint();
   cout << endl;
   ken.postOrderPrint();
   cout << endl;
   
   cout << "Height of tree: " << ken.getHeight() << endl;
   cout << "Number of Nodes: " << ken.numberOfNodes() << endl;
   	
   return 0;   
}
