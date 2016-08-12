.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=threadattr tsd
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
threadattr:threadattr.o
	$(cc) $(CFLAGS) $^ -o $@ -lpthread
tsd:tsd.o
	$(cc) $(CFLAGS) $^ -o $@ -lpthread
clean:
	rm -f *.o $(BIN)

	
