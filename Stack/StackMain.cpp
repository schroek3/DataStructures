#include <iostream>

#include "Stack.h"
#include <cmath>

using namespace std;

int main(){
   Stack ken;

   ken.push(20);
   ken.push(7);
   ken.pop();
   ken.push(41);
   ken.push(38);
   
   cout << ken << endl;
   
   ken.pop();
   
   cout << ken;
return 0;   
}


