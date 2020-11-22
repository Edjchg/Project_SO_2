.PHONY: clean
CC = gcc
APP = using_fifo_server
SRC = $(APP).c
CFLAGS = -lm
DEP = ../sobel/sobel
DEP2 = fifo_server
$(APP): $(SRC) $(DEP).h $(DEP2).h
		$(CC) -o $(APP) $(SRC) $(DEP).c $(DEP2).c $(CFLAGS)
clean:
		rm $(APP)
