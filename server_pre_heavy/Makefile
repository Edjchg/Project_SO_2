.PHONY: clean
CC = gcc
APP = using_pre_heavy_server
SRC = $(APP).c
CFLAGS = -lm
DEP = ../sobel/sobel
DEP2 = pre_heavy_server
DEP3 = fd_shared
$(APP): $(SRC) $(DEP).h $(DEP2).h
		$(CC) -o $(APP) $(SRC) $(DEP).c $(DEP2).c $(DEP3).c $(CFLAGS)
clean:
		rm $(APP)
