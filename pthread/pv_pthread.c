/*************************************************************************
	> File Name: pv_pthread.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月15日 星期三 14时59分33秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

char buf[32];   //定义全局的缓冲区，方便读写线程直接访问，然后进行PV操作
sem_t sem_read;      //定义读信号灯，表示是否可读
sem_t sem_write;     //定义写信号灯，表示是否可写

void* function(void* arg);      //线程要执行的函数

int main()
{
    pthread_t a_thread;

    //初始化读信号量
    if (sem_init(&sem_read, 0, 0) < 0)   //用于线程间，初始值
    {
        perror("sem_init");
        return -1;
    }

    //初始化写信号量
    if (sem_init(&sem_write, 0, 1) < 0)     //刚开始应该是可向buf写入数据的，所以写的信号量为1   
    {
        perror("sem_init");
        return -1;
    }

    //创建线程，先初始化信号量再创建线程
    if (pthread_create(&a_thread, NULL, function, NULL) != 0)   
    {
        printf("fail to pthread_create\n");
        return -1;
    }

    //主线程用来读取输入，产生资源，同时也要检查p操作是否完成
    printf("input 'quit' to exit\n");
    
    do {
        //判断是否可写buf
        sem_wait(&sem_write);

        fgets(buf, sizeof(buf), stdin);

        //表示可以读取了
        sem_post(&sem_read);
    }while (strncmp(buf, "quit", 4) != 0);

    return 0;
}

//线程执行函数用来输出buf内容
void* function(void* argc)
{
    while (1)
    {
        //一直等待有可读的信号产生
        sem_wait(&sem_read);

        printf("you input %d characters\n", strlen(buf));

        //表示可以写了
        sem_post(&sem_write);
    }
}
