.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=shm_open shm_unlink shm_write shm_read
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
shm_open:shm_open.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
shm_unlink:shm_unlink.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
shm_write:shm_write.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
shm_read:shm_read.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
clean:
	rm -f *.o $(BIN)

	
