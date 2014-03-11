#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include "hash.h"
#include <cstring>

using namespace std;

class Link{
private: Link* myLink; double data; char key[180];
  
public:
  Link();
  Link(const char*);
  double& getDataReference();
  void setNextLink(Link*);
  Link* getNextLink(void);
  
  void setData(double);
  double getData(void);

  void setKey(const char*);
  char* getKey(void);

  
};

class HashTable{
private:
  Link** table; int length;
  void add(double, const char*);
public:
  HashTable(int);
  HashTable(void);
  HashTable(const HashTable&);
  ~HashTable(){}
  friend HashTable& operator +=(HashTable&, const char*);
  friend ostream& operator <<(ostream& out, const HashTable& s);
  double& operator [](char*);
  double operator [](char*) const;
  bool inTable(const char*) const;
  int getLength(){return length;}
  




};
#endif
