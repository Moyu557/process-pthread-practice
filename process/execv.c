/*************************************************************************
	> File Name: execv.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月12日 星期日 15时35分14秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main()
{
    char* argv[] = {"ls", "-la", ".", NULL};

    if (execv("/bin/ls", argv) < 0)
    {
        perror("execv");
        return -1;
    }
}
