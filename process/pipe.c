/*************************************************************************
	> File Name: pipe.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月16日 星期四 09时18分47秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int pd[2];  //两个文件描述符，用于读写管道

int main()
{
    pid_t pid1, pid2, pid3;   //两个进程用来写管道
    char buf[32];       //写入的字符串
    int fd[2];          //文件描述符

    //创建无名管道（pipe)，先创建管道再创建子进程
    if (pipe(fd) < 0)
    {
        perror("pipe");
        return -1;
    }

    //创建子进程1
    if ((pid1 = fork()) < 0)
    {
        perror("fork");
        return -1;
    }

    //子进程1向管道写入数据
    else if (pid1 == 0)
    {
        strcpy(buf, "I'm process1");
        write(fd[1], buf, sizeof(buf));
        
        //退出进程
        exit(0);
    }

    //父进程
    else
    {
        //创建子进程2
        if ((pid2 = fork()) < 0)
        {
            perror("fork");
            return -1;
        }

        //子进程2
        else if (pid2 == 0)
        {
            sleep(1);   //输出显示会有1秒间隔
            strcpy(buf, "I'm process2");
            write(fd[1], buf, sizeof(buf));
        }

        //父进程
        else
        {
            //创建子进程3
            if ((pid3 = fork()) < 0)
            {
                perror("fork");
                return -1;
            }

            //进程3写入内容到管道
            if(pid3 == 0)
            {
                sleep(2);   //间隔一秒打印进程3写入的内容
                strcpy(buf, "I'm process3");
                write(fd[1], buf, sizeof(buf));
            }

            //父进程
            else
            {
                //打印子进程写入的内容
                wait(NULL);     //阻塞等待进程1结束
                read(fd[0], buf, sizeof(buf));
                printf("%s\n", buf);    //进程1写的内容

                //打印子进程2写入的内容
                wait(NULL);     //阻塞等待进程结束
                read(fd[0], buf, sizeof(buf));
                printf("%s\n", buf);    //进程2写的内容

                //打印子进程3写入的内容
                wait(NULL);     //阻塞等待进程结束
                read(fd[0], buf, sizeof(buf));
                printf("%s\n", buf);    //进程2写的内容
            }
        }
    }
    
    return 0;
}
