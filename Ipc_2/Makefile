.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=msg_get msg_rmid msg_stat msg_set msg_send msg_recv
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

	
