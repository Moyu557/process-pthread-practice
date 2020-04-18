/*************************************************************************
	> File Name: msg1.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月17日 星期五 21时32分44秒
 ************************************************************************/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>

//定义消息结构体
typedef struct
{
    long type;  //消息类型，必须为long，并且是个正整数
    char text[64];   //消息正文
}MSG;

#define LEN (sizeof(MSG) - sizeof(long))
#define type1 100
#define type2 200

int main()
{
    int msgid;
    key_t key;
    MSG buf;
    
    //创建key
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

    while(1)
    {
        //指定对方消息类型
        buf.type = type2;

        //从键盘读取输入
        printf("input> ");
        fgets(buf.text, 64, stdin);


        //发送消息
        if (msgsnd(msgid, &buf, LEN, 0) < 0)
        {
            perror("msgsnd");
            return -1;
        }
        
        //退出
        if (strcmp(buf.text, "quit\n") == 0)
            break;

        //接收消息
        if (msgrcv(msgid, &buf, LEN, type1, 0) < 0)
        {
            perror("msgrcv");
            return -1;
        }

        //收到对方发来的退出，删除消息队列
        if (strcmp(buf.text, "quit\n") == 0)
        {
            if (msgctl(msgid, IPC_RMID, NULL) < 0)
            {
                perror("msgctl");
                return -1;
            }
            return 0;
        }
        //打印消息
        printf("recv 2: %s", buf.text);
    }
}
