/*************************************************************************
	> File Name: pthread_mutex.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月15日 星期三 20时44分33秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

unsigned int count = 0, value1, value2;
pthread_mutex_t lock;

void* function(void* arg);

int main()
{
    pthread_t a_thread;

    //初始化锁
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        perror("ptherad_mutex_init");
        return -1;
    }

    //创建线程
    if (pthread_create(&a_thread, NULL, function, NULL) != 0)
    {
        perror("pthread_create");
        return -1;
    }

    //主线程
    while (1)
    {
        count++;
        #ifdef _LOCK_   //如果定义了 _LOCK_ 这个宏，这条件为真，执行下面的语句
        pthread_mutex_lock(&lock);  //给资源上锁，获得资源
        #endif 
        
        value1 = count;
        value2 = count;
        
        #ifdef _LOCK_
        pthread_mutex_unlock(&lock);    //释放锁，解锁资源
        #endif
    }

    return 0;
}

void* function(void* argc)
{
    while (1)
    {
        #ifdef _LOCK_
        pthread_mutex_lock(&lock);
        #endif

        if (value1 != value2)
        {
            printf("value1 = %u, value2 = %u\n", value1, value2);
            usleep(100000);
        }

        #ifdef _LOCK_
        pthread_mutex_unlock(&lock);
        #endif
    }
    return NULL;
}
