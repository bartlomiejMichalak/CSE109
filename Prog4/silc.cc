#include<iostream>
#include<fstream>
#include "parser.h"
int main(int argc, char **argv){
  if(argc > 1){
    ifstream myStream;
    myStream.open(argv[1]);
    Lex lexer(myStream);
    Parser parser(lexer, cout);
    parser.program();
  }
  else{
  Lex lexer(cin);
  Parser parser(lexer, cout);
  parser.program();
  }
}
