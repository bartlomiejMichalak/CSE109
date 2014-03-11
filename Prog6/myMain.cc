#include "lex.h"
#include <iostream>

int main(int argc, char **argv){
  Lex lexer(cin);
  Token token(0, "", 0, 0);

  token = lexer.nextToken();
  printf(" type    mmyLexeme     line#    pos\n");
while(token.type() != Lex::ENDOFFILE) {

printf("%5d     %-10s  %5d   %5d\n", token.type(),
token.lexeme().c_str(), token.line(), token.pos());
token = lexer.nextToken();
}


}



