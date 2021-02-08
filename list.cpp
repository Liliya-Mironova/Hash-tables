#include "list.hpp"

using namespace List;

// list creation
PNode* List::init(T a) { // а is the value of the first node
  PNode* head = new PNode;
  head->key = a;
  head->next = nullptr; // it is the last node of the list
  
  return head;
}

// adding a new node to the end of a list
PNode* List::add(PNode* head, T a) {
  assert (head); // if head = 0 then q = 0 then q->next will fail
  
  PNode* q = head;
  if (q->key == a) // we will not add the same words
      return nullptr;
  while (q->next) {
    q = q->next;
    if (q->key == a) // we will not add the same words
      return nullptr;
  }
  
  PNode* p = new PNode;
  p->key = a;
  p->next = nullptr;
  q->next = p;

  return p;
}
//-----------------------------------------------------------------------
// calculate the length of the loop
int List::loop_length(PNode* hare, bool& is_loop) {
  PNode* l1 = hare;
  PNode* l2 = hare;
  int length_loop = 0;
  do {
    length_loop++;
    l2 = l2->next;
  } while (l1 != l2);

  is_loop = true;

  return length_loop;
}

// find the begenning of the loop
PNode* List::loop_beginning(PNode* head, PNode* hare) {
  PNode* tortoise = head;
  while (tortoise != hare) {
    tortoise = tortoise->next;
    hare = hare->next; // the last hare is the place of meeting
  }

  return hare;
}
  
// is the list cycled or uncycled?
PNode* List::find_loop(PNode* head, int& length, bool& is_loop) {
  assert (head);

  PNode* tortoise = head; // slow pointer increments of 1
  PNode* hare = head; // fast pointer increments of 2
  while (hare->next) {
    if (!hare->next->next) {
      is_loop = 0;
      return nullptr;
    }
    tortoise = tortoise->next;
    hare = hare->next->next;
    if (tortoise == hare) // the meeting
      break;
  }
    
  if (!hare->next) {
    is_loop = 0;
    return nullptr; // there is no loop
  }

  hare = loop_beginning(head, hare);
  length = loop_length(hare, is_loop);

  return hare;
}
//-----------------------------------------------------------------------

// returns a list in reverse order
PNode* List::inverse(PNode *head) {
  assert (head); // can not inverse an empty list

  PNode* p = nullptr;
  PNode* tmp = nullptr;
  while (head) {
    tmp = head->next;
    head->next = p;
    p = head;
    head = tmp;
  }

  return p;
}
//-----------------------------------------------------------------------

// print list
void List::print(PNode* head) {
  assert (head); // can not print an empty list

  int length;
  bool is_loop;
  PNode* first_loop = find_loop(head, length, is_loop);

  // print a line
  PNode* p = head;
  do {
    cout << p->key << " ";
    p = p->next;
  } while (p != first_loop);
   
  // print a loop
  if (first_loop) {
    printf("loop: ");
    cout << p->key << " ";
    p = p->next;
    while (p != first_loop) {
      cout << p->key << " ";
      p = p->next;
    }
  }
}
//-----------------------------------------------------------------------

void List::deleteM(PNode* head, int m) {
  assert (m > 0);

  PNode* q = head;

  int length;
  bool is_loop;
  PNode* first_loop = find_loop(head, length, is_loop);
  assert (q && q->next && is_loop);
   
  if (m == 2) { // particular case
    int i = length;
    while (i > 0) {
      if (!(i & (i - 1))) // max i, which is (2^d), (2^d) < length
        break;
      i--;
    }
    cout << endl<< "alive: " << (length - i) * 2 + 1;
  }

  else {
    int p = 1;
    while (q->next->key != q->key) {
      for (int i = 1; i < m - 1; i++)
        q = q->next;
      PNode* tmp = q->next;
      cout << endl << tmp->key << "deleted"; 
      q->next = tmp->next;
      delete tmp;
      q = q->next;
      p++;
    }
    cout << endl << "alive: " << q->key;  
  }
}
//-----------------------------------------------------------------------

// delete list
void List::free_list(PNode* head) {
  assert (head); // can not delete an empty list
  int length;
  bool is_loop;
  PNode* first_loop = find_loop(head, length, is_loop);
  PNode* tmp = nullptr;
	
	if (first_loop != head) {
		// clear a line
		do {
		  tmp = head;
		  head = head->next;
		  delete tmp;
		} while (head != first_loop);
	} 
		// clear a loop
	tmp = head;
	if (first_loop) { 
	  for (int k = 0; k < length; k++) {
	    tmp = head;
	    head = head->next;
	    delete tmp;
	  }
	}
}