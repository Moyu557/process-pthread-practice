/*************************************************************************
	> File Name: exit_process.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月12日 星期日 14时37分26秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("this process will exit");
    exit(0);        //exit 会刷新流，打印前一条语句
    //_exit(0);     //——exit 直接退出，不会打印出printf的内容
    printf("never be displayed");
}
