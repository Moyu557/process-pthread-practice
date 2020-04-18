/*************************************************************************
	> File Name: pipe_size.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月16日 星期四 12时29分41秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int count = 0;
    char buf[1024];
    int fd[2];

    //创建pipe
    if (pipe(fd) < 0)
    {
        perror("pipe");
        return -1;
    }

    //循环写入数据
    while (1)
    {
        write(fd[1], buf, 1024);

        //写入成功打印，否则阻塞
        printf("write %dk\n", ++count);
    }
}
