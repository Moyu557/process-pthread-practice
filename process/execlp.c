/*************************************************************************
	> File Name: execlp.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月12日 星期日 15时27分30秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main()
{
    if (execlp("ls", "ls", "-al", NULL) < 0)
    {
        perror("execlp");
        return -1;
    }
}
