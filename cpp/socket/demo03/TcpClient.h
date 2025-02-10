#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/select.h>
#include <netdb.h>
#include <signal.h>

class TcpClient
{
private:
    int m_sockfd;
    char m_ip[21];  //�����ƴ洢ip
    int m_port;
    bool m_btimeout;    //����Read/Writeʱ����false���Ƿ�ʱ��־��true-��ʱ��false-δ��ʱ
    int m_bufferlen;
public:
    TcpClient();
    ~TcpClient();

    bool ConnectServer(const char* ip, int port);
    
    bool Readn(const int sockfd, char* buffer, const size_t n);
    bool Writen(const int sockfd, char* buffer, const size_t n);
    bool TcpRead(int sockfd, char* buffer, int* ibuflen, const int timeout=0);
    bool TcpWrite(int sockfd, char* buffer, int* ibuflen=0);
    
    bool Read(char* buffer, const int timeout);
    bool Write(char* buffer, int ibuflen=0);

    void Close();

};
