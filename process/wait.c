/*************************************************************************
	> File Name: wait.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月12日 星期日 20时17分59秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int status;     //子进程状态
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        perror("fork");
        return -1;
    }

    //子进程
    else if (pid == 0)
    {
        sleep(1);
        exit(2);
    }

    //父进程
    else
    {
        wait(&status);      //父进程阻塞直到子进程退出，获取到子进程推出时的信息
        printf("%0x\n", status);
    }
}
