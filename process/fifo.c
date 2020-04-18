/*************************************************************************
	> File Name: fifo.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月16日 星期四 12时59分54秒
 ************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    //创建fifo
    if (mkfifo("myfifo", 0666) < 0)
    {
        perror("mkfifo");
        return -1;
    }

    return 0;
}
