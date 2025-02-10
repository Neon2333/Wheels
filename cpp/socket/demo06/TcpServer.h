#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/select.h>
#include <errno.h>
#include <signal.h>

class TcpServer
{
private:
    struct sockaddr_in m_server_addr;
    struct sockaddr_in m_client_addr;
    int m_client_addr_size;
public:
    int m_listenBacklog=100;
    unsigned int m_port;   
    int m_listenfd;
    int m_clientfd;
    bool m_btimeout;
    int m_bufferlen;
public:
    TcpServer();
    ~TcpServer();
    bool InitServer(const unsigned int port);
    bool Accept();


    bool Readn(const int sockfd, char* buffer, const size_t n);
    bool Writen(const int sockfd, char* buffer, const size_t n);
    bool TcpRead(int sockfd, char* buffer, int* ibuflen, const int timeout=0);
    bool TcpWrite(int sockfd, char* buffer, int* ibuflen=0);

    bool Read(char* buffer, const int timeout=0);
    bool Write(char* buffer, int ibuflen=0);
    char* GetIP();
    void CloseListen(); 
    void CloseClient();

};
