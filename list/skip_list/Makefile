.PHONY:test

TARGET = skip_list
CUR_DIR = $(shell pwd)
OBJ_DIR = $(CUR_DIR)/obj
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/$(TARGET).o
CFLAGS = -g
cc = g++

$(OBJ_DIR)/main:$(OBJ)
	$(cc) $(CFLAGS) $^ -o $@
$(OBJ_DIR)/main.o: main.cpp
	$(cc) $(CFLAGS) -c $^ -o $@
$(OBJ_DIR)/$(TARGET).o: $(TARGET).cpp
	$(cc) $(CFLAGS) -c $^ -o $@

test:
	make clean && make $(OBJ_DIR)/main && $(OBJ_DIR)/main

clean:
	-rm -rf $(OBJ_DIR)
	-mkdir $(OBJ_DIR)
