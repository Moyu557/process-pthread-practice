/*************************************************************************
	> File Name: read_shm.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月17日 星期五 20时08分56秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key;  
    int shmid;
    char* add;  //要映射的地址

    //创建key
    if ((key = ftok(".",'a')) < 0)
    {
        perror("ftok");
        return -1;
    }

    //创建共享内存
    if ((shmid = shmget(key, 1024, IPC_CREAT|0666)) < 0)
    {
        perror("shmget");
        return -1;
    }

    //映射共享内存
    if ((add = shmat(shmid, NULL, 0)) < 0)
    {
        perror("shmat");
        return -1;
    }

    //读键盘数据到共享内存
    fgets(add, 32, stdin);

    //写数据到终端
    fputs(add, stdout);

    //取消共享内存的映射
    if (shmdt(add) < 0)     //同free，需要保存原来的地址
    {
        perror("shmad");
        return -1;
    }

    //删除共享内存对象
    if (shmctl(shmid, IPC_RMID, NULL) < 0)
    {
        perror("shmctl");
        return -1;
    }
}
