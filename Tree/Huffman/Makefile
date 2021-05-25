.PHONY:test

SRC = huffman
CUR_DIR = $(shell pwd)
OBJDIR = $(CUR_DIR)/obj
OBJ = $(OBJDIR)/main.o $(OBJDIR)/$(SRC).o
cc = c++

main:$(OBJ)
	$(cc) $^ -o $(OBJDIR)/$@

$(OBJDIR)/main.o:
	$(cc) -c test.c -o $(OBJDIR)/main.o

$(OBJDIR)/$(SRC).o:
	$(cc) -c $(SRC).c -o $(OBJDIR)/$(SRC).o

test:
	make clean && make main && $(OBJDIR)/main

clean:
	-rm -rf $(OBJDIR)
	-mkdir $(OBJDIR)
