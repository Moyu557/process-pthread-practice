/*************************************************************************
	> File Name: msgsnd.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月17日 星期五 20时58分26秒
 ************************************************************************/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

//消息队列的结构体
typedef struct
{
    long mytype;     //首成员表示消息队列的类型，必须为long
    char mytext[64];     //正文
}MSG;

#define LEN (sizeof(MSG) - sizeof(long))    //消息正文的长度，方便发送和接收

int main()
{
    key_t key;
    int msgid;
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


    buf.mytype = 100;   //类型必须为正整数，发送的类型要为对方（接收方）的类型
    
    fgets(buf.mytext, 64, stdin);    //从键盘获取一行输入作为正文

    //发送消息
    msgsnd(msgid, &buf, LEN, 0);    //发送成功才返回

    //接收消息
    msgrcv(msgid, &buf, LEN, 100, 0);    //接收到才返回，接受的消息类型要是自己的类型

    //打印消息内容
    fputs(buf.mytext, stdout);

   //删除消息队列(立即删除)
    msgctl(msgid, IPC_RMID, NULL);  //同shmctl
}
