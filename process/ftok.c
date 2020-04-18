/*************************************************************************
	> File Name: ftok.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月17日 星期五 19时07分40秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    key_t key;  //生成的key值

    //每个进程都应当调用ftok生成相同的key值，才能访问同一个IPC对象，即：ftok的参数要相同
    if ((key = ftok(".", 'a')) == -1)
    {
        perror("ftok");
        return -1;
    }
}

