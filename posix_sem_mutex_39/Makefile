.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=pctest
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
pctest:pctest.o
	$(cc) $(CFLAGS) $^ -o $@ -lpthread
clean:
	rm -f *.o $(BIN)

	
