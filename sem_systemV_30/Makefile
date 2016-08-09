.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=sem semtool
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

	
