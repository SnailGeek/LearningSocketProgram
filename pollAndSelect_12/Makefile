.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN= echosrv echocli nofile_limit conntest pollsrv
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

	
