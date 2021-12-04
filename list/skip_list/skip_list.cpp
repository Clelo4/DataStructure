#include "skip_list.h"
#include <stdlib.h>
#include <limits.h>

Skiplist::Skiplist() { head = new Node(); }

Skiplist::~Skiplist() {
  Node *curHead = head;
  while (curHead) {
    Node *pre = curHead;
    curHead = curHead->son;
    while (pre) {
      Node *t = pre;
      pre = pre->next;
      delete t;
    }
  }
}

bool Skiplist::search(int target) {
  Node *pre = head;
  while (pre) {
    while (pre->next) {
      if (pre->next->data == target) {
        return true;
      } else if (pre->next->data < target) {
        pre = pre->next;
      } else {
        break;
      }
    }
    pre = pre->son;
  }
  return false;
}

void Skiplist::add(int num) {
  preStack.clear();
  Node *pre = head;
  while (pre) {
    while (pre->next) {
      if (pre->next->data >= num) {
        preStack.push_back(pre);
        break;
      } else {
        pre = pre->next;
      }
    }
    pre = pre->son;
  }
  bool insertUp = true;
  Node *newNode = NULL;
  while (insertUp && preStack.size()) {
    Node *pre = preStack.back();
    preStack.pop_back();
    newNode = new Node(num, pre->next, newNode);
    pre->next = newNode;

    insertUp = (rand() & 4) == 0;
  }
  if (insertUp) {
    head = new Node(-1, new Node(num, NULL, newNode), head);
  }
}

bool Skiplist::erase(int num) {
  Node *pre = head;
  Node *preHead = NULL;
  Node *preFather = NULL;
  bool result = false;
  while (pre) {
    while (pre->next) {
      if (pre->next->data == num) {
        // 处理重复元素的情况
        if (preFather == NULL) {
          preHead = preFather = pre->next;
          pre->next = pre->next->next;
          result = true;
          break;
        } else if (preFather->son != pre->next) {
          pre = pre->next;
        } else {
          preFather = pre->next;
          pre->next = pre->next->next;
          result = true;
          break;
        }
      } else if (pre->next->data < num) {
        pre = pre->next;
      } else {
        break;
      }
    }
    pre = pre->son;
  }
  while (preHead) {
    Node *t = preHead;
    preHead = preHead->son;
    delete t;
  }
  return result;
}