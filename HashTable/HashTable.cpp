//HashTable.cpp
#include "HashTable.h"

HashTable::HashTable(){
  table = new vector<int> [101];
}

bool HashTable::insert(int n){
  if (!find(n)){
    int index = hash(n);
    table[index].push_back(n);
    cout << "Value " << n << "inserted into Hash Bucket " << index << endl;
    cout << "Contents of HashBucket " << index << ": " << endl;
    for (int i = 0; i < table[index].size(); i++){
      cout << "\t" << table[index][i] << " " << endl;
    }
    inserts++;
    if (inserts / capacity > .5){
      resize();
    }
    return true;
  }
  return false;
}

bool HashTable::remove(int n){
  int index = hash(n);
  if (!find(n)){
    return false;
  }
  else{
    for (int i = 0; i < table[index].size(); i++){
      if (table[index][i] == n){
        table[index].erase(table[index].begin()+i);
      }
    }
    return true;
  }
}

bool HashTable::find(int n){
   int index = hash(n);
  if (table[index].size() == 0){
    return false;
  }
  else{
    for (int i = 0; i < table[index].size(); i++){
      if (table[index][i] == n){
        return true;
      }
    }
  }
  return false;
}

int HashTable::hash(int n){
  return n % 101;
}

void HashTable::resize(){
  vector<int>* grower = NULL;
  grower = new vector<int> [capacity * 2];
  for (int i = 0; i < capacity; i++){
    if (table[i].size()){
      for (int j = 0; J < table[i].size(); j++){
        
      }
    }
  }
}
