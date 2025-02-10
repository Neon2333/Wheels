#include "TcpServer.h"
#include "CLogFile.h"
#include <string>
#include <pthread.h>

CLogFile logfile;
TcpServer tcpServer;

void mainEXIT(int sig)
{
    if(sig>0)	
    {
        signal(sig,SIG_IGN);
        signal(SIGINT,SIG_IGN);
        signal(SIGTERM,SIG_IGN);
        
        kill(0,15);	
        printf("mpserver exit..(father process:%d)\n",getpid());
        
        tcpServer.CloseListen();
        exit(0);
    }
}


void* pthmainfunc(void* arg)
{
    int sockfd=(int)(long)(arg);
    while(true)
    {
        int iBufferlen;
        char buffer[1024];
        memset(buffer,0,sizeof(buffer));
        if(tcpServer.TcpRead(sockfd,buffer,&iBufferlen,300)==false)    
        {
            break;
        }

        logfile.Write("recv: %s\n",buffer);
        strcat(buffer,"ok\n");

        if(tcpServer.TcpWrite(sockfd,buffer)==false)
        {
            break;
        }
        logfile.Write("send: %s\n",buffer);

    }
    logfile.Write("client(%s) disconnected..\n", tcpServer.GetIP());
    pthread_exit(0);
}


int main(int argc, char** argv)
{
 	if(argc!=3)	
    {
        printf("Using: ./mthserver port logfile\nExample:./mthserver 5000 /tmp/mthserver.log\n\n");
        return -1;
    }
	
    //logfile.m_bBackup=false; //多进程服务程序关闭日志切换

    if(logfile.Open(argv[2], "a+") == false)	//a+添加，不存在则创建
    {
        printf("logfile open failed..(%s)\n", argv[2]);
    }
    
    signal(SIGINT,mainEXIT);	
    signal(SIGTERM,mainEXIT);
    if(tcpServer.InitServer(atoi(argv[1]))==false)
    {
        //printf("server init failed..\n");
        logfile.Write("server init failed..\n");
        mainEXIT(-1);
    }

    while(true)
    {
        if(tcpServer.Accept()==false)
        {
            logfile.Write("client(%s) connected failed..\n", tcpServer.GetIP());
            continue;	
        }
        logfile.Write("client(%s) connected..\n", tcpServer.GetIP());

        pthread_t pthid;
        if(pthread_create(&pthid,NULL,pthmainfunc,(void*)(long)tcpServer.m_clientfd)!=0)
        {
          logfile.Write("create thread failed..\n");
          return -1;
        }
    }
    return 0;
}