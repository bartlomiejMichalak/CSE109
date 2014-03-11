#include "parser.h"

const string Parser::ops[] = {"ADD", "SUB", "AND", "DIV", "REM", "ISEQ", "ISGE", "ISGT", "ISLE",
			      "ISLT", "ISNE", "MULT", "OR", "LOADL", "LOADV", "STOREV", "JUMPF",
			      "JUMP", "INSLABEL", "PRINT", "SEQ", "NULLX", "PRINTLN", "PRINTS"};

Parser::Parser(Lex& lexerx, ostream& outx): lexer(lexerx), out(outx) {
  token = lexer.nextToken();
}

Parser::~Parser() {
}

void Parser::genCode() {
}

void Parser::gen(TreeNode* node) {
}

void Parser::generateCode(TreeNode* node) {
}

Parser::TreeNode* Parser::optimize(TreeNode* node) {
  return NULL;
}

void Parser::error(string message) {
  cerr << message << " Found " << token.lexeme() << " at line " << token.line() << " position " << token.pos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.type() != tokenType)
    error(message);
}


void Parser::optimizeAndGenerateExpressionCode(TreeNode* exp) {
}

Parser::TreeNode* Parser::factor() {
  if(token.type()== Token::LPAREN){
    token = lexer.nextToken();
    expression();
    check(Token::RPAREN, "NOT FOUND");
    token = lexer.nextToken();
    return NULL;
  }
  else if(token.type()== Token::INTLIT){
    token = lexer.nextToken();
    return NULL;
  }
  else if(token.type() == Token::FLOATLIT){
    token = lexer.nextToken();
    return NULL;
  }
  else if(token.type() == Token::IDENT){
    token = lexer.nextToken();
    return NULL;
  }
  else{
    error("REACHED END OF FACTOR()");
  }
  return NULL;
}

Parser::TreeNode* Parser::term() {
  factor();
  while((token.type() == Token::TIMES) || (token.type() == Token::DIVIDE) || (token.type() == Token::REM)){
    if(token.type()== Token::TIMES){
      token= lexer.nextToken();
      factor();
    }
    if(token.type()== Token::DIVIDE){
      token = lexer.nextToken();
      factor();
    }
    if(token.type() == Token::REM){
      token = lexer.nextToken();
      factor();
    }
    return NULL;
  }
  return NULL;
}

Parser::TreeNode* Parser::expression() {
  term();
  while((token.type()== Token::MINUS) || (token.type() == Token::PLUS)){
    if(token.type()== Token::MINUS){
      token= lexer.nextToken();
      term();
    }
    if(token.type() == Token::PLUS){
      token = lexer.nextToken();
      term();
    }
    return NULL;
  }
  return NULL;
}
  
Parser::TreeNode* Parser::relationalExpression() {
  expression(); 
  while((token.type() == Token::EQ) || (token.type() == Token::LT) || (token.type() == Token::LE) || (token.type() == Token::GT) || (token.type() == Token::GE) || (token.type() == Token::NE)){
    if(token.type() == Token::EQ){
      token = lexer.nextToken();
      expression();
    }
    if(token.type() == Token::LT){
      token = lexer.nextToken();
      expression();
    }
    if(token.type() == Token::LE){
      token = lexer.nextToken();
      expression();
    }
    if(token.type() == Token::GT){
      token = lexer.nextToken();
      expression();
    }
    if(token.type() == Token::GE){
      token = lexer.nextToken();
      expression();
    }
    if(token.type() == Token::NE){
      token = lexer.nextToken();
      expression();
    }
  }
  return NULL;
}

 
Parser::TreeNode* Parser::logicalExpression() {
  relationalExpression();
  while((token.type() == Token::AND) || (token.type() == Token::OR)){
    if(token.type() == Token::AND){
      token = lexer.nextToken();
      relationalExpression();
    }
    if((token.type() == Token::OR)){
      token = lexer.nextToken();
      relationalExpression();
    }
    return NULL;
  }
  return NULL;
}

Parser::TreeNode* Parser::setStatement() {
  check(Token::SET, "expecting SET");
  token = lexer.nextToken();
  check(Token::IDENT, "expecting IDENT");
  token = lexer.nextToken();
  check(Token::ASSIGN, "excpecting ASSIGN");
  token = lexer.nextToken();
  expression();
  
  return NULL;
}

Parser::TreeNode* Parser::printExpression() {
  if(token.type() == Token::STRLIT){
    return NULL;
    token = lexer.nextToken();
  }
  else{
    expression();
  }
  return NULL;
}

Parser::TreeNode* Parser::printStatement() {
  check(Token::PRINT, "expecting PRINT");
  token = lexer.nextToken();
  printExpression();
  while(token.type() == Token::COMMA){
    token = lexer.nextToken();
    printExpression();
  }
  return NULL;
}

Parser::TreeNode* Parser::whileStatement() {
  check(Token::WHILE, "expecting WHILE");
  token = lexer.nextToken();
  logicalExpression();
  check(Token::DO, "expecting DO");
  token = lexer.nextToken();
  compoundStatement();
  check(Token::END, "expecting END");
  token = lexer.nextToken();
  return NULL;
  
}

Parser::TreeNode* Parser::forStatement() {
  check(Token::FOR, "expecting FOR");
  token = lexer.nextToken();
  check(Token::IDENT, "expecting IDENT");
  token = lexer.nextToken();
  check(Token::ASSIGN, "expecting ASSIGN");
  token = lexer.nextToken();
  expression();
  check(Token::TO, "expecting TO");
  token = lexer.nextToken();
  expression();
  compoundStatement();
  check(Token::END, "expecting END");
  token = lexer.nextToken();

  return NULL;
}

Parser::TreeNode* Parser::ifStatement() {
  check(Token::IF, "expecting IF");
  token = lexer.nextToken();
  logicalExpression();
  check(Token::THEN, "expecting THEN");
  token = lexer.nextToken();
  compoundStatement();
  if(token.type() == Token::ELSE){
    token = lexer.nextToken();
    compoundStatement();
  }
  check(Token::ENDIF, "expecting ENDIF");
  token = lexer.nextToken();

  return NULL;
}

Parser::TreeNode* Parser::statement() {
  if((token.type() == Token::SET)||(token.type() == Token::PRINT)||(token.type() == Token::WHILE)||(token.type() == Token::IF)||(token.type() == Token::FOR)){
    if(token.type() == Token::SET){
      token = lexer.nextToken();
      setStatement();
      return NULL;
    }
    if(token.type() == Token::PRINT){
      token = lexer.nextToken();
      printStatement();
      return NULL;
    }
    if(token.type() == Token::WHILE){
      token = lexer.nextToken();
      whileStatement();
      return NULL;
    }
    if(token.type() == Token::IF){
      token = lexer.nextToken();
      ifStatement();
      return NULL;
    }
    if(token.type()== Token::FOR){
      token = lexer.nextToken();
      forStatement();
      return NULL;
    }
  }
  else{
    error("NOT FOUND");
    return NULL;
  }
  return NULL;
}

Parser::TreeNode* Parser::compoundStatement() {
  if((token.type() == Token::SET)||(token.type() == Token::PRINT)||(token.type() == Token::WHILE)||(token.type() == Token::IF)||(token.type() == Token::FOR)){
    do{
      statement();
      token = lexer.nextToken();
    }
    while((token.type() == Token::SET)||(token.type() == Token::PRINT)||(token.type() == Token::WHILE)||(token.type() == Token::IF)||(token.type() == Token::FOR));
      }
  return NULL;
}


Parser::TreeNode* Parser::program() {
  check(Token::PROGRAM, "expecting PROGRAM");
  token = lexer.nextToken();
  check(Token::IDENT, "expecting IDENT");
  token = lexer.nextToken();
  compoundStatement();
  check(Token::END, "expecting END");
  token = lexer.nextToken();
  check(Token::PROGRAM, "expecting PROGRAM");
  token = lexer.nextToken();
  
  return NULL;
}
