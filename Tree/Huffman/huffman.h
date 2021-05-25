#ifndef _HUFF_MAN_H
#define _HUFF_MAN_H

typedef struct _Node* Node;
struct _Node {
    int data;
    Node left;
    Node right;
}
typedef struct _Huffman* Huffman;
struct _Huffman {
    Node root;
}

#endif
