CC = gcc
CFLAGS = -Wall -std=c99 -g
DEBUG = -DDEBUG

INC = include/
SRC = src/
BIN = bin/
EXM = examples/

SRC_FILES = $(wildcard src/ds*.c)
OBJ_FILES = $(patsubst src/ds%.c,bin/ds%.o,$(SRC_FILES))

libds: $(BIN)libds

examples: $(EXM)hashTableExample.c $(EXM)listExample.c $(EXM)priorityQueueExample.c $(EXM)queueExample.c $(EXM)stackExample.c $(OBJ_FILES) $(INC)ds*.h
	$(CC) $(CFLAGS) $(EXM)hashTableExample.c $(OBJ_FILES) -I$(INC) -o hashTableExample
	$(CC) $(CFLAGS) $(EXM)listExample.c $(OBJ_FILES) -I$(INC) -o listExample
	$(CC) $(CFLAGS) $(EXM)priorityQueueExample.c $(OBJ_FILES) -I$(INC) -o priorityQueueExample
	$(CC) $(CFLAGS) $(EXM)queueExample.c $(OBJ_FILES) -I$(INC) -o queueExample
	$(CC) $(CFLAGS) $(EXM)stackExample.c $(OBJ_FILES) -I$(INC) -o stackExample

##-D$(DEBUG) can be added bellow for stderr print outs
$(BIN)libds: $(OBJ_FILES)
	gcc -shared $(OBJ_FILES) -o $(BIN)libds.so

##-D$(DEBUG) can be added bellow for stderr print outs
$(BIN)ds%.o: $(SRC)ds%.c $(INC)ds*.h           
	gcc $(CFLAGS) -I$(INC) -c -fpic $< -o $@

clean:
	rm -rf $(BIN)*.o $(BIN)*.so hashTableExample listExample priorityQueueExample queueExample stackExample

###################################################################################################