#include "parser.h"
//#include "lexer.h"
//#include "lex.h"
//#include "token.h"

const string Parser::ops[] = {"ADD", "SUB", "AND", "DIV", "REM", "ISEQ", "ISGE", "ISGT", "ISLE",
			      "ISLT", "ISNE", "MULT", "OR", "LOADL", "LOADV", "STOREV", "JUMPF",
			      "JUMP", "INSLABEL", "PRINT", "SEQ", "NULLX", "PRINTLN", "PRINTS"};

Parser::Parser(Lex& lexerx, ostream& outx): lexer(lexerx), out(outx) {
  token = lexer.nextToken();
  lindex = 0;
}

Parser::~Parser() {
}

void Parser::genCode() {
}

void Parser::gen(TreeNode* node) {
  switch(node->op){
  case SEQ:
    return;
  case NULLX:
    return;
  case LOADL:
    emit(LOADL, token.lexeme());
  case JUMP:
    emit(JUMP, token.lexeme());
  case INSLABEL:
    emit(INSLABEL, token.lexeme());
  default:
    emit(token.lexeme());
  }
}

void Parser::generateCode(TreeNode* node) {
  if(node != NULL){
    generateCode(node->leftChild);
    generateCode(node->rightChild);
    gen(node);
  }
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
  TreeNode *tmp;
  if(token.type()== Token::LPAREN){
    token = lexer.nextToken();

    tmp = expression();
    check(Token::RPAREN, "NOT FOUND");
    token = lexer.nextToken();
    return tmp;
  }
  else if(token.type()== Token::INTLIT){
    tmp = new TreeNode(LOADL, token.lexeme());
    token = lexer.nextToken();
    return tmp;
  }
  else if(token.type() == Token::FLOATLIT){
    tmp = new TreeNode(LOADL, token.lexeme());
    token = lexer.nextToken();
    return tmp;
  }
  else if(token.type() == Token::IDENT){
    tmp = new TreeNode(LOADV, token.lexeme());
    token = lexer.nextToken();
    return tmp;
  }
  else{
    error("REACHED END OF FACTOR()");
  }
  return NULL;
}

Parser::TreeNode* Parser::term() {
  TreeNode *tmp = factor();
  while((token.type() == Token::TIMES) || (token.type() == Token::DIVIDE) || (token.type() == Token::REM)){
    if(token.type()== Token::TIMES){
      token= lexer.nextToken();
      tmp = new TreeNode(MULT, tmp, factor());
    }
    if(token.type()== Token::DIVIDE){
      token = lexer.nextToken();
      tmp = new TreeNode(DIV, tmp, factor());
    }
    if(token.type() == Token::REM){
      token = lexer.nextToken();
      tmp  = new TreeNode(REM, tmp, factor());
    }
  }
  return tmp;
}

Parser::TreeNode* Parser::expression() {
 TreeNode *tmp = term();
  while((token.type()== Token::MINUS) || (token.type() == Token::PLUS)){
    if(token.type()== Token::MINUS){
      token= lexer.nextToken();
      tmp = new TreeNode(SUB, tmp, term());
    }
    if(token.type() == Token::PLUS){
      token = lexer.nextToken();
      tmp = new TreeNode(ADD, tmp, term());
    }
  }
  return tmp;
}

Parser::TreeNode* Parser::relationalExpression() {
  TreeNode *tmp = expression(); 
  while((token.type() == Token::EQ) || (token.type() == Token::LT) || (token.type() == Token::LE) || (token.type() == Token::GT) || (token.type() == Token::GE) || (token.type() == Token::NE)){
    if(token.type() == Token::EQ){
      token = lexer.nextToken();
      tmp = new TreeNode(ISEQ, tmp, expression());
    }
    if(token.type() == Token::LT){
      token = lexer.nextToken();
      tmp = new TreeNode(ISLT, tmp, expression());
    }
    if(token.type() == Token::LE){
      token = lexer.nextToken();
      tmp = new TreeNode(ISLE, tmp, expression());
    }
    if(token.type() == Token::GT){
      token = lexer.nextToken();
      tmp = new TreeNode(ISGT, tmp, expression());
    }
    if(token.type() == Token::GE){
      token = lexer.nextToken();
      tmp = new TreeNode(ISGE, tmp, expression());
    }
    if(token.type() == Token::NE){
      token = lexer.nextToken();
      tmp = new TreeNode(ISNE, tmp, expression());
    }
  }
  return tmp;
}

Parser::TreeNode* Parser::logicalExpression() {
  TreeNode *tmp = relationalExpression();
  while((token.type() == Token::AND) || (token.type() == Token::OR)){
    if(token.type() == Token::AND){
      token = lexer.nextToken();
      tmp = new TreeNode(AND, tmp, relationalExpression());
    }
    if((token.type() == Token::OR)){
      token = lexer.nextToken();
      tmp = new TreeNode(OR, tmp, relationalExpression());
    }
  }
  return tmp;
}

Parser::TreeNode* Parser::setStatement() {
  check(Token::SET, "expecting SET");
  token = lexer.nextToken();
  check(Token::IDENT, "expecting IDENT");
  TreeNode *tmp = new TreeNode(STOREV, token.lexeme());
  token = lexer.nextToken();
  check(Token::ASSIGN, "excpecting ASSIGN");
  token = lexer.nextToken();
  tmp = new TreeNode(SEQ, expression(), tmp);
  
  return tmp;
}

Parser::TreeNode* Parser::printExpression() {
  TreeNode *tmp;
  if(token.type() == Token::STRLIT){
    tmp = new TreeNode(PRINTS, token.lexeme());
    token = lexer.nextToken();
    return tmp;
  }
  else{
    tmp = new TreeNode(SEQ, expression(), new TreeNode(PRINT));
  }
  return tmp;
}

Parser::TreeNode* Parser::printStatement() {
  check(Token::PRINT, "expecting PRINT");
  token = lexer.nextToken();
  TreeNode *tmp = printExpression();
  while(token.type() == Token::COMMA){
    token = lexer.nextToken();
    tmp = new TreeNode(SEQ, tmp, printExpression());
  }
  return new TreeNode(SEQ, tmp, new TreeNode(PRINTLN));
}

Parser::TreeNode* Parser::whileStatement() {

  check(Token::WHILE, "expecting WHILE");
  token = lexer.nextToken();
  string myString = makeLabel();
  TreeNode *tmp = new TreeNode(INSLABEL, myString);
  tmp = new TreeNode(SEQ, tmp, logicalExpression());
  string myOtherString = makeLabel();
  tmp = new TreeNode(SEQ, tmp, new TreeNode(JUMPF, myOtherString));
  
  check(Token::DO, "expecting DO");
  token = lexer.nextToken();
  tmp = new TreeNode(SEQ, tmp, compoundStatement());
  tmp = new TreeNode(SEQ, tmp, new TreeNode(JUMP, myString));
  check(Token::END, "expecting END");
  token = lexer.nextToken();
  tmp = new TreeNode(SEQ, tmp, new TreeNode(INSLABEL, myOtherString));
  
  return tmp;
  
}

Parser::TreeNode* Parser::forStatement() {
  check(Token::FOR, "expecting FOR");
  token = lexer.nextToken();
  string myString = makeLabel();
  string myOtherString = makeLabel();
  
  check(Token::IDENT, "expecting IDENT");
  string myLexeme = token.lexeme();
  TreeNode *tmp = new TreeNode(STOREV, myLexeme);
  token = lexer.nextToken();
  
  check(Token::ASSIGN, "expecting ASSIGN");
  token = lexer.nextToken();
  tmp = new TreeNode(SEQ, expression(), tmp);
  
  check(Token::TO, "expecting TO");
  token = lexer.nextToken();
  tmp = new TreeNode(SEQ, tmp, new TreeNode(INSLABEL, myString));
  tmp = new TreeNode(SEQ, tmp, expression());
  tmp = new TreeNode(SEQ, tmp, new TreeNode(LOADV, myLexeme));
  tmp = new TreeNode(SEQ, tmp, new TreeNode(ISNE));
  tmp = new TreeNode(SEQ, tmp, new TreeNode(JUMPF, myOtherString));
  tmp = new TreeNode(SEQ, tmp, compoundStatement());
  
  check(Token::END, "expecting END");
  token = lexer.nextToken();
  tmp = new TreeNode(SEQ, tmp, new TreeNode(LOADL, "1"));
  tmp = new TreeNode(SEQ, tmp, new TreeNode(LOADV, myLexeme));
  tmp = new TreeNode(SEQ, tmp, new TreeNode(ADD));
  tmp = new TreeNode(SEQ, tmp, new TreeNode(STOREV, myLexeme));
  tmp = new TreeNode(SEQ, tmp, new TreeNode(JUMP, myString));
  tmp = new TreeNode(SEQ, tmp, new TreeNode(INSLABEL, myOtherString));
  
  return tmp;
}

Parser::TreeNode* Parser::ifStatement() {

  check(Token::IF, "expecting IF");
  token = lexer.nextToken();
  string myString = makeLabel();
  string myOtherString = makeLabel();
  TreeNode *tmp = logicalExpression();
  
  check(Token::THEN, "expecting THEN");
  token = lexer.nextToken();
  tmp = new TreeNode(SEQ, tmp, new TreeNode(JUMPF, myString));
  tmp = new TreeNode(SEQ, tmp, compoundStatement());
  tmp = new TreeNode(SEQ, tmp, new TreeNode(JUMP, myOtherString));
  tmp = new TreeNode(SEQ, tmp, new TreeNode(INSLABEL, myString));

  if(token.type() == Token::ELSE){
    token = lexer.nextToken();
    tmp = new TreeNode(SEQ, tmp, compoundStatement());
  }
  tmp = new TreeNode(SEQ, tmp, new TreeNode(INSLABEL, myOtherString));

  check(Token::ENDIF, "expecting ENDIF");
  token = lexer.nextToken();

  return tmp;
}

Parser::TreeNode* Parser::statement() {
  TreeNode *tmp;
  if((token.type() == Token::SET)||(token.type() == Token::PRINT)||(token.type() == Token::WHILE)||(token.type() == Token::IF)||(token.type() == Token::FOR)){
    if(token.type() == Token::SET){
      tmp = setStatement();
      return tmp;
    }
    
    if(token.type() == Token::PRINT){
      tmp = printStatement();
      return tmp;
    }
    
    if(token.type() == Token::WHILE){
      tmp = whileStatement();
      return tmp;
    }
    
    if(token.type() == Token::IF){
      tmp = ifStatement();
      return tmp;
    }
    
    if(token.type()== Token::FOR){
      tmp = forStatement();
      return tmp;
    }
  }
  else{
    error("NOT FOUND: in STATEMENT");
    return NULL;
  }
  return NULL;
}

Parser::TreeNode* Parser::compoundStatement() {
  TreeNode *tmp;
  if((token.type() == Token::SET)||(token.type() == Token::PRINT)||(token.type() == Token::WHILE)||(token.type() == Token::IF)||(token.type() == Token::FOR)){
    int counter = 0;
    do{
      if(counter == 0){
      tmp = statement();
      counter++;
      }
      else{ 
	tmp = new TreeNode(SEQ, tmp, statement());
      }
    }
    while((token.type() == Token::SET)||(token.type() == Token::PRINT)||(token.type() == Token::WHILE)||(token.type() == Token::IF)||(token.type() == Token::FOR));
  }
  else{ 
  check(Token::SET, "expected statement");
  }
  return tmp;
}


Parser::TreeNode* Parser::program() {
  check(Token::PROGRAM, "expecting PROGRAM");
  token = lexer.nextToken();
  check(Token::IDENT, "expecting IDENT");
  token = lexer.nextToken();
  TreeNode *tmp = compoundStatement();
  check(Token::END, "expecting END");
  token = lexer.nextToken();
  check(Token::PROGRAM, "expecting PROGRAM");
  token = lexer.nextToken();
  
  return tmp;
}
