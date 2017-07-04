#include "list.hpp"
#include "tree.hpp"

// count a number of strings in a file
long count_strings(string filename) {
	ifstream fin(filename);
  assert(fin.is_open());

	long M = 0;
  string str;
  while (!fin.eof())
    while (getline(fin, str))
      M++;

  str.erase();
  fin.close();
  return M;
}

// make an array of words
void fill_array(string filename, string* word, long& count) {

	ifstream fin1(filename);
  assert(fin1.is_open());

  string str;

  while (!fin1.eof()) {
    getline(fin1, str);
    word[count] = str;
    count++;
    str.erase();
  }

  fin1.close();
}