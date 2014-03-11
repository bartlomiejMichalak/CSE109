
int main(int argc, char** argv) {
  Vault v;
  v.put("Lehigh", 43);
  v.put("lemon", 54);
  v.put("cse 109", 1);
  v.put("lemonade", 13);

  cout << v.get("lemon") << "  " << v.get("Lehigh") << endl;
  cout << v.get("cse 109") << endl;
  cout << v.get("error") << endl;

  v += "book;
  cout << "book = " << v.get("book") << endl;

  /* Extra credit

  Vault v2(v);
  cout << v2.get("Lehigh") << endl;
  v2.put("lestoil", 23);
  cout << v2.get("lestoil") << endl;
  cout << v.get("lestoil") << endl;

  */
}
