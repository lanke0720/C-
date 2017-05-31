#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *thread_run1(void *_val)
{   
    sleep(4);
    printf("thread 1 returning...\n");
    return ((void*)1);
}

void *thread_run2(void *_val)
{
    printf("thread 2 exiting...\n");
    pthread_exit((void*)2);
}

void *thread_run3(void *_val)
{
    while(1)
    {
        printf("pthread 3 runing, wait for be cancal..\n");
        sleep(1);       
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    void *tret;
    //1 return 
    pthread_create(&tid, NULL, thread_run1, NULL);
    int ret_return =  pthread_join(tid, &tret);
    printf("ret = %d\n", (int)tret);
    //printf("join_ret = %d\n", ret_return);
    printf("thread return,thread id is:%u, return code is:%d\n",(unsigned long)tid, (int)tret);
    //2 exit 
    //pthread_create(&tid, NULL, thread_run2, NULL);
    //pthread_join(tid, &tret);
    //printf("thread exit,thread id is:%u, exit code is:%d\n",(unsigned long)tid, (int)tret);
    ////3 cancle by other
    //pthread_create(&tid, NULL, thread_run3, NULL);
    //sleep(3);
    //pthread_cancel(tid);
    //int ret_cancle = pthread_join(tid, &tret);
    //printf("ret_cancle = %d\n", ret_cancle);
    //printf("thread return,thread id is%u, calcel code is:%d\n",(unsigned long)tid, (int)tret); 
    return 0;
}
