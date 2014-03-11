#ifndef VAULT_H
#define VAULT_H
#include "node.h"
#include "link.h"
#include <iostream>
#include <cstring>

using namespace std;

class Vault{
public:
  Node* startNode;
  
  void put(string key, int value);
  int get(string key);

  Vault();
  ~Vault();

  friend Vault& operator +=(Vault&, const char*);

private:

};
#endif
