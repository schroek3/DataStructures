//HashTable.h
//Hash Table to hold 50, 10 digit numbers


#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include <vector>

using namespace std;

class HashTable{
  private:
    vector<int>* table;
    int hash(int);
    void resize();
    double capacity;
    double inserts;
  public:
    bool insert(int);
    bool remove(int);
    bool find(int);
};
#endif
