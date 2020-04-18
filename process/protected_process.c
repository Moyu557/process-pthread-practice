/*************************************************************************
	> File Name: protected_process.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月12日 星期日 21时11分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/stat.h>

int main()
{
    pid_t pid;
    FILE* fp;
    time_t t;

    //创建子进程作为守护进程
    if ((pid = fork()) < 0)
    {
        perror("fork");
        return -1;
    }

    //退出父进程，将子进程变成孤儿进程，脱离父进程控制
    if (pid > 0)
    {
        exit(0);
    }

    //创建新的会话，脱离当前终端的控制
    setsid();

    //设置文件掩码为0，保证可以方便设置文件权限
    umask(0);

    //设置文件目录为根目录（或者/tmp目录）
    chdir("/tmp");

    //关闭打开的所有文件描述符
    for (int i = 0; i < getdtablesize(); ++i)
        close(i);

    //打开文件
    if ((fp = fopen("time.log", "a")) == NULL)
    {
        perror("fopen");
        return -1;
    }

    //将时间写入文件
    while (1)
    {
        t = time(0);
        fprintf(fp, "%s", ctime(&t));
        
        //因为文件是全缓冲，所以强制刷新
        fflush(fp);

        //间隔1秒写入时间
        sleep(1);
    }
}
