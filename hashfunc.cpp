#include "hash.hpp"

using namespace List;
using namespace Hash;
using namespace std;

unsigned Hash::hash_mod(string word) {
  unsigned h = 0;
  unsigned i = 0;
  while (i < word.length()) {
    h += word[i];
    i++;
  }

  return h % N;
}

// Fibonacci hash function
unsigned Hash::hash_Fib(string word) {
  unsigned h = 0;
  unsigned i = 0;
  while (i < word.length()) {
    h += word[i];
    i++;
  }
      
  double A = 0.618033; // A = (√5-1)/2 - golden section
  double intpart_hA, res; // integer parts
  double tmp2 = modf(N * modf(h * A, &intpart_hA), &res); // res = [N * {h * A}]
  unsigned hash = (unsigned)res;

  return hash;
}

// Weinberger's non-cryptographic hash function
unsigned Hash::hash_PJW(string word) {
  unsigned hash = 0, g;
  unsigned i = 0;
  while (i < word.length()) {
    hash = (hash << 4) + word[i];
    g = hash & 0xf0000000L;
    if (g)
      hash ^= g >> 24;
    hash &= ~g;
    i++;
  }

  return hash % N;
}