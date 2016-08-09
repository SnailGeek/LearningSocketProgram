#ifndef _SHM_FIFO_H_
#define _SHM_FIFI_H_

#include "ipc.h"

typedef struct shmfifo shmfifo_t;
typedef struct shmhead shmhead_t;

//假设缓冲区是定长的
struct shmhead
{
	unsigned int blksize; // 块的大小
	unsigned int blocks; //块的总数
	unsigned int rd_index; //读索引
	unsigned int wr_index;//写索引
};

struct shmfifo
{
	shmhead_t *p_shm; // 共享内存头部指针
	char *p_payload; // 有效负载的起始地址
	
	int shmid; // 共享内存IO
	int sem_mutex; // 用来互斥用的信号量
	int sem_full;// 用来控制共享内存是否满的信号量
	int sem_empty;// 用来控制共享内存是否空的信号量
};

shmfifo_t* shmfifo_init(int key ,int blksize, int blocks); //key用来创创建shmid, sem_empty, sem_full, sem_mutex 的ID
void shmfifo_put(shmfifo_t* fifo, const void *buf);
void shmfifo_get(shmfifo_t* fifo, char *buf);
void shmfifo_destory(shmfifo_t* fifo);

#endif 




