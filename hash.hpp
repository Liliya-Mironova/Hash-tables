#ifndef HASH_HPP
#define HASH_HPP

#include "list.hpp"

#define N 18919 // number of hash table = prime number

using namespace std;
using namespace List;

namespace Hash {

	template <typename T>
	class Hashtable final {
		PNode* hashtab[N];
		
		public:
		Hashtable();
		Hashtable(const Hashtable<T>&);
		Hashtable(Hashtable<T>&&);
		~Hashtable();

		Hashtable<T> operator=(const Hashtable<T>&);
		Hashtable<T> operator=(Hashtable<T>&&);

		void hashtab_add(T);
		PNode* hashtab_find(T) const;
		void hashtab_delete(T);
		void hashtab_print() const;
		void hashtab_analyze(int&, int&) const;
	};

	unsigned hash_mod(string);
	unsigned hash_Fib(string);
	unsigned hash_PJW(string);

	void make_hashtable(string*, Hashtable<string>*);
//----------------------------------------------------------------------

	// default constructor
	template <typename T>
	Hashtable<T>::Hashtable() {
		for (int i = 0; i < N; i++)
    		hashtab[i] = nullptr;
	}

	// copy constructor
	template <typename T>
	Hashtable<T>::Hashtable(const Hashtable<T>& other) {
		for (int i = 0; i < N; i++)
    		hashtab[i] = other.hashtab[i];
	}
	
	// move constructor
	template <typename T>
	Hashtable<T>::Hashtable(Hashtable<T>&& other) {
		for (int i = 0; i < N; i++) {
    		hashtab[i] = other.hashtab[i];
    		other.hashtab[i] = nullptr; // ???
    	}
	}
	
	template <typename T>
	Hashtable<T>::~Hashtable() {
		for (int i = 0; i < N; i++)
			if (hashtab[i])
    			free_list(hashtab[i]);
	}

	// copy assignment
	template <typename T>	
	Hashtable<T> Hashtable<T>::operator=(const Hashtable<T>& other) {
		if (this != &other) {
			for (int i = 0; i < N; i++) {
				if (hashtab[i])
    				free_list(hashtab[i]);
    			hashtab[i] = other.hashtab[i];
    		}
		}

		return *this;
	}
	
	// move assignment
	template <typename T>
	Hashtable<T> Hashtable<T>::operator=(Hashtable<T>&& other) {
		if (this != &other) {
			for (int i = 0; i < N; i++) {
				if (hashtab[i])
    				free_list(hashtab[i]);
    			hashtab[i] = other.hashtab[i];
    			other.hashtab[i] = nullptr;
    		}
		}

		return *this;
	}

	template <typename T>
	void Hashtable<T>::hashtab_add(T word) {
	  unsigned index = hash_Fib(word);

	  if (!hashtab[index]) {
	    hashtab[index] = init(word); // create a node and attach it to an array of lists
	  } else // collision
	    PNode* node  = add(hashtab[index], word); // attach a node to a list
	}

	template <typename T>
	PNode* Hashtable<T>::hashtab_find(T word) const {
	  assert(hashtab);

	  unsigned index = hash_Fib(word);

	  for (PNode* node = hashtab[index]; node; node = node->next) // find a word's cell according to its hash 
	    if (node->key == word) { // search the word in a list
	       cout << "Node: " << word << endl;
	      return node;
	    }

	  cout << "'" << word << "' not found" << endl;
	  return nullptr;
	}

	// delete an element
	template <typename T>
	void Hashtable<T>::hashtab_delete(T word) {
	  assert(hashtab);
	  
	  PNode *prev = nullptr;
	  unsigned index = hash_Fib(word);

	  for (PNode* node = hashtab[index]; node; node = node->next) {
	    if (node->key == word) { // search the word in a list
	      if (!prev) // no collision
	        hashtab[index] = node->next;
	      else // collision
	        prev->next = node->next;
	      delete node;
	      cout << "'" << word << "' deleted" << endl;
	      return;
	    }
	    prev = node;
	  }
	  cout << "'" << word << "' not found to delete" << endl;
	}

	template <typename T>
	void Hashtable<T>::hashtab_print() const {
	  assert(hashtab);

	  cout << endl << "Hash table" << endl;

	  for (int i = 0; i < N; i++) {
	  	if (!hashtab[i])
	  		cout << "[" << i << "] -";
	   	for (PNode* node = hashtab[i]; node; node = node->next)
	   		cout << "[" << i << "] " << node->key;
	   	cout << endl;
	  }
	  cout << endl;
	}

	// calculate max length and a number of collisions in the hashtable
	template <typename T>
	void Hashtable<T>::hashtab_analyze(int& max, int& collisions) const {
	  assert(hashtab);

	  max = 0, collisions = 0;
	  for (int i = 0; i < N; i++) {
	    int j = 0;
	    for (PNode* node = hashtab[i]; node; node = node->next)
	      j++;
	    if (j > max)
	      max = j;
	    if (j)
	      collisions += j - 1;
	  }
	  	cout << endl << "number of rows = " << N << endl << "max length = " << max << endl << "number of collisions = " << collisions << endl;
	}
}

#endif