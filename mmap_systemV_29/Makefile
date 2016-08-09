.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=shmwrite shmread
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

	
