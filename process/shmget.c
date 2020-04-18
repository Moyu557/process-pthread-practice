/*************************************************************************
	> File Name: shmget.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月17日 星期五 19时22分20秒
 ************************************************************************/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main()
{
    int shmid;
    key_t key;

    //创建key，非私有的key
    if ((key = ftok(".",'m')) == -1)
    {
        perror("ftok");
        return -1;
    }

    //创建共享内存
    if ((shmid = shmget(key, 1024, IPC_CREAT|0666)) < 0)     //因为是私有的IPC对象，所以肯定是新建的，所以不用写 IPC_CREAT
    {
        perror("shmget");
        return -1;
    }
}
