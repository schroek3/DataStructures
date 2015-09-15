#include <iostream>

#include "KWSSet.h"
using namespace std;

int main(){
	KWSSet ken;
	ken.insert(7);
	ken.insert(20);
	ken.insert(16);
	ken.insert(31);
	KWSSet han;
	han.insert(20);
	han.insert(4);
	han.insert(49);
	han.insert(31);
	han.insert(7);
	cout << "Ken: " << ken << endl;
	cout << "Hannah: " << han << endl;
	ken.intersection(han);
	cout << "Ken A Hannah: " << ken << endl;
}
