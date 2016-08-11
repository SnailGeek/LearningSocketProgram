.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=pthread_create echosrv echocli
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
pthread_create:pthread_create.o
	$(cc) $(CFLAGS) $^ -o $@ -lpthread
echosrv:echosrv.o
	$(cc) $(CFLAGS) $^ -o $@ -lpthread
clean:
	rm -f *.o $(BIN)

	
