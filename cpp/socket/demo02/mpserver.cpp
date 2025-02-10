#include "TcpServer.h"
#include "CLogFile.h"

CLogFile logfile;
TcpServer tcpServer;


void FatherEXIT(int sig)
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

void ChildEXIT(int sig)
{
    if(sig>0)
    {
        signal(sig,SIG_IGN);
        signal(SIGINT,SIG_IGN);
        signal(SIGTERM,SIG_IGN);
        
        printf("mpserver exit..(child process:%d\n),getpid()");
       
        tcpServer.CloseClient();
        exit(0);
    }
}

int main(int argc, char** argv)
{
 	if(argc!=3)	
    {
        printf("Using: ./mpserver port logfile\nExample:./mpserver 5000 /tmp/mpserver.log\n\n");
        return -1;
    }
   
    for(int i=0;i<70;i++)
    {
        signal(i, SIG_IGN);
    }
	
    logfile.m_bBackup=false; //多进程服务程序关闭日志切换

    if(logfile.Open(argv[2], "a+") == false)	//a+添加，不存在则创建
    {
        printf("logfile open failed..(%s)\n", argv[2]);
    }
    
    signal(SIGINT,FatherEXIT);	
    signal(SIGTERM,FatherEXIT);
    if(tcpServer.InitServer(atoi(argv[1]))==false)
    {
        //printf("server init failed..\n");
        logfile.Write("server init failed..\n");
        FatherEXIT(-1);
    }

    while(true)
    {
        if(tcpServer.Accept()==false)
        {
            logfile.Write("client(%s) connected failed..\n", tcpServer.GetIP());
            continue;	
        }
        
       //父进程处理
        if(fork()>0)
        {
            tcpServer.CloseClient();	
            continue;
        }
		
         //子进程处理
        signal(SIGINT,ChildEXIT);	
        signal(SIGTERM,ChildEXIT);
        
        tcpServer.CloseListen();	
        break;        
             
    }

    logfile.Write("client(%s) connected..\n", tcpServer.GetIP());
    char strbuffer[1024];
    while(true)
    {
        memset(strbuffer,0,sizeof(strbuffer));
        if(tcpServer.Read(strbuffer, 300)==false)  
            break;
        logfile.Write("receive msg: %s\n", strbuffer);

        strcat(strbuffer, ":ok\n");
        if(tcpServer.Write(strbuffer)==false)   break;
    }
    
    logfile.Write("client(%s) disconnected..\n", tcpServer.GetIP());
}