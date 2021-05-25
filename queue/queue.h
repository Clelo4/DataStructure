//
//  queue.h
//  data_structure
//
//  Created by jack on 2020/12/9.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>

typedef struct __queue_node* Queue_Node;
struct __queue_node {
    int data;
    Queue_Node next;
    Queue_Node pre;
};

typedef struct queue* Queue;
struct queue {
    int length;
    int maxSize;
    Queue_Node first;
    Queue_Node last;
};
// 创建一个队列
Queue queue_new(int);
// 判断队列是否满
int queue_is_full(Queue);
// 添加一个元素
void queue_add(Queue, int);
// 判断队列是否为空
int queue_is_empty(Queue);
// 判断队列长度
int queue_length(Queue);
// 从队列头删除一个元素并删除
int queue_delete(Queue);
// 删除整个队列
void queue_free(Queue);

#endif /* queue_h */
