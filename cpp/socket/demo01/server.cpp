/*
	server
	socket->bind->listen->accept->read/write->close
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    //参数ip port
    if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
    
    //创建监听socket
    int listenfd = 0;
	listenfd = socket(PF_INET, SOCK_STREAM, 0);
	if(listenfd == -1)	 
    {
        perror("socket");
	    return -1;
    }
	
    //指定协议、ip、端口
    struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);	//INADDR_ANY表示所有网卡都监听（服务器一般不止一块网卡）
	server_addr.sin_port=htons(atoi(argv[1]));
	
    //bind
	if(bind(listenfd, (struct sockaddr*) &server_addr, sizeof(server_addr))==-1 )
    {
        perror("bind");
        close(listenfd);
        return -1;
    }
	
    //监听，最多允许5个client连接
	if(listen(listenfd, 5)==-1)
    {
        perror("listen");
        close(listenfd);
        return -1;
    }
	
    struct sockaddr_in client_addr;
	socklen_t client_addr_size;
	client_addr_size=sizeof(client_addr);  

    //接收client连接，获取连接fd
    int clientfd = 0;
	clientfd = accept(listenfd, (struct sockaddr*)&client_addr,&client_addr_size);
	if(clientfd==-1)
    {
        perror("accept");
        close(listenfd);
		return -1;
    }
    else
    {
        printf("%s has been connected..", inet_ntoa(client_addr.sin_addr));
    }
	
    //数据收发
    char buffer[1024];	//缓冲区
    while(1)
    {
   		memset(buffer,0,sizeof(buffer));
    	int msgCount=0;		//接受报文字节数
    	//if((msgCount = recv(clientfd, buffer, sizeof(buffer), 0))<=0)	//接收client报文
	int len=0;
    	if((msgCount = recv(clientfd, (char*)&len, 4, 0))<=0)	//接收client报文
    	{
        	printf("msgCount=%d\n",msgCount);
        	break;
    	}
	
	len=ntohl(len);	
	printf("len=%d\n",len);	
    	if((msgCount = recv(clientfd, buffer, len, 0))<=0)	//接收client报文
    	{
        	printf("msgCount=%d\n",msgCount);
        	break;
    	}
        printf("msgCount=%d,接收：%s\n", msgCount, buffer);	//打印接收报文
        strcpy(buffer, "ok");	
        if((msgCount = send(clientfd, buffer, sizeof(buffer), 0)) <= 0)	//发送响应ok
        {
            perror("send");
            break;
        }
        printf("发送：%s\n", buffer);
    }
  
	close(clientfd);	
	close(listenfd);
	return 0;
}
