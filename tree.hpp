#ifndef TREE_HPP
#define TREE_HPP

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

namespace AVL {

	template <typename T>
	class AVLNode final {
		T key;
		unsigned h;
		AVLNode<T>* left;
		AVLNode<T>* right;

		public:
		AVLNode();
		explicit AVLNode(T k);
		AVLNode(const AVLNode<T>&);
		AVLNode(AVLNode<T>&&);
		~AVLNode();

		AVLNode<T>* operator=(const AVLNode<T>&);
		AVLNode<T>* operator=(AVLNode<T>&&);

		unsigned height() const;
		int bfactor() const;
		void fix_height();

		AVLNode<T>* rotate_right();
		AVLNode<T>* rotate_left();
		AVLNode<T>* balance();
		AVLNode<T>* AVL_add(T);
		
		AVLNode<T>* find_min() const;
		AVLNode<T>* delete_min();
		AVLNode<T>* AVL_find(T);
		AVLNode<T>* AVL_delete(T);
		
		void AVL_print() const;
		void AVL_free();

		T get_key() const;
	};
	
	void make_tree(string*, AVLNode<string>*&);
//----------------------------------------------------------------------

	// default constructor
	template <typename T>
	AVLNode<T>::AVLNode() {
		h = 0;
		right = nullptr;
		left = nullptr;
	}

	template <typename T>
	AVLNode<T>::AVLNode(T k) : key(k) {
		h = 1;
		right = nullptr;
		left = nullptr;
	}

	// copy constructor
	template <typename T>
	AVLNode<T>::AVLNode(const AVLNode& other) {
		key = other.key;
		left = other.left;
		right = other.right;
		h = other.h;
	}

	// move constructor
	template <typename T>
	AVLNode<T>::AVLNode(AVLNode<T>&& other) {
		key = other.key;
		left = other.left;
		right = other.right;
		h = other.h;

		other.key = nullptr;
		other.left = nullptr;
		other.right = nullptr;
		other.h = 0;
	}

	template <typename T>
	AVLNode<T>::~AVLNode() {
		key = nullptr;
		right = nullptr;
		left = nullptr;
		h = 0;
	}

	template <typename T>
	AVLNode<T>* AVLNode<T>::operator=(const AVLNode<T>& other) {
		if (this != &other) {
			key = other.key;
			left = other.left;
			right = other.right;
			h = other.h;	
		}

		return this;
	}

	template <typename T>
	AVLNode<T>* AVLNode<T>::operator=(AVLNode<T>&& other) {
		if (this != &other) {
			key = other.key;
			left = other.left;
			right = other.right;
			h = other.h;

			other.key = nullptr;
			other.left = nullptr;
			other.right = nullptr;
			other.h = 0;
		}

		return this;
	}

	// (additional) a height of a node
	template <typename T>
	unsigned AVLNode<T>::height() const {
		if (this)
			return h;
		return 0;
	}

	// (additional) a balance factor of a node
	template <typename T>
	int AVLNode<T>::bfactor() const {
		assert(this);

		return right->height() - left->height();
	}

	// (additional) - set a hight of a node
	template <typename T>
	void AVLNode<T>::fix_height() {
		assert(this);

		unsigned hl = left->height();
		unsigned hr = right->height();
		if (hl > hr)
			h = hl + 1;
		else
			h = hr + 1;
	}

	// right rotation around a node
	template <typename T>
	AVLNode<T>* AVLNode<T>::rotate_right() {
		assert(this);

		AVLNode* q = left;
		left = q->right;
		q->right = this;
		fix_height();
		q->fix_height();
		return q;
	}

	// left rotation around a node
	template <typename T>
	AVLNode<T>* AVLNode<T>::rotate_left() {
		assert(this);

		AVLNode* p = right;
		right = p->left;
		p->left = this;
		fix_height();
		p->fix_height();
		return p;
	}

	// balancing of a node
	template <typename T>
	AVLNode<T>* AVLNode<T>::balance() {
		assert(this);

		fix_height();
		if (bfactor() == 2) {
			if (right->bfactor() < 0)
				right = right->rotate_right();

			AVLNode* p = rotate_left();
			return p;
		}

		else if (bfactor() == -2) {
			if (left->bfactor() > 0)
				left = left->rotate_left();

			return rotate_right();
		}

		return this;
	}

	// add a node "k" in a tree
	template <typename T>
	AVLNode<T>* AVLNode<T>::AVL_add(T k) {
		if (h == 0) {
			h = 1;
			key = k;
			return this;
		}

		if (key > k) {
			if (!left)
				left = new AVLNode<T>; // здесь какая-то фигня
			left = left->AVL_add(k); // здесь какая-то фигня
		}
		else if (key <= k) {
			if (!right)
				right = new AVLNode<T>; //здесь какая-то фигня
			right = right->AVL_add(k); //здесь какая-то фигня
		}

		return balance();
	}

	// (additional) search a node with minimal key in a tree
	template <typename T>
	AVLNode<T>* AVLNode<T>::find_min() const {
		assert(this);

		AVLNode<T>* tmp;
		while (left)
			tmp = left;
		return tmp;
	}

	// (additional) delete a node with minimal key in a tree
	template <typename T>
	AVLNode<T>* AVLNode<T>::delete_min() {
		if (!left)
			return right;

		left = left->delete_min();
		return balance();
	}

	// search a node "k" in a tree
	template <typename T>
	AVLNode<T>* AVLNode<T>::AVL_find(T k) {
		assert(this);
		
		AVLNode<T>* tmp = this;
		while (tmp) {
			if (tmp->key == k) {
				cout << "Node: " << k << endl;
				return tmp;
			}
			if (tmp->key > k)
				tmp = tmp->left;
			else if (tmp->key < k)
				tmp = tmp->right;
		} 

		cout << "'" << k << "' not found" << endl;
		return nullptr;
	}

	// delete a node "k" from a tree
	template <typename T>
	AVLNode<T>* AVLNode<T>::AVL_delete(T k) {
		assert(this);

		AVLNode* tmp = this;
		tmp = tmp->AVL_find(k);
		if (tmp) {
			AVLNode* q = tmp->left;
			AVLNode* r = tmp->right;
			cout << "'" << tmp->key << "' deleted" << endl;
			//delete tmp;
			tmp->left = nullptr;
			tmp->right = nullptr;
			if (!r) 
				return q;
			AVLNode* min = r->find_min();
			min->right = r->delete_min();
			min->left = q;
			return min->balance();
		}

		return balance();
	}

	// print a tree
	template <typename T>
	void AVLNode<T>::AVL_print() const {
		assert(this);

	    if (left)
	    	left->AVL_print();
	    if (right)
	    	right->AVL_print();
	    
	    cout << h << ": " << key << endl;
	}

	// delete a tree
	template <typename T>
	void AVLNode<T>::AVL_free() {
	    if (!this) return; 
	        
	    if (left) { 
	        left->AVL_free(); 
	        left = nullptr; 
	    }
	    
	    if (right) { 
	        right->AVL_free(); 
	        right = nullptr; 
	    }
	    delete this;  
	}

	template <typename T>
	T AVLNode<T>::get_key() const {
		return key;
	}
}

#endif