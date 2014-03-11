#include "hashTable.h"



void x(const HashTable &h);

int main(){
  HashTable p(5), q(101);
  (((q += "Lehigh") += "Lafayette") += "DeSales") += "Kutztown";
  q["Moravian"] = 14;
  cout << "Here is q:\n" << q << endl;
  HashTable r(q);
  r["Cedar Crest"] = 14;
  q["Alvernia"] = 29;
  cout << "Here is q:\n" << q << "\nHere is r:\n" << r << endl;
  HashTable w(300); //should crash, because non-prime table size
}

void x(const HashTable &h){
  if(h.inTable(0))
    cout << "Here is h[0]: " << h[0] << endl;
}


/*

Here is q:
-----------[ 18]------
(Lafayette, 0)
-----------[ 21]------
(Moravian, 14)
-----------[ 67]------
(DeSales, 0)
-----------[ 78]------
(Kutztown, 0)
-----------[ 88]------
(Lehigh, 0)

Here is q:
-----------[ 10]------
(Alvernia, 29)
-----------[ 18]------
(Lafayette, 0)
-----------[ 21]------
(Moravian, 14)
-----------[ 67]------
(DeSales, 0)
-----------[ 78]------
(Kutztown, 0)
-----------[ 88]------
(Lehigh, 0)

Here is r:
-----------[ 14]------
(Cedar Crest, 14)
-----------[ 18]------
(Lafayette, 0)
-----------[ 21]------
(Moravian, 14)
-----------[ 67]------
(DeSales, 0)
-----------[ 78]------
(Kutztown, 0)
-----------[ 88]------
(Lehigh, 0)

ERROR[HashTable]: (HashTable()) Need positive prime number for table size

 */

