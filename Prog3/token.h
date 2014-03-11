#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>

using namespace std;

class Token{

private:
  int mmyType;
  string mmyLexeme;
  int mlineNum;
  int mposition;

public:
  int type(){return mmyType;}
  string lexeme(){return mmyLexeme;}
  int line(){return mlineNum;}
  int pos(){return mposition;}

  Token(int myType, string myLexeme, int position, int lineNum);
  ~Token(){}
};

#endif
  
