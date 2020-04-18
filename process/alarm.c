/*************************************************************************
	> File Name: signal.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月16日 星期四 22时05分41秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main()
{
    alarm(3);   //设置定时器，时间为3‘
    //pause();    //挂起进程，直到进程收到信号,如果不让进程挂起或者 sleep，进程会很快就执行完结束，alarm 就没有意义

    //printf 语句不会被执行。因为当定时器时间到了后，会发出一个型号SIFALRM，这个信号的操作会使进程终止，所以alarm结束整个进程都会结束。
    printf("I have been waken up!\n");
   pause();
    return 0;
}
