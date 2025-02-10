```cpp
//CTime.h
// 这是一个精确到微秒的计时器。
class CTimer
{
private:
  struct timeval m_start;   // 开始计时的时间。
  struct timeval m_end;     // 计时完成的时间。

  // 开始计时。
  void Start();
public:
  CTimer();  // 构造函数中会调用Start方法。

  // 计算已逝去的时间，单位：秒，小数点后面是微秒。
  double Elapsed();
};
```

```cpp
//CTime.cpp
CTimer::CTimer()
{
  memset(&m_start,0,sizeof(struct timeval));
  memset(&m_end,0,sizeof(struct timeval));

  // 开始计时
  Start();
}

// 开始计时
void CTimer::Start()
{
  gettimeofday( &m_start, 0 );
}

// 计算已逝去的时间，单位：秒，小数点后面是微秒
double CTimer::Elapsed()
{

  gettimeofday( &m_end, 0 );

  double dstart,dend;

  dstart=dend=0;

  char strtemp[51];
  memset(strtemp,0,sizeof(strtemp));
  snprintf(strtemp,30,"%ld.%ld",m_start.tv_sec,m_start.tv_usec);
  dstart=atof(strtemp);

  memset(strtemp,0,sizeof(strtemp));
  snprintf(strtemp,30,"%ld.%ld",m_end.tv_sec,m_end.tv_usec);
  dend=atof(strtemp);

  // 重新开始计时
  Start();

  return dend-dstart;
}
```

```cpp
//demo
CTimer timer;	//构造函数中调用了Start()开始计时
printf("耗时%lf\n",time.Elapsed());	//Elapserd()会打印从开始计时到当前耗时，并重新开始计时
```

