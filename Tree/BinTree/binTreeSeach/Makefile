.PHONY:test

TARGET = binTreeSearch
CUR_DIR = $(shell pwd)
OBJ_DIR = $(CUR_DIR)/obj
OBJ = $(OBJ_DIR)/test.o $(OBJ_DIR)/$(TARGET).o
CFLAGS = -g
cc = gcc

$(OBJ_DIR)/test:$(OBJ)
	$(cc) $(CFLAGS) $^ -o $@
$(OBJ_DIR)/test.o: test.c
	$(cc) $(CFLAGS) -c $^ -o $@
$(OBJ_DIR)/$(TARGET).o: $(TARGET).c
	$(cc) $(CFLAGS) -c $^ -o $@

test:
	make clean && make $(OBJ_DIR)/test && $(OBJ_DIR)/test

clean:
	-rm -rf $(OBJ_DIR)
	-mkdir $(OBJ_DIR)


