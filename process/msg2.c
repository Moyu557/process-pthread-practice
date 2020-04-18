/*************************************************************************
	> File Name: msg2.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月17日 星期五 21时48分16秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>

//定义消息结构体
typedef struct
{
    long type;
    char text[64];
}MSG;

#define LEN (sizeof(MSG) - sizeof(long))
#define type1 100
#define type2 200

int main()
{
    key_t key;
    int msgid;
    MSG buf;

    //生成key
    if ((key = ftok(".", 'a')) < 0)
    {
        perror("ftok");
        return -1;
    }

    //创建消息队列
    if ((msgid = msgget(key, IPC_CREAT | 0666)) < 0)
    {
        perror("msgget");
        return -1;
    }

    while (1)
    {

        //接收消息队列
        if (msgrcv(msgid, &buf, LEN, type2, 0) < 0)
        {
            perror("msgrcv");
            return -1;
        }

        //退出的消息
        if (strcmp(buf.text, "quit\n") == 0)
        {
            //删除消息队列
            if (msgctl(msgid, IPC_RMID, NULL) < 0)
            {
                perror("msgctl");
                return -1;
            }
            return 0;
        }

        //打印消息
        printf("recv 1: %s", buf.text);

        //指定对方消息类型
        buf.type = type1;

        //从键盘读取输入
        printf("input > ");
        fgets(buf.text, 64, stdin);

        //发送退出消息
        if (strcmp(buf.text, "quit\n") == 0)
            break;

        //发送消息
        if (msgsnd(msgid, &buf, LEN, 0) < 0)
        {
            perror("msgsnd");
            return -1;
        }
    }
}
