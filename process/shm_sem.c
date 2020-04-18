/*************************************************************************
	> File Name: shm_sem.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月18日 星期六 13时41分14秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define N 64        //共享内存的大小
#define READ 0      //信号灯集合中信号的编号，父进程读
#define WRITE 1     //信号灯集合中信号的编号，子进程写


//初始化信号灯的共用体类型
union semun
{
    int val;                //要操作的信号灯的编号
    struct semid_ds* buf;
    unsigned short* array;  //信号灯要执行的操作（P or V）
    struct seminfo* __buf;    
};


//初始化信号灯
void init_sem(int semid, int s[], int n)
{
    int i;
    union semun myun;
    for (i = 0; i  < n; ++i)
    {
        myun.val = s[i];
        semctl(semid, i, SETVAL, myun);
    }
}

//PV操作
void pv(int semid, int num, int op)
{
    struct sembuf buf;

    buf.sem_num = num;
    buf.sem_op = op;
    buf.sem_flg = 0;

    semop(semid, &buf, 1);
}



int main()
{
    int shmid, semid, s[] = {0, 1};     //共享内存ID，信号灯ID，信号灯初始化数组
    pid_t pid;                          //进程ID
    key_t key;                          //key值
    char* shmaddr;                      //共享内存地址

    //生成key
    if ((key = ftok(".", 's'))  < 0)
    {
        perror("ftok");
        return -1;
    }

    //创建共享内存
    if ((shmid = shmget(key, N, IPC_CREAT|0666)) < 0)
        {
            perror("shmget");
            return -1;
        }

    //创建信号灯
    if ((semid = semget(key, 2, IPC_CREAT|0666)) < 0)
    {
        perror("semget");
        
        //信号灯创建失败，删除共享内存
        goto _error1;
    }

    //初始化信号灯
    init_sem(semid, s, 2);

    //映射共享内存
    if ((shmaddr = shmat(shmid, NULL, 0)) < 0)
    {
        perror("shmat");
        goto _error2;
    }

    //创建子进程
    if ((pid = fork()) < 0)
    {
        perror("fork");
        return -1;
    }

    //子进程
    else if (pid == 0)
    {
        char*p, *q;

        while (1)
        {
            pv(semid, READ, -1);
            p = q = shmaddr;

            while (*q)
            {
                if (*q != ' ')
                {
                    *p++ = *q;
                }
                ++q;
            }

            *p = '\0';

            printf("%s", shmaddr);

            pv(semid, WRITE, 1);
        }
    }

    //父进程
    else
    {
        //循环读取输入
        while (1)
        {
            pv(semid, WRITE, -1);
            printf("Input > ");
            fgets(shmaddr, N, stdin);
            if (strcmp(shmaddr, "quit\n") == 0)
                break;
            pv(semid, READ, 1);
        }

        kill(pid, SIGUSR1);
    }

//删除信号灯
_error2:
    semctl(semid, 0, IPC_RMID);

//删除共享内存
_error1:
    shmctl(shmid, IPC_RMID, NULL);
}


