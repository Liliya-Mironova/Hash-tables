#include "tree.hpp"
#include "hash.hpp"

#define F 6 // number of files

using namespace AVL;
using namespace Hash;

int main() {
	string filename[F] = {"english.txt", "german.txt", "italian.txt", "hungarian.txt", "swedish.txt", "names.txt"};
		
	// make a hashtable with these words
	clock_t time_create_h = clock();
	Hashtable<string>* hasht = new Hashtable<T>;
	make_hashtable(filename, hasht);
	time_create_h = clock() - time_create_h;
	printf("\nCreate hash time: %f\n", static_cast<double>(time_create_h)/CLOCKS_PER_SEC);

	// SEARCH:
	clock_t time_search_h = clock();
	PNode* p1 = hasht->hashtab_find("hello");
	time_search_h = clock() - time_search_h;
	printf("Search hash time: %f\n", static_cast<double>(time_search_h)/CLOCKS_PER_SEC);

	// DELETE:
	clock_t time_delete_h = clock();
	hasht->hashtab_delete("sun");
	time_delete_h = clock() - time_delete_h;
	printf("Delete hash time: %f\n", static_cast<double>(time_delete_h)/CLOCKS_PER_SEC);

	int max, collisions;
	hasht->hashtab_analyze(max, collisions);

	PNode* p2 = hasht->hashtab_find("sun");

	delete hasht;

	printf("//------------------------------------------------------------------\n");
	
	// make a tree with these words
	clock_t time_create_t = clock();
	AVLNode<string>* root = new AVLNode<string>;
	make_tree(filename, root);
	time_create_t = clock() - time_create_t;
	printf("Create tree time: %f\n", static_cast<double>(time_create_t)/CLOCKS_PER_SEC);

	// SEARCH:
	clock_t time_search_t = clock();
	AVLNode<string>* n1 = root->AVL_find("hello");
	time_search_t = clock() - time_search_t;
	printf("Search tree time: %f\n", static_cast<double>(time_search_t)/CLOCKS_PER_SEC);

	// DELETE:
	clock_t time_delete_t = clock();
	AVLNode<string>* n2 = root->AVL_delete("sun");
	time_delete_t = clock() - time_delete_t;
	printf("Delete tree time: %f\n", static_cast<double>(time_delete_t)/CLOCKS_PER_SEC);

	printf("\nHeight of tree: %d\n", root->height());

	AVLNode<string>* n4 = root->AVL_find("sun");

	delete root;

	return 0;
}

// g++ -std=gnu++11 list.cpp hashfunc.cpp filereader.cpp creator.cpp main.cpp