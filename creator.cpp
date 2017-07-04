#include "tree.hpp"
#include "hash.hpp"

#define F 6 // number of files

void Hash::make_hashtable(string* filename, Hashtable<string>* hasht) {	
	// count strings in a file
	long M = 0;
	for (int i = 0; i < F; i++)
		M += count_strings(filename[i]);

	// get an array of words
	string* word = new string[M]; // array of M words
	long count = 0;
	for (int i = 0; i < F; i++)
		fill_array(filename[i], word, count);

	for (long i = 0; i < M; i++)
		hasht->hashtab_add(word[i]);

	delete[] word;
}

void AVL::make_tree(string* filename, AVLNode<string>*& root) {	
	// count strings in a file
	long M = 0;
	for (int i = 0; i < F; i++)
		M += count_strings(filename[i]);

	// get an array of words
	string* word = new string[M]; // array of M words
	long count = 0;
	for (int i = 0; i < F; i++)
		fill_array(filename[i], word, count);

	for (long i = 0; i < M; i++)
	  	root = root->AVL_add(word[i]);

	delete[] word;
}