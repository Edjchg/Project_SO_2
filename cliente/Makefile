.PHONY: clean
CC = gcc
APP = using_image_client
SRC = $(APP).c
CFLAGS = -pthread
DEP = client_image_sender
$(APP): $(SRC) $(DEP).h
		$(CC) -o $(APP) $(SRC) $(DEP).c $(CFLAGS)
clean: 
		rm $(APP)