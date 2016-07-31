.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=echosrv echocli echocli2 
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

	
