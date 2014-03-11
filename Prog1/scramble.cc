/*
  Bart Michalak
  bpm215
  Program Description:
  Program #1    DEADLINE: 8/16/2013, 11PM
*/

#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv){
  char* line;
  // char ** words;

  //  String* strArray; 
  
  //while (getline(cin, line)){
    // for(int i = 0; i < line.
  while (cin.good()){
    cin >> line;
    int size = sizeof(line)/sizeof(char);
    for(int i = 1; i <= size-2; ++i){
      int index = (rand()%(size-2))+1;
      char temp = line[index];
      line[index] = line[i];
      line[i] = temp;
    }
    cout << line << endl;  
  }
  char* tmp = strtok(line, " ");
  while(tmp!=NULL){
    cout << tmp << endl;
    tmp = strtok(NULL, " ");
  }
  return 0;
  

}


