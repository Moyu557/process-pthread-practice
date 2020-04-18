/*************************************************************************
	> File Name: fifo_read.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月16日 星期四 13时12分58秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define N 32

int main()
{
    int fd;     //文件描述符，读取数据
    char buf[N];

    //只读方式打开管道，作为读端
    if ((fd = open("myfifo", O_RDONLY)) < 0)
    {
        perror("open");
        return -1;
    }

    //读取管道数据
    while (read(fd, buf, N) > 0)
    {
        printf("The length of string is %d\n", strlen(buf));
    }

    close(fd);

    return 0;
}
