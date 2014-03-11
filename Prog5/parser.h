#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lex.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sstream>

using namespace std;

class Parser {
  
private:

  enum Operation {
    ADD, SUB, AND, DIV, REM, ISEQ, ISGE, ISGT, ISLE, ISLT,
    ISNE, MULT, OR,
    LOADL, LOADV, STOREV, JUMPF, JUMP, INSLABEL,
    PRINT, SEQ, NULLX, PRINTLN, PRINTS
  };
  public:
  class TreeNode {

  public:
    Operation op;
    string val;
    TreeNode *leftChild;
    TreeNode *rightChild;

    void init(Operation opx, string valx, TreeNode *leftChildx, TreeNode *rightChildx) {
      op = opx;
      val = valx;
      leftChild = leftChildx;
      rightChild = rightChildx;
    }


    TreeNode(Operation op, string val) {
      init(op, val, NULL, NULL);
    }

    TreeNode(Operation op, string val, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, val, leftChild, rightChild);
    }

    TreeNode(Operation op) {
      init(op, "", NULL, NULL);
    }

    TreeNode(Operation op, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, "", leftChild, rightChild);
    }
  };
  
  string toString(TreeNode *n){
    string s = "";
    s+= ops[n->op] + "[" + n->val + "]";
    if(n-> leftChild != NULL && n->rightChild!=NULL)
      s+= "("+ toString(n->leftChild)+","+ toString(n->rightChild)+")";
    return s;
  };
  
private:
  
  
  Lex lexer;
  Token token;
  ostream& out;
  int lindex;
  int tindex;

  string makeLabel() { string tmp = "L"; stringstream ss; ss << ++lindex; string res = ss.str(); tmp = tmp + res; return tmp;}

  
  string makeTemp() { string tmp = "$TEMP"; stringstream ss; ss << ++tindex; string res = ss.str(); tmp = tmp + res; return tmp;}

  static const string ops[];  
  void emit(Operation op, string object) { out << ops[op] << " " <<  object << endl; }
  void emit(Operation op) { out << ops[op] << endl; }
  void emit(string label) { out << label << endl; }
  
  void gen(TreeNode* node);
  void generateCode(TreeNode* node);
  TreeNode* optimize(TreeNode* node);
  void error(string message);
  void check(int tokenType, string message);
  void optimizeAndGenerateExpressionCode(TreeNode* exp);
  
  TreeNode* compoundStatement();
  TreeNode* statement();
  TreeNode* setStatement();
  TreeNode* printExpression();
  TreeNode* printStatement();
  TreeNode* whileStatement();
  TreeNode* forStatement();
  TreeNode* ifStatement();
  TreeNode* logicalExpression();
  TreeNode* relationalExpression();
  TreeNode* expression();
  TreeNode* term();
  TreeNode* factor();

 public:
  Parser(Lex& lexer, ostream& out);
  ~Parser(); 
  TreeNode *program(); 
  void genCode();
};

#endif
