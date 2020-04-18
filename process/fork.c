/*************************************************************************
	> File Name: fork.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月12日 星期日 13时38分41秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        perror("fork");
        return -1;
    }

    //子进程
    if (pid == 0)
    {
        printf("son process: %d\n", getpid());  //getpid得到的是当前进程（子进程）的进程号
        sleep(10);
    }

    //父进程
    if (pid > 0)
    {
        printf("child process: %d\n", pid);
        printf("parent process: %d\n", getpid());
    }

}

