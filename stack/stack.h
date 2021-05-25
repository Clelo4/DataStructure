//
//  stack.h
//  data_structure
//
//  Created by jack on 2020/12/8.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>

typedef struct __stack_node* Stack_Node;
struct __stack_node {
    int data;
    Stack_Node pre;
};

typedef struct stack* Stack;
struct stack {
    int size;
    Stack_Node top;
    int MaxSize;
};
// 创建一个stack
Stack stack_new(int);
// 判断stack是否达到最大值
int stack_is_full(Stack);
// 判断stack是否为空
int stack_is_empty(Stack);
// 从stack顶部弹出一个元素
int stack_pop(Stack);
// 入栈
int stack_push(Stack, int);
// 取得栈顶元素，但不删除元素
int stack_top(Stack);
// 删除整个堆栈
void stack_free(Stack);

#endif /* stack_h */
