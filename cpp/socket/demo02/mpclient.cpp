#include "TcpClient.h"

int main(int argc, char** argv)
{
    TcpClient tcpClient;

    if(tcpClient.ConnectServer("127.0.0.1",5000)==false)
    {
        printf("connect server failed..\n");
        return -1;
    }

    char strBuffer[1024];
    for(int i=0;i<100;i++)
    {
        memset(strBuffer,0,sizeof(strBuffer));
        snprintf(strBuffer,50,"this is msg:(%d)\n",i+1);
        if(tcpClient.Write(strBuffer)==false)   break;
        printf("send msg: %s\n", strBuffer);

        memset(strBuffer,0,sizeof(strBuffer));
        if(tcpClient.Read(strBuffer, 300)==false)    break;
        printf("receive msg: %s\n", strBuffer);
        sleep(1);
    }

}
