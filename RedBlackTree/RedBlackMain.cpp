//Ken Schroeder
//January 28, 2015
//CSS 502
//Implement a Red Black Tree
//File: RedBlackMain.cpp

#include <iostream>
#include <fstream>

#include "RedBlack.h"

using namespace std;

int main(){
  RedBlack ken;
  ken.insert(8);
  ken.insert(25);
  ken.insert(27);
  ken.insert(32);
  ken.insert(22);

  ken.insert(90);
  ken.insert(87);
  ken.insert(11);
  ken.insert(76);
  ken.insert(83);

  ken.insert(31);
  ken.insert(17);
  ken.insert(29);
  ken.insert(60);
  ken.insert(24);



  ken.insert(3);
  //ken.remove(3);
  /*
  ken.remove(32);

  ken.remove(27);
  ken.remove(31);
  ken.remove(29);
  ken.remove(8);
  ken.remove(87);
  
  ken.remove(22);
  ken.remove(24);
  ken.remove(76);
  ken.remove(11);
  ken.remove(32);

  ken.remove(3);
  ken.remove(25);
  ken.remove(17);
  ken.remove(83);
  ken.remove(60);
  ken.remove(90);

  */
  ken.testPrint();
  
  cout << endl;
  
  return 0;
}
