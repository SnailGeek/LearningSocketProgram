#include "shmfifo.h"

typedef struct stu
{
	char name[32];
	int age;
} STU;

int main(void)
{
	shmfifo_t* fifo = shmfifo_init(1234, sizeof(STU), 3);

	int i;
	STU s;
	memset(&s, 0, sizeof(STU));
	s.name[0] = 'A';

	for(i = 0 ;i < 5; i++){
		s.age = 20 + i;
		shmfifo_put(fifo, &s);
		s.name[0] = s.name[0] + 1;

		printf("send OK\n");
	}

	return 0;
}
