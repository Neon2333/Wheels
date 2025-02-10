// ��־�ļ�������
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

void LocalTime(char *stime,const char *fmt=0,const int timetvl=0);
void timetostr(const time_t ltime,char *stime,const char *fmt=0);

class CLogFile
{
public:
  FILE*   m_tracefp;           // ��־�ļ�ָ�롣
  char    m_filename[301];     // ��־�ļ�����������þ���·����
  char    m_openmode[11];      // ��־�ļ��Ĵ򿪷�ʽ��һ�����"a+"��
  bool    m_bEnBuffer;         // д����־ʱ���Ƿ����ò���ϵͳ�Ļ�����ƣ�ȱʡ�����á�
  long    m_MaxLogSize;        // �����־�ļ��Ĵ�С����λM��ȱʡ100M��
  bool    m_bBackup;           // �Ƿ��Զ��л�����־�ļ���С����m_MaxLogSize���Զ��л���ȱʡ���á�

    
  // MaxLogSize�������־�ļ��Ĵ�С����λM��ȱʡ100M����СΪ10M��
  CLogFile(const long MaxLogSize=100); 

  // ����־�ļ���
  // filename����־�ļ�����������þ���·��������ļ����е�Ŀ¼�����ڣ����ȴ���Ŀ¼��
  // openmode����־�ļ��Ĵ򿪷�ʽ����fopen�⺯�����ļ��ķ�ʽ��ͬ��ȱʡֵ��"a+"��
  // bBackup���Ƿ��Զ��л���true-�л���false-���л����ڶ���̵ķ�������У����������й���һ����־�ļ���bBackup����Ϊfalse��
  // bEnBuffer���Ƿ������ļ�������ƣ�true-���ã�false-�����ã�������û���������ôд����־�ļ��е����ݲ�������д���ļ���ȱʡ�ǲ����á�
  bool Open(const char *filename,const char *openmode=0,bool bBackup=true,bool bEnBuffer=false);

  // �����־�ļ�����100M���Ͱѵ�ǰ����־�ļ����ݳ���ʷ��־�ļ����л��ɹ�����յ�ǰ��־�ļ������ݡ�
  // ���ݺ���ļ�������־�ļ������������ʱ�䡣
  // ע�⣬�ڶ���̵ĳ����У���־�ļ������л������ߵĳ����У���־�ļ������л���
  bool BackupLogFile();

  // ������д����־�ļ���fmt�ǿɱ������ʹ�÷�����printf�⺯����ͬ��
  // Write������д�뵱ǰ��ʱ�䣬WriteEx������дʱ�䣬WriteUseMtxд��־��Ϊ����
  bool Write(const char *fmt,...);
  bool WriteEx(const char *fmt,...);
  bool WriteUseMtx(const char *fmt,...);
  // �ر���־�ļ�
  void Close();

  ~CLogFile();  // �������������Close������
};