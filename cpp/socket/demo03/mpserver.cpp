#include "TcpServer.h"
#include "CLogFile.h"
#include <string>

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
        sprintf(strSendBuffer,"<retcode>0</retcode><message>success</message>");
    else
        sprintf(strSendBuffer,"<retcode>-1</retcode><message>用户名或密码不正确</message>");
    
    return true;
}

bool BusinessProcess(const char* strRecvBuffer,char* strSendBuffer)
{
    int ibizcode=-1;
    GetXmlBuffer(strRecvBuffer,"bizcode",&ibizcode);
    
    switch(ibizcode)
    {
        case 0:
            //biz000(strRecvBuffer,strSendBuffer);	//心跳
            break;
        case 1:
            return biz001(strRecvBuffer,strSendBuffer);	//登录
        case 2:
            //biz002(strRecvBuffer,strSendBuffer);	//业务2
            break;
        default:
            logfile.Write("非法报文：%s\n",strSendBuffer);
            return false;
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
    char strRecvBuffer[1024];
    char strSendBuffer[1024];
    while(true)
    {
        memset(strRecvBuffer,0,sizeof(strRecvBuffer));
       	memset(strSendBuffer,0,sizeof(strSendBuffer));
        if(tcpServer.Read(strRecvBuffer, 300)==false)  
            break;
        logfile.Write("recv msg:%s\n",strRecvBuffer);
        if(BusinessProcess(strRecvBuffer,strSendBuffer)==false)        
        	ChildEXIT(-1);
       	logfile.Write("send msg:%s\n",strSendBuffer);
        if(tcpServer.Write(strSendBuffer)==false)   
            break;
    }
    
    logfile.Write("client(%s) disconnected..\n", tcpServer.GetIP());
    ChildEXIT(-1);
}