## 1. 统计int二进制中1的个数

```c
int func(int x)
{
    int count = 0;
    while(x)
    {
        count++;
        x=x&(x-1);	//清空x二进制形式最低位的1
    }
    return count;
}
```

