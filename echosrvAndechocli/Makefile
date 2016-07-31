.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=echosrv echocli echosrv2
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

	
