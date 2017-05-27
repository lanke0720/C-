ДњТыЃК
//comm.h

#ifndef _COMM_H_
#define _COMM_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>

#define PATHNAME "."
#define PROJ_ID 888
#define _SIZE 1024*4


int CreatShm();
char *at_addr(int shmid);
int Delete_at_addr(char* shmaddr);
int DestroyShm(int shmid);
#endif

//comm.c
#include "comm.h"

int CreatShm()
{
    key_t _key = ftok(PATHNAME, PROJ_ID);
    if (_key < 0)
    {
        perror("ftok error!!");
        return -1;
    }

    int shm_id = shmget(_key, _SIZE, IPC_CREAT|0666);
    if (shm_id < 0)
    {
        perror("shmget error!");
        return -1;
    }
    return shm_id;
}

char *at_addr(int shmid)
{
    return shmat(shmid, NULL, 0);
}

int Delete_at_addr(char* shmaddr)
{
    return shmdt(shmaddr);   
}

int DestroyShm(int shmid)
{
    return shmctl(shmid, IPC_RMID, NULL);
}

//shm.c
#include "comm.h"

int main()
{
    int shmid = CreatShm();
    pid_t id = fork();
    if (id < 0)
    {
        perror("fork error!");
        return 1;
    }
    else if (id == 0)//child
    {
        char* buf = at_addr(shmid);
        int i = 0;
        while (i < 26)
        {
            buf[i] = 'A' ;
            ++i;
        }

        buf[25] = '\0';
        Delete_at_addr(buf);
    }
    else//father
    {
        char* buf = at_addr(shmid);
        sleep(5);
        printf("%s\n", buf);
        Delete_at_addr(buf);
        waitpid(id, NULL, 0);
        DestroyShm(shmid);
    }
    return 0;
}
