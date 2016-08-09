.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=print
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

	
