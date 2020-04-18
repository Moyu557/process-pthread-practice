/*************************************************************************
	> File Name: process1.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月16日 星期四 13时02分59秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define N 32

int main()
{
    char buf[N];
    int fd;         //文件描述符，fifo写入数据
    
    //打开管道（只读）
    if((fd = open("myfifo", O_WRONLY)) < 0)
    {
        perror("open");
        return -1;
    }

    //stdin读取数据
    while (1)
    {
        fgets(buf, N, stdin);
        
        //输入quit退出
        if (strcmp (buf, "quit\n") == 0)
            break;

        //写入管道
        write(fd, buf, N);
    }

    close(fd);

    return 0;
}
