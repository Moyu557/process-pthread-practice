/*************************************************************************
	> File Name: execl.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月12日 星期日 15时08分12秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        perror("fork");
        return -1;
    }

    else if (pid == 0)
    {
        if (execl("/bin/ls", "ls", "-la", NULL) < 0)
        {
            perror("execl");
            return -1;
        }
        exit(0);
    }

    else
        printf("parent process %d\n", getpid());
}
