.PHONY:test

CUR_DIR = $(shell pwd)
DEBUG_DIR = $(CUR_DIR)/debug
CFLAGS = -g -D USE_TRAVERSAL_ITERATE=1 -D DEBUG=true --std=c++11
cc = g++

all:
	make clean
	make BinarySearchTree
	make BinaryTree
	make AVLTree
	make SplayTree

$(DEBUG_DIR)/BinaryTree.o: BinaryTree.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/BinarySearchTree.o: BinarySearchTree.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/BinaryTree_test.o: BinaryTree_test.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/BinarySearchTree_test.o: BinarySearchTree_test.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/AVLTree_test.o: AVLTree_test.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/AVLTree.o: AVLTree.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/SplayTree_test.o: SplayTree_test.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/SplayTree.o: SplayTree.cpp
	$(cc) $(CFLAGS) -c $^ -o $@

$(DEBUG_DIR)/BinaryTree: $(DEBUG_DIR)/BinaryTree_test.o $(DEBUG_DIR)/BinaryTree.o
	$(cc) $(CFLAGS) $^ -o $@
$(DEBUG_DIR)/BinarySearchTree: $(DEBUG_DIR)/BinarySearchTree_test.o $(DEBUG_DIR)/BinarySearchTree.o $(DEBUG_DIR)/BinaryTree.o
	$(cc) $(CFLAGS) $^ -o $@
$(DEBUG_DIR)/AVLTree: $(DEBUG_DIR)/AVLTree_test.o $(DEBUG_DIR)/AVLTree.o $(DEBUG_DIR)/BinarySearchTree.o $(DEBUG_DIR)/BinaryTree.o
	$(cc) $(CFLAGS) $^ -o $@
$(DEBUG_DIR)/SplayTree: $(DEBUG_DIR)/SplayTree_test.o $(DEBUG_DIR)/SplayTree.o $(DEBUG_DIR)/BinarySearchTree.o $(DEBUG_DIR)/BinaryTree.o
	$(cc) $(CFLAGS) $^ -o $@

BinaryTree:
	make $(DEBUG_DIR)/BinaryTree && $(DEBUG_DIR)/BinaryTree
BinarySearchTree:
	make $(DEBUG_DIR)/BinarySearchTree && $(DEBUG_DIR)/BinarySearchTree
AVLTree:
	make $(DEBUG_DIR)/AVLTree && $(DEBUG_DIR)/AVLTree
SplayTree:
	make $(DEBUG_DIR)/SplayTree && $(DEBUG_DIR)/SplayTree

clean:
	-rm -rf $(DEBUG_DIR)
	-mkdir $(DEBUG_DIR)
