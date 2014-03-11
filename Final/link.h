#ifndef LINK_H
#define LINK_H
#include "node.h"
#include <iostream>
#include <cstring>

using namespace std;

class Link{
public:
  // char myChar;
  // Node* nextNode;

  Link();
  ~Link();

private:
  char myChar;
  Node* nextNode;
};
#endif
