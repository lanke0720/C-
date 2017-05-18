//comm.h
#ifndef _COMM_H_
#define _COMM_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define _PATH_ "."
#define PROJ_ID 0x6666

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf
{
    long mytype;
    char mtext[1024];
};

int CreatMsgQueue();
int GetMsqid();
int DestroyMsqid(int  msqid);
int SendMsg(int msqid, int who, char* msg);
int RevMsg(int msqid, int recType, char out[]);



#endif
