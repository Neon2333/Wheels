//mpserver.cpp
#include "TcpServer.h"
#include "CLogFile.h"
#include <string>
#include <pthread.h>
#include <vector>

CLogFile logfile;
TcpServer tcpServer;
std::vector<long> vpthids;


// 删除字符串左边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteLChar(char *str,const char chr)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;

  char strTemp[strlen(str)+1];

  int iTemp=0;

  memset(strTemp,0,sizeof(strTemp));
  strcpy(strTemp,str);

  while ( strTemp[iTemp] == chr )  iTemp++;

  memset(str,0,strlen(str)+1);

  strcpy(str,strTemp+iTemp);

  return;
}

// 删除字符串右边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteRChar(char *str,const char chr)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;

  int istrlen = strlen(str);

  while (istrlen>0)
  {
    if (str[istrlen-1] != chr) break;

    str[istrlen-1]=0;

    istrlen--;
  }
}


// 删除字符串左右两边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteLRChar(char *str,const char chr)
{
  DeleteLChar(str,chr);
  DeleteRChar(str,chr);
}

// 把字符串中的小写字母转换成大写，忽略不是字母的字符。
// str：待转换的字符串，支持char[]和string两种类型。
void ToUpper(char *str)
{
  if (str == 0) return;

  if (strlen(str) == 0) return;

  int istrlen=strlen(str);

  for (int ii=0;ii<istrlen;ii++)
  {
    if ( (str[ii] >= 'a') && (str[ii] <= 'z') ) str[ii]=str[ii] - 32;
  }
}

void ToUpper(std::string& str)
{
  if (str.empty()) return;

  char strtemp[str.size()+1];

  memset(strtemp,0,sizeof(strtemp));
  strcpy(strtemp,str.c_str());

  ToUpper(strtemp);

  str=strtemp;

  return;
}



bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,char *value,const int ilen)
{
  if (value==0) return false;

  if (ilen>0) memset(value,0,ilen+1);   // 调用者必须保证value的空间足够，否则这里会内存溢出。

  char *start=0,*end=0;
  char m_SFieldName[51],m_EFieldName[51];

  int m_NameLen = strlen(fieldname);
  memset(m_SFieldName,0,sizeof(m_SFieldName));
  memset(m_EFieldName,0,sizeof(m_EFieldName));

  snprintf(m_SFieldName,50,"<%s>",fieldname);
  snprintf(m_EFieldName,50,"</%s>",fieldname);

  start=0; end=0;

  start = (char *)strstr(xmlbuffer,m_SFieldName);

  if (start != 0)
  {
    end   = (char *)strstr(start,m_EFieldName);
  }

  if ((start==0) || (end == 0))
  {
    return false;
  }

  int   m_ValueLen = end - start - m_NameLen - 2 + 1 ;

  if ( ((m_ValueLen-1) <= ilen) || (ilen == 0) )
  {
    strncpy(value,start+m_NameLen+2,m_ValueLen-1); value[m_ValueLen-1]=0;
  }
  else
  {
    strncpy(value,start+m_NameLen+2,ilen); value[ilen]=0;
  }

  DeleteLRChar(value,' ');

  return true;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,bool *value)
{
  if (value==0) return false;

  (*value) = false;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,10) == true)
  {
    ToUpper(strTemp);  // 转换为大写来判断。
    if (strcmp(strTemp,"TRUE")==0) { (*value)=true; return true; }
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,int *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = atoi(strTemp); return true;
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,unsigned int *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = (unsigned int)atoi(strTemp); return true;
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,long *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = atol(strTemp); return true;
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,unsigned long *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = (unsigned long)atol(strTemp); return true;
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,double *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = atof(strTemp); return true;
  }

  return false;
}

void mainEXIT(int sig)
{
    if(sig>0)	
    {
        signal(sig,SIG_IGN);
        signal(SIGINT,SIG_IGN);
        signal(SIGTERM,SIG_IGN);
        
        printf("mthserver exit..(PID=%d)\n",getpid());
        logfile.Write("mthserver exit..(PID=%d)\n",getpid());

        tcpServer.CloseListen();
        for(auto& pthid:vpthids)
        {
          pthread_cancel(pthid);
        }
        std::vector<long>(0).swap(vpthids);
        exit(0);
    }
}

void pthExit(void* arg)
{
    int sockfd=(int)(long)arg;
    close(sockfd);

    for(auto iter=vpthids.begin();iter!=vpthids.end();iter++)
    {
      if(*iter==pthread_self())
        vpthids.erase(iter);
    }

    logfile.Write("thread clean..\n") ;
}


bool biz002(const char* strRecvBuffer,char* strSendBuffer)
{
    char msg[1024];
    memset(msg,0,sizeof(msg));
    GetXmlBuffer(strRecvBuffer,"message",msg,1023);
    
    strcat(msg,"ok");
    sprintf(strSendBuffer,"<retcode>0</retcode><message>%s</message>",msg);
    return true;
}

//业务1（business001）处理函数
bool biz001(const char* strRecvBuffer,char* strSendBuffer)
{
    //从strRecvBuffer中解析出username字段和password字段的值
    char username[51],password[51];
    memset(username,0,sizeof(username));
    memset(password,0,sizeof(password));
    
    GetXmlBuffer(strRecvBuffer,"username",username,50);
    GetXmlBuffer(strRecvBuffer,"password",password,50);
    
    //将用户名、密码同数据库中值对比
    if((strcmp(username, "wk")==0)&&(strcmp(password, "p@ssw0rd")==0))
        sprintf(strSendBuffer,"<retcode>0</retcode><message>login success</message>");
    else
        sprintf(strSendBuffer,"<retcode>-1</retcode><message>用户名或密码不正确</message>");
    
    return true;
}

//心跳响应
bool biz000(const char* strRecvBuffer,char* strSendBuffer)
{
    sprintf(strSendBuffer, "<retcode>0</retcode><message>heartbeat success</message>");
    return true;
}

//业务处理函数
//strRecvBuffer-接收报文
//strSendBuffer-发送报文
bool BusinessProcess(const char* strRecvBuffer,char* strSendBuffer)
{
    int ibizcode=-1;
    GetXmlBuffer(strRecvBuffer,"bizcode",&ibizcode);
    
    switch(ibizcode)
    {
        case 0:
            return biz000(strRecvBuffer,strSendBuffer);	//心跳
            break;
        case 1:
            return biz001(strRecvBuffer,strSendBuffer);	//登录
            break;
        case 2:
            return biz002(strRecvBuffer,strSendBuffer);	//业务2
            break;
        default:
            logfile.Write("非法报文：%s\n",strSendBuffer);
            return false;
    }
}


void* th1mainfunc(void* arg)
{
    pthread_detach(pthread_self());
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    pthread_cleanup_push(pthExit,arg);

    char strRecvBuffer[1024];
    char strSendBuffer[1024];
    int sockfd=(int)(long)arg;
    while(true)
    {
        memset(strRecvBuffer,0,sizeof(strRecvBuffer));
       	memset(strSendBuffer,0,sizeof(strSendBuffer));
        int iBufferlen;
        if(tcpServer.TcpRead(sockfd,strRecvBuffer, &iBufferlen,300)==false)  //超过60s没有收到心跳报文，就断开连接
            break;
        logfile.Write("recv msg:%s\n",strRecvBuffer);
        
        //业务处理
        if(BusinessProcess(strRecvBuffer,strSendBuffer)==false)
          pthread_exit(0);
        
       	logfile.Write("send msg:%s\n",strSendBuffer);
        if(tcpServer.TcpWrite(sockfd,strSendBuffer)==false)   
            break;
    }
    
    logfile.Write("client(%s) disconnected..\n", tcpServer.GetIP());
    pthread_cleanup_pop(1);
    pthread_exit(0);
}


int main(int argc, char** argv)
{
 	if(argc!=3)	
    {
        printf("Using: ./mthserver port logfile\nExample:./mthserver 5000 /tmp/mthserver.log\n\n");
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
        if(pthread_create(&pthid,NULL,th1mainfunc,(void*)(long)tcpServer.m_clientfd)!=0)
        {
          logfile.Write("create thread failed..\n");
          return -1;
        }
        vpthids.push_back(pthid);
    }
    return 0;
}