#ifndef LIST_HPP
#define LIST_HPP

#include <cassert>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ctime>

#define N 18919// number of hash table = prime number

using namespace std;

namespace List {

	typedef string T;
	//typedef int T;

	struct PNode {
		T key;
		struct PNode* next; // a pointer to the next element
	};

	PNode* init(T);
	PNode* add(PNode*, T); 

	int loop_length(PNode*, bool&);
	PNode* loop_beginning(PNode*, PNode*);
	PNode* find_loop(PNode*, int&, bool&);

 	PNode* inverse(PNode*);

	void print(PNode*);

	void deleteM(PNode*, int);

	void free_list(PNode*);
}

	long count_strings(string);
	void fill_array(string, string*, long&);

#endif