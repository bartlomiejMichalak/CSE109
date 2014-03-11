#include <iostream>

using namespace std;

string toupper(string& s)
{
  string ret(s.size(), char());
  for(int i = 0; i < s.size(); ++i)
    ret[i] = (s[i] <= 'z' && s[i] >= 'a') ? s[i]-('a'-'A') : s[i];
  return ret;
}

string tolower(string& s)
{
  string ret(s.size(), char());
  for(int i = 0; i < s.size(); ++i)
    ret[i] = (s[i] <= 'Z' && s[i] >= 'A') ? s[i]+('a'-'A') : s[i];
  return ret;
}


int main(int argc, char** argv) {

  string line;

  if (argc < 2) {
    cerr << "Usage: ccase (upper|lower)\n";
    return 1;
  }

  if (strcmp(argv[1],"upper") != 0 && strcmp(argv[1],"lower") != 0) {
    cerr << "Usage: ccase (upper|lower)\n";
    return 1;
  }

  bool isUpper = false;

  if (strcmp(argv[1],"upper") == 0)
    isUpper = true;
  
  while (getline(cin, line)) {
    if (isUpper)
      cout << toupper(line) << endl;
    else
      cout << tolower(line) << endl;
  }

  return 0;
  
}

