/*
	client
	socket->connect->read/write->close
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    //指定要连接的server的ip、port
	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(server_addr));

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);	
	server_addr.sin_port=htons(atoi(argv[2]));
	
	//创建socket
    int sockfd;
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd==-1)
    {
        perror("socket");
        return -1;
    }
   	//连接server
	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect");
        close(sockfd);
    }
    
    //数据收发
    //向server发送一个字符串，等待回复并打印，再发送下一个
    char buffer[1024];
    
    for(int i=0;i<10;i++)
    {
        //发送给server
        int msgCount=0;
        memset(buffer,0,sizeof(buffer));
        //sprintf(buffer, "这是来自client的第%d个消息", i+1);
	int ilen=16;
	char bufferTmp[16]="this is msg:(1)";
	int ilenn=htonl(ilen);
	char buffer[ilen+4];
	
	memset(buffer,0,ilen+4);
	memcpy(buffer,&ilenn,4);
	memcpy(buffer+4,bufferTmp,ilen);

        if((msgCount = send(sockfd, buffer, sizeof(buffer), 0)) <= 0)	
        {
		   perror("send");
            break;
        }
        printf("发送了%s\n", buffer);
        
        //接收server的回应
        memset(buffer, 0 ,sizeof(buffer));
        if((msgCount = recv(sockfd, buffer, sizeof(buffer), 0)) <= 0)	
        {
            printf("msgCount=%d", msgCount);
            break;
        }
        printf("接收了%s\n", buffer);

    }
   
}
