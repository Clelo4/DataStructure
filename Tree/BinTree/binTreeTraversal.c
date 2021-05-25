//
//  binTree.c
//  data_structure
//
//  Created by jack on 2020/12/10.
//

#include "binTree.h"
#include "stack/stack.h"

// 递归实现
void __pre_order_traversal_recure(BinTree b) {
    if (b) {
        printf("%d", b->data);
        __pre_order_traversal_recure(b->left);
        __pre_order_traversal_recure(b->right);
    }
}
void __in_order_traversal_recure(BinTree b) {
    if (b) {
        __in_order_traversal_recure(b->left);
        printf("%d", b->data);
        __in_order_traversal_recure(b->right);
    }
}
void __post_order_traversal_recure(BinTree b) {
    if (b) {
        __post_order_traversal_recure(b->left);
        __post_order_traversal_recure(b->right);
        printf("%d", b->data);
    }
}
int __tree_hight_recure(BinTree b) {
  if (!b) {
    return 1;
  }
  int left_hight = __tree_hight_recure(b->left);
  int right_hight =  __tree_hight_recure(b->right);
  if (left_hight > right_hight) {
    return left_hight + 1;
  } else {
    return right_hight + 1;
  }
}

typedef struct __tree_stack_node* __Tree_Stack_Node;
struct __tree_stack_node
{
  BinTree tree;
  __Tree_Stack_Node pre;
};
typedef struct __stack* __Stack;
struct __stack
{
  int size;
  __Tree_Stack_Node top;
};
// 创建一个stack
__Stack __stack_new() {
  __Stack new_stack = calloc(1, sizeof(struct __stack));
  new_stack->size = 0;
  new_stack->top = NULL;
  return new_stack;
}
// 判断stack是否为空
int __stack_is_empty(__Stack s) {
  return s->top == NULL;
}
// 从stack顶部弹出一个元素
BinTree __stack_pop(__Stack s) {
  if (!s) return NULL;
  __Tree_Stack_Node newTarget = s->top;
  if (!newTarget) return NULL;
  BinTree result = newTarget->tree;
  s->top = s->top->pre;
  free(newTarget);
  // s->size--;
  return result;
}
// 入栈
void __stack_push(__Stack s, BinTree tree) {
  if (!s) return;
  if (!tree) return;
  __Tree_Stack_Node newTarget = calloc(1, sizeof(struct __tree_stack_node));
  newTarget->tree = tree;
  newTarget->pre = s->top;
  s->top = newTarget;
  // s->size++;
  return;
}
// 取得栈顶元素，但不删除元素
BinTree __stack_top(__Stack s) {
  return s->top->tree;
}
// 删除整个堆栈
void __stack_free(__Stack s) {
  __Tree_Stack_Node start = s->top;
  __Tree_Stack_Node target = NULL;
  while (start) {
    target = start;
    start->pre = NULL;
    free(target);
  }
  free(s);
}

// 迭代实现，使用堆栈实现
void __pre_order_traversal_iterate(BinTree b) {
  if (!b) return;
  __Stack stack = __stack_new();
  BinTree target = b;
  __stack_push(stack, target);
  while (!stack_is_empty(stack)) {
    target = __stack_pop(stack);
    printf("%d\n", target->data);
    if (target->right) __stack_push(stack, target->right);
    if (target->left) __stack_push(stack, target->left);
  }
}
void __in_order_traversal_iterate(BinTree b) {
  if (!b) return;
  __Stack s = __stack_new();
  BinTree target = b;
  while (1) {
    while (target) {
      __stack_push(s, target);
      target = target->left;
    }
    if (!__stack_is_empty(s)) {
      BinTree parent = __stack_pop(s);
      printf("%d\n", parent->data);
      target = parent->right;
    } else {
      break;
    }
  }
  // __stack_free(s);
}
void __post_order_traversal_iterate(BinTree b) {
  if (!b) return;
  BinTree target = b;
  BinTree t = NULL;
  BinTree last = NULL;
  __Stack s = __stack_new();
  while (1) {
    while (target) {
      __stack_push(s, target);
      target = target->left;
    }
    if (stack_is_empty(s)) break;
    else {
      t = __stack_top(s);
      if (!t->right || last == t->right) {
        t = __stack_pop(s); last = t;
        printf("%d\n", t->data);
      } else {
        target = t->right;
      }
    }
  }
}
// 求树高度（非递归实现）
int __tree_hight_iterate(BinTree b) {
  if (!b) exit(EXIT_FAILURE);
  __Stack s = __stack_new();
  BinTree target = b;
  BinTree last = NULL;
  Stack count = stack_new(10000);
  while (1) {
    while (target) {
      __stack_push(s, target);
      target = target->left;
    }
    if (!__stack_is_empty(s)) {
      BinTree parent = __stack_top(s);
      BinTree right = parent->right;
      if (!right || right == last) {
        BinTree parent = __stack_pop(s);
        last = parent;
        // int left_Height = stack_pop(count);
        // stack_push(count, left_Height + 1);
        int parent_height = 1;
        int left_height = 0;
        int right_height = 0;
        if (parent->left && parent->right) {
          right_height = stack_pop(count);
          left_height = stack_pop(count);
        } else if (parent->left) {
          left_height = stack_pop(count);
        } else if (parent->right) {
          right_height = stack_pop(count);
        } else {}
        // 重新计算高度
        parent_height = (left_height > right_height) ? (left_height + 1) : (right_height + 1);
        stack_push(count, parent_height);
      } else {
        target = right;
      }
    } else {
      break;
    }
  }
  int result = stack_pop(count);

  __stack_free(s);
  stack_free(count);
  return result;
}

// queue for level order traversal
typedef struct __queue_node* __Queue_Node;
struct __queue_node {
  BinTree tree;
  __Queue_Node next;
};
typedef struct __queue* __Queue;
struct __queue {
  int length;
  __Queue_Node first;
  __Queue_Node last;
};
__Queue __queue_new() {
  __Queue q = calloc(1, sizeof(struct __queue));
  q->length = 0;
  q->first = q->last = NULL;
  return q;
}
int __queue_is_empty(__Queue q) {
  return q->length == 0;
}
int __queue_length(__Queue q) {
  return q->length;
}
void __queue_add(__Queue q, BinTree tree) {
  __Queue_Node newTarget = calloc(1, sizeof(struct __queue_node));
  newTarget->tree = NULL;
  newTarget->next = NULL;
  if (q->length == 0) {
    q->first = q->length = newTarget;
  } else {
    q->last->next = newTarget;
    q->last = newTarget;
  }
  q->length++;
  return;
}
BinTree __queue_delete(__Queue q) {
  if (q->length < 1) return NULL;
  __Queue_Node newTarget = q->first;
  BinTree result = newTarget->tree;
  if (q->length == 1) {
    q->first = q->last = NULL;
  } else {
    q->first = q->first->next;
  }
  free(newTarget);
  q->length--;
  return result;
}
void __queue_free(__Queue q) {
  __Queue_Node start = q->first;
  __Queue_Node target = NULL;
  while (start) {
    target = start;
    start = start->next;
    free(start);
  }
  free(q);
  return;
}

void level_order_traversal(BinTree b) {
  if (!b) return;
  __Queue q = __queue_new();
  __queue_add(q, b);
  while (!__queue_is_empty(q)) {
    BinTree target = __queue_delete(q);
    BinTree left = target->left;
    BinTree right = target->right;
    if (left) {
      __queue_add(q, left);
    }
    if (right) {
      __queue_add(q, right);
    }
    // print
    printf("%d\n", target->data);
  }
  __queue_free(q);
  return;
}

void pre_order_traversal(BinTree b) {
  __pre_order_traversal_recure(b);
  printf("\n");
  __pre_order_traversal_iterate(b);
}
void in_order_traversal(BinTree b) {
  __in_order_traversal_recure(b);
  printf("\n");
  __in_order_traversal_iterate(b);
}
void post_order_traversal(BinTree b) {
  __post_order_traversal_recure(b);
  printf("\n");
  __post_order_traversal_iterate(b);
}

int bin_tree_height(BinTree b) {
  return __tree_hight_iterate(b);
}
