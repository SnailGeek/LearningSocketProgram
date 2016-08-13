.PHONY:clean
cc=gcc
CFLAGS=-Wall -g
OBJECTS=main.o condition.o threadpool.o
BIN=main
#all:$(BIN)
$(BIN):$(OBJECTS)
	$(cc) $(CFLAGS) $^ -o $@ -lpthread -lrt
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@ 
#main.o:main.c threadpool.h
#	$(cc) $(CFLAGS) -c $< -o $@ -lnk 
#condition.o:condition.c condition.h 
#	$(cc) $(CFLAGS) -c $< -o $@ -lpthread
#threadpool.o:threadpool.c threadpool.h
#	$(cc) $(CFLAGS) -c $< -o $@ -lpthread
clean:
	rm -f *.o $(BIN)

	
