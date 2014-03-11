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
  // string line;

  //  String* strArray; 
  
  //while (getline(cin, line)){

  // for(int i = 0; i < line.
  int size = sizeof(line)/sizeof(char);
  cout << "The var size is Equal to: " << size << endl;
  while (cin.good()){
    cin >> line;
    
    for(int i = 1; i <= size-2; ++i){
      size = sizeof(line)/sizeof(char);
      cout << line[i] << endl;
      int index = (rand()%(size-2))+1;
      char temp = line[index];
      line[index] = line[i];
      line[i] = NULL;
    }
    cout << line << endl;  
  }
  char* temp = strtok(line, " ,");
  while(temp!=NULL){
    cout << tmp << endl;
    temp = strtok(NULL, " ,");
  }
  return 0;
  

}
