#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
#include "link.h"
#include "node.h"
#include "vault.h"

class Node{
public:
  Node* nextNode;
  // int nodeVal;
  // Link* myLinks [10];
  // int numOfLinks;

  Node();
  Node(int);
  ~Node();
  
private:
  int nodeVal;
  Link* myLinks[10];
  int numOfLinks;
};
#endif
  
