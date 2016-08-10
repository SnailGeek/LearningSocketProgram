.PHONY:clean all
cc=gcc
CFLAGS=-Wall -g
BIN=mq_open mq_open2 mq_getattr mq_send mq_recv mq_notify
all:$(BIN)
%.o:%.c
	$(cc) $(CFLAGS) -c $< -o $@
mq_open:mq_open.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
mq_open2:mq_open2.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
mq_getattr:mq_getattr.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
mq_send:mq_send.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
mq_recv:mq_recv.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
mq_notify:mq_notify.o
	$(cc) $(CFLAGS) $^ -o $@ -lrt
clean:
	rm -f *.o $(BIN)

	
