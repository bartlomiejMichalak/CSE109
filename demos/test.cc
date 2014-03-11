#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  char *b;
  char a[3];
  a[0] = 'a';
  a[1] = 'b';
  a[2] = '\0';
  char c = a[0];
  cout << a << endl;
  b = a;
  cout << ++b << endl;

  cout << c << endl;

  b = &c;
  cout << *b << endl;
  
  return 0;

  
}
