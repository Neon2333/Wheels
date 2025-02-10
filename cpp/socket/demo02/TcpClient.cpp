#include "TcpClient.h"

TcpClient::TcpClient()
{
    m_sockfd=-1;
    memset(m_ip, 0, sizeof(m_ip));
    m_port=0;
    m_btimeout=false;
    m_bufferlen=0;
}

TcpClient::~TcpClient()
{
    Close();
}


bool TcpClient::ConnectServer(const char* ip, int port)
{
    if(m_sockfd != -1)
    {
        Close();
    }

    //memcpy(m_ip, ip, sizeof(ip));
    strcpy(m_ip,ip);
    m_port=port;

    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
    //������������������IP
	struct hostent* host;
	if(!(host = gethostbyname(m_ip)))	//���������ip
	{
	    Close();
    	return false;
	}

	//memcpy(&server_addr.sin_addr, &host->h_addr, host->h_length);	//h_addr�궨��Ϊip�б���һ��Ԫ��
	server_addr.sin_addr.s_addr=inet_addr(ip);	
	server_addr.sin_port=htons(m_port);
	
    m_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(m_sockfd==-1)
    {
        return false;
    }

   	//����server
	if(connect(m_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        Close();
        return false;
    }

    return true;
}

bool TcpClient::Readn(const int sockfd, char* buffer, const size_t n)
{
        if(sockfd==-1 || NULL==buffer) return false;
        int nleft,nread,idx;
        nleft=n;
        nread=0;
        idx=0;
        while(nleft>0)
        {
            if((nread = recv(sockfd, buffer+idx, nleft, 0))<=0)
	        {
	            return false;
	        }
	        nleft-=nread;
    	    idx+=nread;
        }
        return true;
}

 bool TcpClient::Writen(const int sockfd, char* buffer, const size_t n)
{
        if(sockfd==-1 || NULL==buffer) return false;
        int nleft,nwrite,idx;
        nleft=n;
        nwrite=0;
        idx=0;

    while(nleft>0)
    {
        if((nwrite = send(sockfd, buffer+idx, nleft, 0))<=0)
	   {
		    fprintf(stderr, "Error: %s\n", strerror(errno));
	        return false;
	    }
	        nleft-=nwrite;
    	    idx+=nwrite;
    }
    return true;
}


bool TcpClient::TcpRead(int sockfd, char* buffer, int* ibuflen, const int timeout)
{
        if(sockfd==-1 || NULL==buffer || NULL==ibuflen)	return false;
       
        fd_set tmpfd;
        
        FD_ZERO(&tmpfd);
        FD_SET(sockfd,&tmpfd);
        
        struct timeval ttimeout;
        ttimeout.tv_sec=timeout;
        ttimeout.tv_usec=0;
        
        int i;
        if((i=select(sockfd+1,0,&tmpfd,0,&ttimeout))<=0)	return false;
        (*ibuflen)=0;
        if(Readn(sockfd,(char*)ibuflen,4)==false)	return false;	//¶ÁÈ¡±¨Í·4×Ö½Ú
        (*ibuflen)=ntohl(*ibuflen);	//×ªÖ÷»ú×Ö½ÚÐò£¬»ñµÃÊý¾Ý³¤¶È
        
        if(Readn(sockfd, buffer, (*ibuflen))==false)	return false;
        return true;
}

 bool TcpClient::TcpWrite(int sockfd, char* buffer, int* ibuflen)
 {
        if(sockfd==-1 || NULL==buffer || NULL==ibuflen)	return false;
        
	fd_set tmpfd;
        
        FD_ZERO(&tmpfd);
        FD_SET(sockfd,&tmpfd);
        
        struct timeval timeout;
        timeout.tv_sec=5;
        timeout.tv_usec=0;
        
        if(select(sockfd+1,0,&tmpfd,0,&timeout)<=0)	return false;
        int ilen=1;
        if(ibuflen==0)	ilen=strlen(buffer);    //ibuflen==0£¬·¢ËÍµÄÊÇ×Ö·û´®£¬²ÉÓÃ×Ö·û´®³¤¶È
        else ilen=*ibuflen;	//·¢ËÍµÄÊÇ¶þ½øÖÆÊý¾Ý
        
        int ilenn=htonl(ilen);	//ilen×ªÎªÍøÂç×Ö½ÚÐò
       
       	char strBufferTmp[ilen+4];

        memset(strBufferTmp,0,ilen+4);
        memcpy(strBufferTmp,&ilenn,4);	//¿½Èëilenn
        memcpy(strBufferTmp+4,buffer,ilen);	//¿½ÈëbufferÖÐÊý¾Ý
	
        if(Writen(sockfd, strBufferTmp, ilen+4) == false)	return false;
        return true;
}


bool TcpClient::Read(char* buffer, const int timeout)
{
    if(m_sockfd==-1)	return false;	   
    if(timeout>0)
    {
        fd_set tmpfd;
    
    	FD_ZERO(&tmpfd);
    	FD_SET(m_sockfd,&tmpfd);
    
    	struct timeval _timeout;
    	_timeout.tv_sec=timeout;
    	_timeout.tv_usec=0;
        m_btimeout=false;

        int i; 
        if((i=select(m_sockfd+1,0,&tmpfd,0,&_timeout))<=0)	
    	{
        	if(i==0)
            	m_btimeout=true;
        	return false;
    	}
    }
    m_bufferlen=0;
    return TcpRead(m_sockfd, buffer, &m_bufferlen); 
}


bool TcpClient::Write(char* buffer, int ibuflen)
{
    if(m_sockfd==-1)	return false;
    
    fd_set tmpfd;
    
    FD_ZERO(&tmpfd);
    FD_SET(m_sockfd,&tmpfd);
    
    struct timeval timeout;
    timeout.tv_sec=5;
    timeout.tv_usec=0;
    
    int i;
    if((i=select(m_sockfd+1,0,&tmpfd,0,&timeout))<=0)	
    {
        if(i==0)
            m_btimeout=true;
        return false;
    }
    int ilen=ibuflen;
    if(ilen==0)
        ilen=strlen(buffer);
    
    return TcpWrite(m_sockfd, buffer, &ilen);
}

void TcpClient::Close()
{
    close(m_sockfd);
    m_sockfd=-1;
}
