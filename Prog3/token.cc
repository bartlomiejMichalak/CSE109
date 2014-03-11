#include "token.h"
using namespace std;

//Token constructor
Token::Token(int myType, string myLexeme, int position, int lineNum){
 mmyType = myType;
  mmyLexeme = myLexeme;
  mlineNum = lineNum;
  mposition = position;
  
}
