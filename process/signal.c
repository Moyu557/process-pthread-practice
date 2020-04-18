/*************************************************************************
	> File Name: signal.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月16日 星期四 22时25分34秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//收到信号要执行的函数
void handler (int signo)
{
    if (signo == SIGINT)
        printf("I have got SIGINT!\n");
    if (signo == SIGQUIT)
        printf("I have got SIGQUIT!\n");
}

int main()
{
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    
    while (1)
        pause();
    
    return 0;
}
