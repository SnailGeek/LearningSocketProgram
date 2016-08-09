.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=shmfifo shmfifo_send
OBJS1=shmfifo_send.o shmfifo.o ipc.o
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
shmfifo_send:$(OBJS1)
	$(cc) $(CFLAGS)  $^ -o $@
clean:
	rm -f *.o $(BIN)

	
