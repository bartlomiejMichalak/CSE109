/*
  CSE109
  Bart Michalak
  Bpm215@lehigh.edu
  Prog2: HashMaps
  Due July 22, 2013
*/
  

#include "hashTable.h"
using namespace std;

Link::Link(void){

  myLink = NULL;

}
Link::Link(const char* myKey){
  myLink = NULL;
  strcpy(key, myKey);

}

void Link::setNextLink(Link* link){
  myLink = link;
  }

Link* Link::getNextLink(){
  return myLink;
}

void Link::setData(double data){
  this->data = data;
}

double Link::getData(void){
  return data;
}

double& Link::getDataReference(void){
  return data;
}

void Link::setKey(const char* myKey){
  strcpy(key, myKey);  
}

char* Link::getKey(void){
  return key;
}

HashTable::HashTable(int leng){
  length = leng;
  int z = 2;
  while(z<=length-1){
    if(length%z==0){
      exit(2);
    }
    z++;
  }
  table = new Link*[length];
  for(int i = 0; i < length; i++){
      table[i] = NULL;
    }
}

void HashTable::add(double data, const char* key){
  int x;
  x = Hash(key).hash()%length;
  Link* tmp = table[x];
  table[x] = new Link(key);
  table[x]->setData(data); 
  table[x]->setNextLink(tmp);
}

HashTable::HashTable(){
 length = 101;
 table = new Link*[length];
 for(int i = 0; i < length; i++){
   table[i] = NULL;
 }
}

HashTable::HashTable(const HashTable& hashbrowns){
  length = hashbrowns.length;
  table = new Link*[length];
  for(int i = 0; i < length; i++){
    table[i] = NULL;
  }
  
  for(int i =0;i < length; i++){
    Link* temp = hashbrowns.table[i];
    Link* curTemp = NULL;
    while(temp != NULL){
      if(curTemp == NULL){
	table[i] = new Link(temp->getKey());
	curTemp = table[i];
	curTemp->setData(temp->getData());
      }
      else{
	curTemp->setNextLink(new Link(temp->getKey()));
	curTemp = (curTemp->getNextLink());
	curTemp->setData(temp->getData());
      }
      temp=temp->getNextLink();
    }
  }
}

HashTable& operator +=(HashTable& hashbrowns, const char* key){
  if(hashbrowns.inTable(key) == false){
  hashbrowns.add(0, key);
  }
  else
    exit(1);
  return hashbrowns;
}

ostream& operator <<(ostream& out, const HashTable& s){
  for(int i = 0; i< s.length;i++){
    Link* temp = s.table[i];
    if(s.table[i]!=NULL){
      out<<"Index: "<<i<<"; ";
      while(temp!=NULL){
	out<<"("<<temp->getKey()<<", "<<temp->getData()<<")"<<" ";
	temp = temp->getNextLink();
      }
      out<<endl;
    }
  }
  return out;
}

double& HashTable::operator [](char* key){
  int x= Hash(key).hash()%length;
  Link* tmp = table[x];
  while(tmp!=NULL){
    if(strcmp(tmp->getKey(), key)==0)
      return tmp->getDataReference();
    tmp = tmp->getNextLink();
  }
  add(0, key);
  return table[x]->getDataReference();
}

double HashTable::operator [](char* key)const{
  int x= Hash(key).hash()%length;
  Link* tmp = table[x];
  while(tmp!=NULL){
    if(strcmp(tmp->getKey(), key)==0)
      return tmp->getData();
    tmp = tmp->getNextLink();
  }
  exit(4);
}

bool HashTable::inTable(const char* aString) const{
  int x;
  x = Hash(aString).hash()%length;
  Link* tmp = table[x];
  while(tmp!=NULL){
    if(strcmp((tmp->getKey()), aString) ==0)
       return true;
    tmp = tmp->getNextLink();
       }
  return false;
}
