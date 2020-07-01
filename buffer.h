
#ifndef BUFFER_H
#define BUFFER_H

#include <string>

class Buffer
{
private:
    char buf[256]; // 文件IO缓冲
    int p ; // 辅助缓冲的指针 p
public:
    Buffer();
    void readFromFile(std::string fileName);// 该函数从文件中读入数据
    void printToFile(std::string fileName);// 与上个函数类似，该函数输出到文件
    unsigned long long getNextN(int n); // 获取二进制文件中由[p..p+n)部分组成的数字
    void setNext(bool val);// 该函数用于对单点进行赋值
    void clear(); // 清空buf
    void setNBits(int n,unsigned long long data); // 将data中的低n个bit输出到buf中
};

#endif