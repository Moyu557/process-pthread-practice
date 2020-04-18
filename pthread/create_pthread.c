/*************************************************************************
	> File Name: pthread.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月14日 星期二 21时44分18秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

char message[32] = "Hello World";   //使用静态变量，所有线程都可以访问
void* thread_func(void* arg);   //线程要执行的函数，返回类型和参数类型都为 void×

int main()
{
    pthread_t a_thread;
    void* result;           //接收线程执行完函数的返回值

    if (pthread_create(&a_thread, NULL, thread_func, NULL) != 0)     //创建线程，执行 thread_func 函数
    {
        printf("fail to pthread_creat\n");
        return -1;
    }

    pthread_join(a_thread, &result);   //等待线程结束，接受返回值
    printf("result is %s\n", result);
    printf("massage is %s\n", message);

    return 0;
}


void* thread_func(void* arg)
{
    sleep(1);   //线程先睡眠1秒钟，测试 pthread_join 是否阻塞程序
    strcpy(message, "marked by thread"); 
    pthread_exit("thank you for waiting for me");   //退出线程
}
