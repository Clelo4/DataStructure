.PHONY:test

CUR_DIR = $(shell pwd)
DEBUG_DIR = $(CUR_DIR)/debug
CFLAGS = -g -D USE_TRAVERSAL_ITERATE=1 -D DEBUG=true
cc = g++

$(DEBUG_DIR)/BinaryTree.o: BinaryTree.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/BinarySearchTree.o: BinarySearchTree.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/BinaryTree_test.o: BinaryTree_test.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/BinarySearchTree_test.o: BinarySearchTree_test.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/RedBlackTree.o: RedBlackTree.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/RedBlackTree_test.o: RedBlackTree_test.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/AVLTree_test.o: AVLTree_test.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(DEBUG_DIR)/AVLTree.o: AVLTree.cpp
	$(cc) $(CFLAGS) -c $^ -o $@

$(DEBUG_DIR)/BinaryTree: $(DEBUG_DIR)/BinaryTree_test.o $(DEBUG_DIR)/BinaryTree.o
	$(cc) $(CFLAGS) $^ -o $@
$(DEBUG_DIR)/BinarySearchTree: $(DEBUG_DIR)/BinarySearchTree_test.o $(DEBUG_DIR)/BinarySearchTree.o $(DEBUG_DIR)/BinaryTree.o
	$(cc) $(CFLAGS) $^ -o $@
$(DEBUG_DIR)/RedBlackTree:  $(DEBUG_DIR)/RedBlackTree_test.o $(DEBUG_DIR)/RedBlackTree.o
	$(cc) $(CFLAGS) $^ -o $@
$(DEBUG_DIR)/AVLTree: $(DEBUG_DIR)/AVLTree_test.o $(DEBUG_DIR)/AVLTree.o $(DEBUG_DIR)/BinarySearchTree.o $(DEBUG_DIR)/BinaryTree.o
	$(cc) $(CFLAGS) $^ -o $@

BinaryTree:
	make clean && make $(DEBUG_DIR)/BinaryTree && $(DEBUG_DIR)/BinaryTree
BinarySearchTree:
	make clean && make $(DEBUG_DIR)/BinarySearchTree && $(DEBUG_DIR)/BinarySearchTree
RedBlackTree:
	make clean && make $(DEBUG_DIR)/RedBlackTree && $(DEBUG_DIR)/RedBlackTree
AVLTree:
	make clean && make $(DEBUG_DIR)/AVLTree && $(DEBUG_DIR)/AVLTree

clean:
	-rm -rf $(DEBUG_DIR)
	-mkdir $(DEBUG_DIR)
