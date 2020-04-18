/*************************************************************************
	> File Name: execvp.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月12日 星期日 15时38分36秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main()
{
    char* argv[] = {"ls", "-la", ".", NULL};

    if (execvp("ls", argv) < 0)
    {
        perror("execvp");
        return -1;
    }
}
