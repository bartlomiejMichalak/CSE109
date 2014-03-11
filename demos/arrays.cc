#include <iostream>

using namespace std;

int sum(const int a[], int size, int& wsum);

void fcn(int arr*[10]) {
}

int main(int argc, char** argv) {

  const int SIZE_OF_ARRAY = 3;
  // base type = int, declaring and defining 
  int numbs[7] = { 1, 2, 3, 4, 5 }, a[SIZE_OF_ARRAY];
  int m[5][10];

  fcn(m);
  
  a[0] = 10;
  a[1] = 11;
  a[2] = 12;

  m[0][0] = 12;
   
  cout << sizeof numbs/ sizeof(int) << endl;
  
  for (int i=0; i < 7; ++i) {
    cout << numbs[i] << endl;    
  }
  
  for (int i=0; i < 3; ++i) {
    cout << a[i] << endl;    
  }

  int xsum;
  int  mysum = sum(a, SIZE_OF_ARRAY, xsum);
  cout << mysum << xsum << endl;
  return 0;
  
}



int sum(const int a[], int size, int& wsum) {
  int s = 0;
  for (int i=0; i < size; ++i) {
    s += a[i];
  }
  wsum = s;
  return s;
}
