#ifndef LEX_H
#define LEX_H
#include <iostream>
#include "token.h"
using namespace std;

class Lex{

public:
  Lex(istream&);
  char nextChar();
  Token nextToken();
   
 private:
  istream *myPoint;
  char curChar;
  int position;
  int line;
};
#endif
