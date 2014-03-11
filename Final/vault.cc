#include "vault.h"
#include <string>

Vault::Vault(string key, int num){
  string key = myKey;
  int num = myNum;
  startNode = Node();
}

void Vault::put(string key, int val){
  Vault(key, val);
  int counter = 0;
  char* temp[100];
  for(int i = 0; i<key.length();i++){
    temp[i] = key.at(i);
  }
  
  Node* myTemp = startNode;
  for(int i = 0; i < (temp.size());i++){
    if(startNode == NULL){
      while(temp.size() > counter){
	myTemp = Link(temp[i]);
	nextNode = myTemp;
	nextNode = Node();
	counter ++;
      }
      nextNode = Node(nodeVal);
    }
    else if(startNode != NULL){
      myTemp = myTemp->Link::letter;
      //if the letter is equal to the character at the given point in
      //the array keep checking to see if the next letter is the same
      //as the next in the array until the next letter is not the
      //same. At the point move myTemp pointer to the following node
      //and assign myTemp pointer to a new Link that is assigned the
      //letter that did not match any sequential letters that existed
      //in the link.
  }
}

int Vault::get(string key){
  char* temp[100];
  for(int i = 0, key.length();i++){
    temp[i] = key.at(i);
  }
  string thisKey = key;
  if(strcmp((v.key), thisKey) = 0){
    v.key = 11;
  }
  else if(strcmp((v.key), thisKey)!=0){
    return -1
      }
  else
    return NULL;
}

Vault& operator +=(Vault& v, char* key){
  if(v.get(key) == -1){
    v.put(key, 0);
  }
}
