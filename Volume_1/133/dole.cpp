#include <iostream>
using namespace std;

class Node{
public:
  int index; 
  Node* next;
  Node* prev;
  bool active; 
  Node(int index_) {
    index = index_;
    active = true;
  }
};

void dump(Node* head) {
  Node* node = head;
  if(head == NULL)
    return;
  do {
    cout << node->index << ",";
    node = node->next;
  } while (node != head);
  cout << endl;
}

int main () {
  int n, m, k;
  while (cin >> n >> k >> m) {
    if (n == 0 && k == 0 && m == 0)
      break;
    // 1. build linked list
    Node* head = new Node(1);
    Node* tail = head;
    for (int i = 2; i <= n; ++i) {
      Node* node = new Node(i);
      node->prev = tail;
      tail->next = node;
      tail = node;
    }
    tail->next = head;
    head->prev = tail;
    //dump(head);
    
    int cnt = 0;
    while(1) {
      int k_cnt = 0, m_cnt = 0;
      while(1) {
        if (head->active == true) 
          k_cnt++;
        
        if (k_cnt == k)
          break;
        head = head->next;
      }
      while(1) {
        if (tail->active == true)
          m_cnt++;
        if (m_cnt == m)
          break;
        tail = tail->prev;
      }
      if (head->index == tail->index) {
        cnt++;
        cout.width(3);
        cout << head->index;
        head->active = false;
      }
      else {
        cnt += 2;
        cout.width(3);
        cout << head->index;
        cout.width(3);
        cout << tail->index; 
        head->active = false;
        tail->active = false;
      }
      if (cnt == n) {
        cout << endl;
        break;
      }
      else 
        cout << ",";
    }
  }

}
