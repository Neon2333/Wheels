#include "TcpServer.h"

TcpServer::TcpServer()
{
    m_port=-1;
    m_listenfd=-1;
    m_client_addr_size=0;
    m_bufferlen=0;
    m_btimeout=false;
}

TcpServer::~TcpServer()
{
    CloseListen();
    CloseClient();
}

bool TcpServer::InitServer(const unsigned int port)
{
    if(m_listenfd>0)
    {
        close(m_listenfd);
        m_listenfd=-1;
    }
	
    m_listenfd = socket(PF_INET, SOCK_STREAM, 0);
    
    if(m_listenfd == -1) return false;


    int opt=1;
    unsigned int len=sizeof(opt);
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, len);
	
	
    memset(&m_server_addr, 0, sizeof(m_server_addr));
    m_server_addr.sin_family=AF_INET;
    m_server_addr.sin_addr.s_addr=htonl(INADDR_ANY);	
    m_server_addr.sin_port=htons(port);

    if(bind(m_listenfd, (struct sockaddr*) &m_server_addr, sizeof(m_server_addr)) == -1)
    {
        CloseListen();
        return false;
    }
    
    if(listen(m_listenfd, m_listenBacklog) == -1)
    {
        CloseListen();
        return false;
    }

    m_client_addr_size=sizeof(m_client_addr);
    return true;
}

bool TcpServer::Accept()
{
    if(m_listenfd == -1)    return false;
    if((m_clientfd = accept(m_listenfd, (struct sockaddr*)&m_client_addr,(socklen_t*)&m_client_addr_size)) == -1)	return false;
    return true;
}


bool  TcpServer::Readn(const int sockfd, char* buffer, const size_t n)
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

 bool  TcpServer::Writen(const int sockfd, char* buffer, const size_t n)
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


bool TcpServer::TcpRead(int sockfd, char* buffer, int* ibuflen, const int timeout)
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

 bool TcpServer::TcpWrite(int sockfd, char* buffer, int* ibuflen)
 {
        if(sockfd==-1 || NULL==buffer)	return false;
        
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

bool TcpServer::Read(char* buffer, const int timeout)
{
    if(m_clientfd==-1)	return false;	   
    if(timeout>0)
    {
        fd_set tmpfd;
    
    	FD_ZERO(&tmpfd);
    	FD_SET(m_clientfd,&tmpfd);
    
    	struct timeval _timeout;
    	_timeout.tv_sec=timeout;
    	_timeout.tv_usec=0;
        m_btimeout=false;

        int i; 
        if((i=select(m_clientfd+1,0,&tmpfd,0,&_timeout))<=0)	
    	{
        	if(i==0)
            	m_btimeout=true;
        	return false;
    	}
    }
    m_bufferlen=0;
    return TcpRead(m_clientfd, buffer, &m_bufferlen);
}


bool TcpServer::Write(char* buffer, int ibuflen)
{
    if(m_clientfd==-1)	return false;
    
    fd_set tmpfd;
    
    FD_ZERO(&tmpfd);
    FD_SET(m_clientfd,&tmpfd);
    
    struct timeval timeout;
    timeout.tv_sec=5;
    timeout.tv_usec=0;
    
    int i;
    if((i=select(m_clientfd+1,0,&tmpfd,0,&timeout))<=0)	
    {
        if(i==0)
            m_btimeout=true;
        return false;
    }
    int ilen=ibuflen;
    if(ilen==0)
        ilen=strlen(buffer);
    
    return TcpWrite(m_clientfd, buffer, &ilen);
}
    
char* TcpServer::GetIP()
{
    return inet_ntoa(m_client_addr.sin_addr);
}
    
void TcpServer::CloseListen()
{
    close(m_listenfd);
    m_listenfd=-1;
}

void TcpServer::CloseClient()
{
    close(m_clientfd);
    m_clientfd=-1;
}
