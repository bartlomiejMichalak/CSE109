//Bart Michalak
//Bpm215
//cse109.133 Final
//Summer session II

#include "node.h"

Node::Node(int val){
  nodeVal = val;
  numOfLinks++;
}

Node::Node(){}

int main(int argc, char** argv) {
  Vault v;
  v.put("Lehigh", 43);
  v.put("lemon", 54);
  v.put("cse 109", 1);
  v.put("lemonade", 13);

  cout << v.get("lemon") << "  " << v.get("Lehigh") << endl;
  cout << v.get("cse 109") << endl;
  cout << v.get("error") <, endl;

  v += "book";
  cout << "book = " << v.get("book") << endl;

}
