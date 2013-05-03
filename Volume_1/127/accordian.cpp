#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

struct Card{
  char suit;
  char rank;
};

class Node{
public:  
  Node(char suit_, char rank_) {
    Card card;
    card.suit = suit_;
    card.rank = rank_;
    pile.push(card);
    next = NULL; 
    prev = NULL;
  }
  
  Node* next;
  Node* prev;
  stack<Card> pile;

  char getSuit() {
    if (!pile.empty()) 
      return pile.top().suit;
    else
      return 0; // should not happen
  }

  char getRank() {
    if (!pile.empty()) 
      return pile.top().rank;
    else
      return 0; // should not happen
  }

  bool empty() {
    return pile.empty();
  }

  void erase() {
    // basciall re-connect its next & prev
    if (next != NULL) 
      next -> prev = prev;
    if (prev != NULL)
      prev -> next = next;
  }
};

bool match(Node* n1, Node* n2) {
  if (n1 == NULL || n1->empty() 
     || n2 == NULL || n2->empty())
    return false;
  else
    return (n1->getSuit() == n2->getSuit() 
       || n1->getRank() == n2->getRank());
}

int NUM_PILES;
void fold(Node* n1, Node* n2) {
  if (n1 == NULL || n1->empty() 
     || n2 == NULL || n2->empty()) {
    cout << "DUMB" << endl;
    return;
  }
  Card card = n2->pile.top();
  n2->pile.pop();
  n1->pile.push(card);
  if (n2->empty()) {
    n2->erase();
    delete n2;
    NUM_PILES--;
  }
}

// must exact k
Node* nextK(Node* n, int k) {
  int cnt = 0;
  while (n != NULL && cnt < k) {
    n = n -> next;
    cnt++;
  }
  return cnt == k ? n : NULL;
}


// must exact k
Node* prevK(Node* n, int k) {
  int cnt = 0;
  while (n != NULL && cnt < k) {
    n = n -> prev;
    cnt++;
  }
  return cnt == k ? n : NULL;
}

void dump(Node* head) {
  Node* cur = head;
  string many = NUM_PILES > 1 ? "s" : "";
  cout << NUM_PILES << " pile" << many << " remaining:"; 
  while (cur != NULL) {
    cout << " " << cur->pile.size() ;
    cur = cur->next;
  }
  cout << endl;
}

void release(Node* head) {
  if (head->next != NULL) {
    release(head->next);
  }
  delete head;
}


int main() {
  string line1;
  string line2;
  while (getline(cin, line1)) {
    if (line1 == "#")
      break;
    // process line 1
    getline(cin, line2);
    string line = line1 + " " + line2;
    stringstream ss(line);
    string card;
    Node* head = NULL;
    Node* cur = head; 
    NUM_PILES = 52;

    while (ss >> card) {
      Node* node = new Node(card[0], card[1]);
      if (head == NULL) 
        head = node;
      node -> prev = cur;
      if (cur != NULL) 
        cur -> next = node;
      cur = node;
    }
        // do simulation here
    cur = head;
    while (cur != NULL) {
      Node* p3 = prevK(cur, 3);
      Node* p1 = cur->prev;
      if (match(p3, cur)) {
        fold(p3, cur);     
        cur = p3;
      } else if (match(p1, cur)) {
        fold(p1, cur);
        cur = p1;
      } else {
        cur = cur->next;
      }
    }
    dump(head);
    release(head); 
  }

}
