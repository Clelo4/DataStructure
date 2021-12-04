#ifndef _SKIP_LIST_H
#define _SKIP_LIST_H
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  Node *next;
  Node *son;
  int data;
  Node(int data = -1, Node *next = NULL, Node *son = NULL) : data(data), next(next), son(son){};
};

class Skiplist {
private:
  Node *head;
  vector<Node *> preStack;

public:
  Skiplist();
  ~Skiplist();

  bool search(int target);
  void add(int num);
  bool erase(int num);
};

#endif