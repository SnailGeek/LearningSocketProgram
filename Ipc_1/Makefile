.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=msg_get
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

	
