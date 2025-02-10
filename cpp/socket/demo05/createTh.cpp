#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


int ival=0;

void cleanfunc1(void* arg)
{
    printf("cleanfunc1..\n");
}

void cleanfunc2(void* arg)
{
    printf("cleanfunc2..\n");
}

void cleanfunc3(void* arg)
{
    printf("cleanfunc3..\n");
}


void* func1(void* arg)
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    pthread_cleanup_push(cleanfunc1,NULL);
    pthread_cleanup_push(cleanfunc2,NULL);
    pthread_cleanup_push(cleanfunc3,NULL);
    for(int i=0;i<100000000;i++)
    {
        ival++;
        printf("ival=%d\n",ival);
    }
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_exit(0);
}


int main(int argc,char** argv)
{
    pthread_t pthid;
    pthread_create(&pthid, NULL, func1, NULL);
    usleep(1000);
    pthread_cancel(pthid);
    pthread_join(pthid,NULL);

    return 0;
}
