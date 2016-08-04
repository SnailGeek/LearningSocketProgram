.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN= echosrv echocli nofile_limit conntest pollsrv epollsrv
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
%.o:%.cpp
	g++ $(CFLAGS) -c $< -o $@
epollsrv:epollsrv.o
	g++ $(CFLAGS) $^ -o $@
clean:
	rm -f *.o $(BIN)

	
