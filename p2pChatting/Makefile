.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=p2psrv p2pcli
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

	
