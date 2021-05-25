//
//  stack.c
//  data_structure
//
//  Created by jack on 2020/12/8.
//

#include "stack.h"

Stack stack_new(int MaxSize) {
    Stack stack = calloc(1, sizeof(struct stack));
    stack->MaxSize = MaxSize;
    stack->size = 0;
    stack->top = NULL;
    return stack;
};
// 判断stack是否达到最大值
int stack_is_full(Stack s) {
    if (s->size == s->MaxSize) return 1;
    else {
        return 0;
    }
}
int stack_is_empty(Stack s) {
    return s->size == 0;
}
int stack_pop(Stack s) {
    if (s->size == 0) return 0;
    Stack_Node target = s->top;
    s->top = target->pre;
    int result = target->data;
    free(target);
    s->size--;
    return result;
}
int stack_push(Stack s, int x) {
    if (s->size >= s->MaxSize) return -1;
    Stack_Node newNode = calloc(1, sizeof(struct __stack_node));
    newNode->data = x;
    if (s->size == 0) {
        newNode->pre = NULL;
        s->top = newNode;
    } else {
        newNode->pre = s->top;
        s->top = newNode;
    }
    s->size++;
    return 0;
}
int stack_top(Stack s) {
    if (s->size == 0) return 0;
    return s->top->data;
}
void stack_free(Stack s) {
    Stack_Node target;
    Stack_Node start = s->top;
    while (start) {
        target = start;
        start = start->pre;
        free(target);
    }
    s->size = 0;
    free(s);
    return;
}
