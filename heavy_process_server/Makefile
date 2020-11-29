.PHONY: clean
CC = gcc
APP = using_heavy_process_server
SRC = $(APP).c
DEP = heavy_process
$(APP): $(SRC) $(DEP).h
		$(CC) -o $(APP) $(SRC) $(DEP).c 
clean:
		rm $(APP)
