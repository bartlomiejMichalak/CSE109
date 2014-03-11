//Bart Michalak
//CSE109 PROG3

#include "lex.h"
#include <iostream>

Lex::Lex(istream& input){
  
  myPoint = &input;
  
  position = 0;
  
  line = 0;
  
  curChar = nextChar();
}

char Lex::nextChar(){

  bool incomment = false;
  char ch;
  while(!myPoint->eof()){
    ch = myPoint->get();
    position+=1;
    if(ch == '\n'){
      line+=1;
      position =0;
    }
    if(ch == -1){
      return '#';
    }
    if(incomment){
      if(ch == '#'){
	incomment = false;
      }
    }else{
      if(ch == '#'){
	incomment = true;
      }else{
       
     	return ch;
      }
    }
  }
  return '#';
}

Token Lex::nextToken(){
  if(curChar== '#'){
    line+=1;
    return Token(ENDOFFILE, " ", position, (line+1));
  }
  while(curChar == ' ' || curChar== '\t' || curChar== '\n'){
    curChar = nextChar();
  }
  if(curChar == '#'){
    return Token(ENDOFFILE, " ", position, line);
  }
  string temp= " ";
  int tempPos = position;
  int tempNum= line;

  if(curChar <= '9' && curChar >= '1'){
    while((curChar <= '9')&&( curChar >= '0')){
      temp = temp + curChar;
      curChar = nextChar();
    }
    if(curChar == '.'){
      temp = temp + curChar;
      curChar = nextChar();
     
      if(curChar > '9' || curChar < '0'){
	return Token(ERROR, "Non-digit", tempPos, tempNum);
      }
      
      while(curChar <= '9' && curChar >= '0'){
	temp = temp +curChar;
	curChar = nextChar();
      }
      
      return Token(FLOATLIT, temp, tempPos, tempNum);
    }
    return Token(INTLIT, temp, tempPos, tempNum);
  }
  else if(curChar== '0'){
    curChar = nextChar();
    if(curChar == 'x'){
      temp = temp + curChar;
      curChar = nextChar();
      if((curChar <= '9' && curChar >= '0') || (curChar >= 'a' && curChar <= 'f')){
	temp = temp + curChar;
	curChar = nextChar();
      }
      else{
	return Token(ERROR, "Non-digit", tempPos, tempNum);
      }
      while((curChar <= '9' && curChar >= '0') || (curChar >= 'a' && curChar <= 'f')){
	temp = temp + curChar;
	curChar = nextChar();
      }
      return Token(INTLIT, temp, tempPos, tempNum);
    }
      else if(curChar == '.'){
	curChar = nextChar();
	if(curChar > '9' || curChar < '0'){
	  return Token(ERROR, "Non-digit", tempPos, tempNum);
	}
	while(curChar <= '9' && curChar >= '0'){
	  temp = temp +curChar;
	  curChar = nextChar();
	}
	return Token(FLOATLIT, temp, tempPos, tempNum);
      }
      return Token(INTLIT, temp, tempPos, tempNum);
  }
  else if((curChar >= 'a' && curChar <= 'z') || (curChar >= 'A' && curChar<= 'Z')){
    temp = temp + curChar;
    curChar = nextChar();
    while((curChar >= 'a' && curChar <= 'z') || (curChar >= 'A' && curChar<= 'Z')||(curChar == '_')||(curChar >= '0' && curChar <= '9')){
      temp = temp + curChar;
      curChar = nextChar();
    }
    if(temp.compare(" set")==0)
      return Token(SET, temp, tempPos, tempNum);
    else if(temp.compare(" print")==0)
      return Token(PRINT, temp, tempPos, tempNum);
    else if(temp.compare(" while")==0)
      return Token(WHILE, temp, tempPos, tempNum);
    else if(temp.compare(" do")==0)
      return Token(DO, temp, tempPos, tempNum);
    else if(temp.compare(" end")==0)
      return Token(END, temp, tempPos, tempNum);
    else if(temp.compare(" and")==0)
      return Token(AND, temp, tempPos, tempNum);
    else if(temp.compare(" or")==0)
      return Token(OR, temp, tempPos, tempNum);
    else if(temp.compare(" if")==0)
      return Token(IF, temp, tempPos, tempNum);
    else if(temp.compare(" then")==0)
      return Token(THEN, temp, tempPos, tempNum);
    else if(temp.compare(" else")==0)
      return Token(ELSE, temp, tempPos, tempNum);
    else if(temp.compare(" endif")==0)
      return Token(ENDIF, temp, tempPos, tempNum);
    else if(temp.compare(" program")==0)
      return Token(PROGRAM, temp, tempPos, tempNum);
    else{
      return Token(IDENT, temp, tempPos, tempNum);
    }
  }
  else if(curChar== '"'){
    temp = temp + curChar;
    curChar = nextChar();
    while(curChar != '"'){
      temp = temp + curChar;
      curChar = nextChar();
    }
    temp = temp + curChar;
    return Token(STRLIT, temp, tempPos, tempNum);
  }

  else if(curChar == '+'){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(PLUS, temp, tempPos, tempNum);
  }

  else if(curChar == '+'){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(PLUS, temp, tempPos, tempNum);
  }

  else if(curChar == '+'){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(PLUS, temp, tempPos, tempNum);
  }

  else if(curChar == '-'){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(MINUS, temp, tempPos, tempNum);
  }

  else if(curChar == '*'){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(TIMES, temp, tempPos, tempNum);
  }

  else if(curChar == '/'){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(DIVIDE, temp, tempPos, tempNum);
  }

  else if(curChar == '%'){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(REM, temp, tempPos, tempNum);
  }

  else if(curChar == '='){
    temp = temp + curChar;
    curChar = nextChar();
    if(curChar== '='){
      temp = temp + curChar;
      curChar = nextChar();
      return Token(EQ, temp, tempPos, tempNum);
    }
    return Token(ASSIGN, temp, tempPos, tempNum);
  }

  else if(curChar == '('){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(LPAREN, temp, tempPos, tempNum);
  }

  else if(curChar == ')'){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(RPAREN, temp, tempPos, tempNum);
  }

  else if(curChar == ','){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(COMMA, temp, tempPos, tempNum);
  }

  else if(curChar == '+'){
    temp = temp + curChar;
    curChar = nextChar();
    return Token(PLUS, temp, tempPos, tempNum);
  }

  else if(curChar == '<'){
    temp = temp + curChar;
    curChar = nextChar();
    if(curChar== '='){
      temp = temp + curChar;
      curChar = nextChar();
      return Token(LE, temp, tempPos, tempNum);
    }
    return Token(LT, temp, tempPos, tempNum);
  }

  else if(curChar == '>'){
    temp = temp + curChar;
    curChar = nextChar();
    if(curChar== '='){
      temp = temp + curChar;
      curChar = nextChar();
      return Token(GE, temp, tempPos, tempNum);
    }
    return Token(GT, temp, tempPos, tempNum);
  }
  else if(curChar == '!'){
    temp = temp + curChar;
    curChar = nextChar();
    if(curChar== '='){
      temp = temp + curChar;
      curChar = nextChar();
      return Token(NE, temp, tempPos, tempNum);
    }
    return Token(ERROR, temp, tempPos, tempNum);
  }
  else
    return Token(ERROR, "wtf?", tempPos, tempNum);
}
